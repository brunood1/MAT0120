#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double data[3];
} Matrix3x1;

typedef struct {
    double data[3][3];
} Matrix3x3;

typedef struct {
    double data[4];
} Matrix4x1;

typedef struct {
    double data[4][4];
} Matrix4x4;

Matrix3x1 mutliplicarM3V(Matrix3x3 A, Matrix3x1 v) {
    Matrix3x1 result;
    for (int i = 0; i < 3; i++) {
        result.data[i] = 0;
        for (int j = 0; j < 3; j++) {
            result.data[i] += A.data[i][j] * v.data[j];
        }
    }
    return result;
}

float normaM31(Matrix3x1 v) {
    float result;
    for (int i = 0; i < 3; i++) {
        result += v.data[i]*v.data[i];
    }
    return sqrt(result);
}

Matrix3x1 normalizarM31(Matrix3x1 v) {
    Matrix3x1 result;
    float norma = normaM31(v);
    for (int i = 0; i < 3; i++) {
        result.data[i] = v.data[i]/norma;
    }
    return result;
}

Matrix3x3 multiplicarM3M(Matrix3x3 A, Matrix3x3 B) {
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

Matrix4x1 multiplicarM4V(Matrix4x4 matrix, Matrix4x1 vector) {
    Matrix4x1 result;
    int i, j;
    for (i = 0; i < 4; i++) {
        result.data[i] = 0;
        for (j = 0; j < 4; j++) {
            result.data[i] += matrix.data[i][j] * vector.data[j];
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


Matrix4x4 multiplicarM4M(Matrix4x4 A, Matrix4x4 B) {
    Matrix4x4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                result.data[i][j] += A.data[i][k] * B.data[k][j];
            }
        }
    }
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

Matrix4x4 transposta4M(Matrix4x4 A) {
    Matrix4x4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.data[i][j] = A.data[j][i];
        }
    }
    return result;
}

void print4M(Matrix4x4 A) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%f ", A.data[i][j]);
        }
        printf("\n");
    }
}

void main(){
    int i,j;
    unsigned int V,F,A,(*T)[9]; //Matriz da conectividade Fx9. Limitada a faces com no máximo 8 lados
    float (*M)[3]; //Matriz Vx3
    FILE *file = fopen("cubo.off","r");

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

    Matrix3x1 lente = {4,4,4};
    Matrix3x1 dir = {0,0,0};

    Matrix3x1 w = {0,0,0};
    for (i = 0; i<3; i++){
        w.data[i] = lente.data[i] - dir.data[i];
    }

    float a = w.data[0];
    float b = w.data[1];
    float c = w.data[2];

    Matrix3x1 u = {-b,a,0};
    Matrix3x1 v = {-c*a, -c*b, a*a + b*b};

    Matrix3x1 w_norm = normalizarM31(w);
    Matrix3x1 u_norm = normalizarM31(u);
    Matrix3x1 v_norm = normalizarM31(v);

    Matrix4x4 D = {{{1, 0, 0, -lente.data[0]}, 
                    {0, 1, 0, -lente.data[1]}, 
                    {0, 0, 1, -lente.data[2]},
                    {0, 0, 0, 1}}};

    Matrix4x4 L = {{{u_norm.data[0], u_norm.data[1], u_norm.data[2], 0}, 
                    {v_norm.data[0], v_norm.data[1], v_norm.data[2], 0}, 
                    {w_norm.data[0], w_norm.data[1], w_norm.data[2], 0}, 
                    {0, 0, 0, 1}}};

    Matrix4x4 Lt = transposta4M(L);

    float z0 = 0.5;

    Matrix4x4 W = {{{1, 0, 0, 0}, 
                    {0, 1, 0, 0}, 
                    {0, 0, 1/(1-z0), (-z0)/(1-z0)},
                    {0, 0, 1, 0}}};


    float (*N)[3];
    N = malloc(3*V*sizeof(float));

    Matrix4x4 C0 = multiplicarM4M(Lt, D);
    Matrix4x4 C = multiplicarM4M(W, C0);

    for (int i = 0; i < V; i++){
        Matrix4x1 vi = {M[i][0], M[i][1], M[i][2], 1};
        Matrix4x1 ui = multiplicarM4V(C,vi);

        N[i][0] = ui.data[0]/ui.data[3];
        N[i][1] = ui.data[1]/ui.data[3];
        N[i][2] = ui.data[2]/ui.data[3];
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