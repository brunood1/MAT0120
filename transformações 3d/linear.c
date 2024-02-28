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

void main(){
    int i,j;
    unsigned int V,F,A,(*T)[9]; //Matriz da conectividade Fx9. Limitada a faces com no máximo 8 lados
    float (*M)[3]; //Matriz Vx3
    FILE *file = fopen("OFF.off","r");

    //Lendo cabeçalho (Apenas cabelhos sem comentários)
    fscanf(file,"OFF\n%u %u %u\n",&V,&F,&A);

    //Alocando memória para a matrix com os vértices
    M = malloc(3*V*sizeof(float));

    //carregando os vértices
    for(i=0;i<V;i++) fscanf(file,"%f %f %f\n",&M[i][0],&M[i][1],&M[i][2]);

    //Alocando memória para a matrix com a conectividade
    T = malloc(9*F*sizeof(int));

    //Carregando a conectividade [(k) a b c d e f g h]. k: número de vértices. a,b,c,d,e,f,g,h: índices dos vértices
    for(i=0;i<F;i++){
        fscanf(file,"%u",&T[i][0]);
        for(j=1;j<=T[i][0];j++) fscanf(file," %u",&T[i][j]);
        fscanf(file,"%*[^\n]"); //Descartando o restante da linha (cor, transparência)
    }
    fclose(file);

    float (*N)[3];
    N = malloc(3*V*sizeof(float));
    Matrix3x3 L = {{{1,0,2},
                    {0,2,0},
                    {0,0,3}}};

    for (int i = 0; i < V; i++){
        Matrix3x1 v = {M[i][0], M[i][1], M[i][2]};
        Matrix3x1 u = multiplicarMV(L,v);
        N[i][0] = u.data[0];
        N[i][1] = u.data[1];
        N[i][2] = u.data[2];
    }

    printf("OFF\n%u %u %u\n",V,F,A);
    for(i=0;i<V;i++){ 
        printf("%g %g %g\n",N[i][0],N[i][1],N[i][2]);
    }
    for(i=0;i<F;i++){
        printf("%u",T[i][0]);
        for(j=1;j<=T[i][0];j++) printf(" %u",T[i][j]);
        printf("\n");
    }

    free(M);
    free(N);
    free(T);
}