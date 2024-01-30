#include <stdio.h>

// gcc plano.c -o plano
// ./plano > plano.off

// ABRIR COM MESHLAB

int main(){
    printf("OFF\n");
    printf("121 100 220\n");
    for (int y = -5; y <= 5; y++){
        for (int x = -5; x <= 5; x++){
            printf("%d %d %d\n", x, y, 3*x + y); // TROCAR FUNÇÃO AQUI
        }
    }
    for (int j = 0; j < 110; j+=11){
        for (int i = 0; i < 10; i++){
            printf("4 %d %d %d %d\n", i+j, i+11+j, i+12+j, i+1+j);
        }
    }

    return 0;
}
