#include <stdio.h>
#include <math.h>

// gcc möbius.c -lm -o mobius
// ./mobius > mobius.off

// TAREFA ::: FAZER IMAGEM .ply

// ABRIR COM MESHLAB

int R = 15;

float x(float u, float v){
    return (R + v*cos(0.5*u))*cos(u);
}

float y(float u, float v){
    return (R + v*cos(0.5*u))*sin(u);
}

float z(float u, float v){
    return v*sin(0.5*u);
}

int main(){
    printf("OFF\n");
    // printf("1260 1240 2500\n");
    printf("1323 1240 2562\n");
    for (int v = -10; v <= 10; v++){
        for (float u = 0; u <= 6.2; u+=0.1){
            printf("%f %f %f\n", x(u,v), y(u,v), z(u,v)); // TROCAR FUNÇÃO AQUI
        }
    }
    for (int j = 0; j < 1260; j+=63){
        for (int i = 0; i < 62; i++){
            printf("4 %d %d %d %d\n", i+j, i+63+j, i+64+j, i+1+j);
        }
    }

    // for (int i = 0; i < 62; i++){
    //     printf("4 %d %d %d %d\n", 1260+i,0+i,1+i,1261+i);
    // }

    return 0;
}
