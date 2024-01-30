#include <stdio.h>
#include <math.h>

// gcc cos.c -o cos
// ./cos > cos.off

// ABRIR COM MESHLAB

int main(){
    printf("OFF\n");
    printf("441 400 840\n");
    for (int y = -10; y <= 10; y++){
        for (int x = -10; x <= 10; x++){
            printf("%d %d %d\n", x, y, cos(sqrt(x*x + y*y))); // TROCAR FUNÇÃO AQUI
        }
    }
    for (int j = 0; j < 420; j+=21){
        for (int i = 0; i < 20; i++){
            printf("4 %d %d %d %d\n", i+j, i+21+j, i+22+j, i+1+j);
        }
    }

    return 0;
}
