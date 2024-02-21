// Universidade Federal de Sergipe
// Material didático do curso Fundamentos de Computação Gráfica
// Prof Evilson 16/02/2024

// Compilação: gcc leitor_off.c -o leitor_off
// Sintaxe: ./leitor_off file.off

#include <stdio.h>
#include <stdlib.h>

void main(int argc, char **argv){
    if (argc != 2) exit(0); //A sintaxe precisa de dois parâmetros: ./leitor_off file.off

    int i,j;
    unsigned int V,F,A,(*T)[9]; //Matriz da conectividade Fx9. Limitada a faces com no máximo 8 lados
    float (*M)[3]; //Matriz Vx3
    FILE *file = fopen(argv[1],"r");

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

    // Conferindo
    printf("OFF\n%u %u %u\n",V,F,A);
    for(i=0;i<V;i++) printf("%g %g %g\n",M[i][0],M[i][1],M[i][2]);
    for(i=0;i<F;i++){
        printf("%u",T[i][0]);
        for(j=1;j<=T[i][0];j++) printf(" %u",T[i][j]);
        printf("\n");
    }

    // Liberando a memória alocada:
    free(M);
    free(T);
}

