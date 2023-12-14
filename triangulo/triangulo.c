#include <stdio.h>
#include <stdlib.h>

int det(int *x, int *y, int *z){
    int X[2][2];
    X[0][0] = y[0] - x[0];
    X[0][1] = y[1] - x[1];
    X[1][0] = z[0] - x[0];
    X[1][1] = z[1] - x[1];

    return X[0][0]*X[1][1] - X[0][1]*X[1][0];
}

int main(){
    unsigned char A[100][100][3];
    int x[2] = {55,60};
    int y[2] = {31,22};
    int z[2] = {71,11};

    for (int i=0;i<100;i++){
        for (int j=0;j<100;j++){
            int p[2] = {i,j};
            if (det(x,y,p) > 0 && det(z,x,p) > 0 && det(y,z,p) > 0){
                A[i][j][0] = 182;
                A[i][j][1] = 9;
                A[i][j][2] = 88;
            }
            else {
                A[i][j][0] = 21;
                A[i][j][1] = 59;
                A[i][j][2] = 89;
            }
        }
    }
    
    FILE *pF = fopen("triangulo_C.ppm", "w");

    fprintf(pF, "P3\n");
    fprintf(pF, "100 100\n255\n");

    for (int i = 0; i < 100; i++){
        for (int j = 0; j < 100; j++){
            for (int k = 0; k < 3; k++){
                fprintf(pF, "%hhu\n", A[i][j][k]);
            }  
        }
    }
    return 0;
}