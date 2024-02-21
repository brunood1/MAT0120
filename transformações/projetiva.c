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


    // do quadrado unitário para o tamanho da imagem
    Matrix3x1 u4 = {h, l, 1};
    Matrix3x3 U = {{{0, h, 0},{0, 0, l},{1, 1, 1}}};
    Matrix3x3 Uinv = inversaM(U);
    Matrix3x1 abg1 = multiplicarMV(Uinv, u4);
    float alfa1 = abg1.data[0];
    float beta1 = abg1.data[1];
    float gama1 = abg1.data[2];
    Matrix3x3 psi1 = {{{-alfa1, 0, 0},{0, beta1, 0},{0, 0, gama1}}};

    Matrix3x3 W = {{{0, 1, 0},{0, 0, 1},{1, 1, 1}}};
    Matrix3x3 Winv = inversaM(W);
    Matrix3x3 T1 = multiplicarMM(U, multiplicarMM(psi1, Winv));

    // do quadrado unitário para a imagem projetada
    Matrix3x1 v4 = {200,130,1};
    Matrix3x3 Vt = {{{2,2,1},{270,50,1},{60,170,1}}};
    Matrix3x3 V  = transpostaM(Vt);
    Matrix3x3 Vinv = inversaM(V);
    Matrix3x1 abg2 = multiplicarMV(Vinv, v4);
    float alfa2 = abg2.data[0];
    float beta2 = abg2.data[1];
    float gama2 = abg2.data[2];
    Matrix3x3 psi2 = {{{-alfa2, 0, 0},{0, beta2, 0},{0,0,gama2}}};
    Matrix3x3 T2 = multiplicarMM(V, multiplicarMM(psi2, Winv));

    Matrix3x3 T = multiplicarMM(T2, inversaM(T1));
    Matrix3x3 Tinv = inversaM(T);

    int m[4] = {Vt.data[0][0], Vt.data[1][0], Vt.data[2][0], v4.data[0]};
    int n[4] = {Vt.data[0][1], Vt.data[1][1], Vt.data[2][1], v4.data[1]};

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
            int wx = w.data[0];
            int wy = w.data[1];
            I = floor(wx);
            J = floor(wy);
            if (I >= 0 && I < h && J >= 0 && J < l){
                new[i][j][0] = imagem[I][J][0];
                new[i][j][1] = imagem[I][J][1];
                new[i][j][2] = imagem[I][J][2];
            }
        }
    }

    fp = fopen("projetiva.ppm", "wb");
    fprintf(fp, "P6\n");
    fprintf(fp, "%u %u\n255\n", L, H);
    for (j=0;j<H;j++) {
        for (i=0;i<L;i++)
            fprintf(fp,"%c%c%c", new[j][i][0],new[j][i][1],new[j][i][2]); 
    }
    fclose(fp);
}
