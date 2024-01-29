#include <stdio.h>

// gcc lista.c -o lista
// ./lista > NOME.off

// ABRIR COM MESHLAB

int main(){
    printf("OFF\n");
    printf("441 400 420\n");
    for (int y = -10; y <= 10; y++){
        for (int x = -10; x <= 10; x++){
            printf("%d %d %d\n", x, y, 3*x + y); // TROCAR FUNÇÃO AQUI
        }
    }
    for (int j = 0; j < 110; j+=21){
        for (int i = 0; i < 20; i++){
            printf("4 %d %d %d %d\n", i+j, i+21+j, i+22+j, i+1+j);
        }
    }

    return 0;
}
