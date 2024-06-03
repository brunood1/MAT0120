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
    float result = 0;
    for (int i = 0; i < 3; i++) {
        result += v.data[i]*v.data[i];
    }
    float r = sqrt(result);
    return r;
}

Matrix3x1 normalizarM31(Matrix3x1 v) {
    Matrix3x1 result;
    float norma = normaM31(v);
    if (norma != 0) {
        for (int i = 0; i < 3; i++) {
            result.data[i] = v.data[i] / norma;
        }
    } else {
        // Handle the case where the vector is already zero or has zero magnitude
        // Here, we'll just return the zero vector
        for (int i = 0; i < 3; i++) {
            result.data[i] = 0.0f;
        }
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

void merge(float arr[][2], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    float L[n1][2], R[n2][2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++) {
        L[i][0] = arr[l + i][0];
        L[i][1] = arr[l + i][1];
    }
    for (j = 0; j < n2; j++) {
        R[j][0] = arr[m + 1 + j][0];
        R[j][1] = arr[m + 1 + j][1];
    }

    // Merge the temporary arrays back into arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i][1] <= R[j][1]) {
            arr[k][0] = L[i][0];
            arr[k][1] = L[i][1];
            i++;
        }
        else {
            arr[k][0] = R[j][0];
            arr[k][1] = R[j][1];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k][0] = L[i][0];
        arr[k][1] = L[i][1];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k][0] = R[j][0];
        arr[k][1] = R[j][1];
        j++;
        k++;
    }
}

// Function to perform merge sort
void mergeSort(float arr[][2], int l, int r) {
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for large l and r
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Merge the sorted halves
        merge(arr, l, m, r);
    }
}

int cross_product(int a[2], int b[2], int c[2]) {
    return (b[0] - a[0]) * (c[1] - a[1]) - (c[0] - a[0]) * (b[1] - a[1]);
}

int pinta_quadrado(int p1[2], int p2[2], int p3[2], int p4[2], int p[2]) {
    // produto vetorial de todos triangulos
    int cp1 = cross_product(p1, p2, p);
    int cp2 = cross_product(p2, p3, p);
    int cp3 = cross_product(p3, p4, p);
    int cp4 = cross_product(p4, p1, p);
    
    if ((cp1 > 0 && cp2 > 0 && cp3 > 0 && cp4 > 0) || (cp1 < 0 && cp2 < 0 && cp3 < 0 && cp4 < 0))
        return 1; // dentro
    else
        return 0; // fora
}

void reta(int *p0, int *p1, unsigned char (**imagem)[3]) {
    int p2[2];
    if ((abs(p0[0] - p1[0]) > 1) || (abs(p0[1] - p1[1]) > 1)) {
        p2[0] = (p0[0] + p1[0]) / 2; 
        p2[1] = (p0[1] + p1[1]) / 2; 
        imagem[p2[0]][p2[1]][0] = 255;
        imagem[p2[0]][p2[1]][1] = 255;
        imagem[p2[0]][p2[1]][2] = 255;
        reta(p0, p2, imagem);
        reta(p2, p1, imagem);
    }
}

void min_column_values(float matrix[][2], float rows, float *min_col1, float *min_col2) {
    *min_col1 = matrix[0][0]; // Initialize min_col1 with the first element of the first column
    *min_col2 = matrix[0][1]; // Initialize min_col2 with the first element of the second column
    
    // Loop through the matrix to find the minimum values for both columns
    for (int i = 0; i < rows; i++) {
        if (matrix[i][0] < *min_col1) {
            *min_col1 = matrix[i][0];
        }
        if (matrix[i][1] < *min_col2) {
            *min_col2 = matrix[i][1];
        }
    }
}

