#include <stdio.h>
#include <stdlib.h>

int main(){
    unsigned char A[100][100][3];

    for (int i=0;i<100;i++){
        for (int j=0;j<100;j++){
            if (42*(i-42) - 31*(j-31) > 0){
                A[i][j][0] = 255;
                A[i][j][1] = 0;
                A[i][j][2] = 0;
            }
            else if (42*(i-42) - 31*(j-31) < 0){
                A[i][j][0] = 0;
                A[i][j][1] = 0;
                A[i][j][2] = 255;
            }
        }
    }
    
    FILE *pF = fopen("imagem_C.ppm", "w");

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