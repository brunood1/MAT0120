#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double data[3];
} Matrix3x1;

typedef struct {
    double data[3][3];
} Matrix3x3;

Matrix3x1 multiplicarMV(Matrix3x3 A, Matrix3x1 v) {
    Matrix3x1 result;
    for (int i = 0; i < 3; i++) {
        result.data[i] = 0;
        for (int j = 0; j < 3; j++) {
            result.data[i] += A.data[i][j] * v.data[j];
        }
    }
    return result;
}

Matrix3x3 multiplicarMM(Matrix3x3 A, Matrix3x3 B) {
    Matrix3x3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                result.data[i][j] += A.data[i][k] * B.data[k][j];
            }
        }
    }
    return result;
}

Matrix3x3 inversaM(Matrix3x3 A) {
    Matrix3x3 result;
    double det = A.data[0][0]*(A.data[1][1]*A.data[2][2] - A.data[1][2]*A.data[2][1]) - 
                 A.data[0][1]*(A.data[1][0]*A.data[2][2] - A.data[1][2]*A.data[2][0]) +
                 A.data[0][2]*(A.data[1][0]*A.data[2][1] - A.data[1][1]*A.data[2][0]);

    double invDet = 1.0 / det;

    result.data[0][0] =  (A.data[1][1]*A.data[2][2] - A.data[1][2]*A.data[2][1]) * invDet;
    result.data[0][1] = -(A.data[0][1]*A.data[2][2] - A.data[0][2]*A.data[2][1]) * invDet;
    result.data[0][2] =  (A.data[0][1]*A.data[1][2] - A.data[0][2]*A.data[1][1]) * invDet;
    result.data[1][0] = -(A.data[1][0]*A.data[2][2] - A.data[1][2]*A.data[2][0]) * invDet;
    result.data[1][1] =  (A.data[0][0]*A.data[2][2] - A.data[0][2]*A.data[2][0]) * invDet;
    result.data[1][2] = -(A.data[0][0]*A.data[1][2] - A.data[0][2]*A.data[1][0]) * invDet;
    result.data[2][0] =  (A.data[1][0]*A.data[2][1] - A.data[1][1]*A.data[2][0]) * invDet;
    result.data[2][1] = -(A.data[0][0]*A.data[2][1] - A.data[0][1]*A.data[2][0]) * invDet;
    result.data[2][2] =  (A.data[0][0]*A.data[1][1] - A.data[0][1]*A.data[1][0]) * invDet;

    return result;
}

Matrix3x3 transpostaM(Matrix3x3 A) {
    Matrix3x3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.data[i][j] = A.data[j][i];
        }
    }
    return result;
}

void multiplicarMs(double scalar, Matrix3x1 *vector) {
    for (int i = 0; i < 3; i++) {
        vector->data[i] *= scalar;
    }
}


void main(){ // int argc, char **argv
    int i, j, k, l, h, L, H;
    unsigned char type, caractere;
    unsigned int cmax, r, g, b;
    FILE *fp;

    // TROCAR NOME DO ARQUIVO AQUI
    fp = fopen("turtle.ppm", "rb");

    fscanf(fp, "P%hhu\n", &type); 

    while ((caractere=getc(fp))=='#')
        while((caractere=getc(fp))!='\n');
    ungetc(caractere,fp);

    fscanf(fp, "%u %u\n%hhu\n", &l, &h, &cmax); 

    unsigned char imagem[h][l][3];

    if(type==3){
        for(j=0; j<h; j++) {
            for(i=0; i<l; i++){
                fscanf(fp, "%u %u %u", &r, &g, &b);
                imagem[j][i][0] = (unsigned char) r;
                imagem[j][i][1] = (unsigned char) g;
                imagem[j][i][2] = (unsigned char) b;
            }
        }
        fclose(fp);
    }
    else if(type==6){
        for(j=0; j<h; j++)
            for(i=0; i<l; i++)
                fscanf(fp, "%c%c%c", &imagem[j][i][0],&imagem[j][i][1],&imagem[j][i][2]);
        fclose(fp);
    }
    else{
        printf("Formato inválido!");
        fclose(fp);
        exit(0);
    }

    /*
    [ a  b  0 ]
    [ c  d  0 ]
    [ 0  0  1 ]
    */
    Matrix3x3 T = {{{1,0,0},{2,1,0},{0,0,1}}};
    Matrix3x3 Tinv = inversaM(T);

    Matrix3x1 aa = {0,0,1};
    Matrix3x1 bb = {h,0,1};
    Matrix3x1 cc = {0,l,1};
    Matrix3x1 dd = {h,l,1};

    Matrix3x1 Ta = multiplicarMV(T,aa);
    Matrix3x1 Tb = multiplicarMV(T,bb);
    Matrix3x1 Tc = multiplicarMV(T,cc);
    Matrix3x1 Td = multiplicarMV(T,dd);

    int m[4] = {Ta.data[0], Tb.data[0], Tc.data[0], Td.data[0]};
    int n[4] = {Ta.data[1], Tb.data[1], Tc.data[1], Td.data[1]};

    int Hm = m[0];
    for (int i = 1; i < 4; i++) {
        if (m[i] < Hm) {
            Hm = m[i];
        }
    }

    int Lm = n[0];
    for (int i = 1; i < 4; i++) {
        if (n[i] < Lm) {
            Lm = n[i];
        }
    }

    for (int i = 0; i < 4; i++) {
        m[i] = abs(m[i]);
        n[i] = abs(n[i]);
    }

    H = m[0];
    for (int i = 1; i < 4; i++) {
        if (m[i] > H) {
            H = m[i];
        }
    }

    L = n[0];
    for (int i = 1; i < 4; i++) {
        if (n[i] > L) {
            L = n[i];
        }
    }

    unsigned char (**new)[3];
    new = calloc(H, sizeof(char*)); 

    for (i=0; i<H; i++)
        new[i] = calloc(L * 3, sizeof(char));

    int I = 0;
    int J = 0;
    for (int i = 0; i < H; i++){
        for (int j = 0; j < L; j++){
            Matrix3x1 v = {i,j,1};
            Matrix3x1 w = multiplicarMV(Tinv,v);
            float w2 = w.data[2];
            float w2inv = 1.0/w2;
            multiplicarMs(w2inv, &w);
            int wx = w.data[0] - Hm;
            int wy = w.data[1] - Lm;
            I = floor(wx);
            J = floor(wy);
            if (I >= 0 && I < h && J >= 0 && J < l){
                new[i][j][0] = imagem[I][J][0];
                new[i][j][1] = imagem[I][J][1];
                new[i][j][2] = imagem[I][J][2];
            }
        }
    }

    fp = fopen("linear.ppm", "wb");
    fprintf(fp, "P6\n");
    fprintf(fp, "%u %u\n255\n", L, H);
    for (j=0;j<H;j++) {
        for (i=0;i<L;i++)
            fprintf(fp,"%c%c%c", new[j][i][0],new[j][i][1],new[j][i][2]); 
    }
    fclose(fp);
}