void main(){
    int i,j;
    unsigned int V,F,A,(*T)[9]; //Matriz da conectividade Fx9. Limitada a faces com no máximo 8 lados
    float (*M)[3]; //Matriz Vx3
    FILE *file = fopen("cubo.off","r");
    char nome[11];

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

    double xy[16][2] = {
        {16.00, 0.00},
    {15.31, 5.88},
    {13.42, 11.31},
    {10.39, 15.31},
    {6.00, 16.00},
    {1.69, 15.31},
    {-2.42, 13.42},
    {-5.88, 10.39},
    {-9.00, 6.00},
    {-11.31, 1.69},
    {-13.42, -2.42},
    {-15.31, -5.88},
    {-16.00, -9.00},
    {-15.31, -11.31},
    {-13.42, -13.42},
    {-10.39, -15.31}
    };

    for (int im = 0; im < 16; im++){
    Matrix3x1 lente = {xy[im][1],xy[im][0],4};
    Matrix3x1 dir = {0,0,0};

    Matrix3x1 w = {0,0,0};
    for (i = 0; i<3; i++){
        w.data[i] = -lente.data[i] + dir.data[i];
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

    float z0 = 0.7;

    Matrix4x4 W = {{{1, 0, 0, 0}, 
                    {0, 1, 0, 0}, 
                    {0, 0, 1/(1-z0), (-z0)/(1-z0)},
                    {0, 0, 1, 0}}};


    float (*N)[3];
    N = malloc(3*V*sizeof(float));

    Matrix4x4 C0 = multiplicarM4M(L, D);
    Matrix4x4 C = multiplicarM4M(W, C0);

    for (int i = 0; i < V; i++){
        Matrix4x1 vi = {M[i][0], M[i][1], M[i][2], 1};
        Matrix4x1 ui = multiplicarM4V(C,vi);

        N[i][0] = ui.data[0]/ui.data[3];
        N[i][1] = ui.data[1]/ui.data[3];
        N[i][2] = ui.data[2]/ui.data[3];
    }

    // Matrix3x3 B = {{{1,0,2},
    //                 {0,2,0},
    //                 {0,0,3}}};

    // float (*K)[3];
    // K = malloc(3*V*sizeof(float));
    // for (int i = 0; i < V; i++){
    //     Matrix3x1 vj = {N[i][0], N[i][1], N[i][2]};
    //     Matrix3x1 uj = multiplicarM3V(B,vj);
    //     K[i][0] = uj.data[0];
    //     K[i][1] = uj.data[1];
    //     K[i][2] = uj.data[2];
    // }

    // printf("OFF\n%u %u %u\n",V,F,A);
    // for(i=0;i<V;i++){ 
    //     printf("%g %g %g\n",N[i][0],N[i][1],N[i][2]);
    // }
    // for(i=0;i<F;i++){
    //     printf("%u",T[i][0]);
    //     for(j=1;j<=T[i][0];j++) printf(" %u",T[i][j]);
    //     printf("\n");
    // }

    // IMAGEM PPM
    unsigned int qtd_lados = T[0][0];
    unsigned int vertices[qtd_lados];

    float inv = 1.0/qtd_lados;

    // N armazena as coordenadas depois da transformação
    // X armazena o indice da face e a coordenada z do centro
    // Y armazena as cordenadas transformadas mas somente (x,y)
    // T matriz de conectividade

    for (i = 0; i < V; i++){
        N[i][0] *= 1000;
        N[i][1] *= 1000;
        N[i][2] *= 1000;
    } 
    
    float (*X)[2];
    X = malloc(2*F*sizeof(float));

    for (i = 0; i < F; i++){
        X[i][0] = i;
    }

    for (int k = 0; k < F; k++){
        for (i = 0; i < qtd_lados; i++){
            vertices[i] = T[k][i];
        }

        float Z[qtd_lados];
        for (i = 0; i < qtd_lados; i++){
            Z[i] = 0;
        }
        for (i = 0; i < qtd_lados; i++){
            Z[i] = N[vertices[i]][2];
        }
        for (i = 0; i < qtd_lados; i++){
            X[k][1] += inv*Z[i];
        }     
    }

    mergeSort(X, 0, F-1);

    float Y[V][2];
    for (i = 0; i < V; i++){
        Y[i][0] = N[i][0];
        Y[i][1] = N[i][1];
    }
    
    float min1, min2;
    min_column_values(Y,V,&min1, &min2);
    for (i = 0; i < V; i++){
        Y[i][0] -= (min1 -30);
        Y[i][1] -= (min2 -30);
    }

    int dim = 400; // tamanho da imagem ppm
    unsigned char (**image)[3];
    image = calloc(dim, sizeof(char*)); 

    for (i=0; i<dim; i++){
        image[i] = calloc(dim * 3, sizeof(char));
    }

    for (int k = 0; k < F; k++){
        int face = X[k][0];
        printf("FILE: %d ::: plotting face %d/%d\n", im, k,F);

        int pontos[4][2];
        for (i = 0; i < 4; i++){
            int pt = T[face][i+1];
            pontos[i][0] = floor(Y[pt][0]);
            pontos[i][1] = floor(Y[pt][1]);
        }
        int p1[2] = {pontos[0][1], pontos[0][0]};
        int p2[2] = {pontos[1][1], pontos[1][0]};
        int p3[2] = {pontos[2][1], pontos[2][0]};
        int p4[2] = {pontos[3][1], pontos[3][0]};
        printf("points: (%d, %d)\n", p1[0], p1[1]);
        printf("points: (%d, %d)\n", p2[0], p2[1]);
        printf("points: (%d, %d)\n", p3[0], p3[1]);
        printf("points: (%d, %d)\n", p4[0], p4[1]);

        for (i = 0; i < dim; i++){
            for (j = 0; j < dim; j++){
                int p[2] = {i,j};
                if (pinta_quadrado(p1, p2, p3, p4, p) == 1){
                    image[i][j][0] = 182 + 3*face;
                    image[i][j][1] = 5;
                    image[i][j][2] = 13;
                    // printf("(%d, %d) is inside", i, j);
                } 
            }
        }
        
        reta(p1, p2, image);
        reta(p2, p3, image);
        reta(p3, p4, image);
        reta(p4, p1, image);
    }

    sprintf(nome, "file%.2d.ppm", im);
    file = fopen(nome, "wb");
    fprintf(file, "P6\n");
    fprintf(file, "%u %u\n255\n", dim, dim);
    for (j=0;j<dim;j++) {
        for (i=0;i<dim;i++)
            fprintf(file,"%c%c%c", image[j][i][0],image[j][i][1],image[j][i][2]); 
    }
    fclose(file);
    }
    

    // free(M);
    // free(N);
    // free(X);
    // free(T);
    // free(image);
}