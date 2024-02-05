#include <stdio.h>
#include <math.h>

// gcc cos.c -o cos
// ./cos > cos.off

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
    printf("1323 1240 2562\n");
    for (int v = -10; v <= 10; v++){
        for (float u = 0; u <= 6.2; u+=0.1){
            printf("%f %f %f\n", x(u,v), y(u,v), z(u,v)); // TROCAR FUNÇÃO AQUI
        }
    }
    for (int j = 0; j < 3782; j+=62){
        for (int i = 0; i < 61; i++){
            printf("4 %d %d %d %d\n", i+j, i+61+j, i+62+j, i+1+j);
        }
    }

    return 0;
}
