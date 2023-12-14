#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int c(int *a, int *b){
  int d;
  d = pow(pow((a[0] - b[0]),2) + pow((a[1] - b[1]),2), 0.5);
  return d;
}

void main(int argc, char **argv)
{
  int i, j, k, l, h;
  FILE *file;

  l=500; //largura: número de colunas
  h=500; //altura : número de linhas

  unsigned char ***imagem;           // ponteiro para um vetor de ponteiros (parecido com a estrutura de matriz)
  imagem = malloc(l*sizeof(char*)); // alocando ponteiros para as colunas: x
  for (i=0; i<l; i++)               // alocando ponteiros para cada coordenada da coluna: y
    imagem[i] = malloc(h);          // Seria malloc(h*sizeof(unsigned char)) mas sizeof(unsigned char)=1 pois um unsigned char ocupa apenas 1 byte
  // Nessa estrutura o píxel imagem[i][j] têm coordenadas (i,j)  
  
  // pintando de branco
  for(i=0; i<l; i++)
    for(j=0; j<h; j++)
      imagem[i][j]=255; 

  time_t t;
  srand((unsigned) time(&t));

  int centro[2];
  int raio;
  unsigned char cor[3];

  int x;
  for (x = 0;x<100;x++){
    cor[0] = rand();
    cor[1] = rand();
    cor[2] = rand();

    raio = rand() % 100;
    
    centro[0] = rand() % 500;
    centro[1] = rand() % 500;

    for (i = 0; i < l; i++){
      for (j = 0; j < h; j++){
        int p[2] = {i,j};
        if (c(centro, p) <= raio){
          imagem[i][j] = cor;
        }
      }
    }
  }
  
  file = fopen("circulos.ppm", "w");
  fprintf(file, "P2\n# Reta no plano - Prof Evilson\n");
  fprintf(file, "%u %u\n255\n", l, h);
  for (j=0;j<h;j++){
    for (i=0;i<l;i++)
        fprintf(file, "%hhu ", imagem[i][j]);
    fprintf(file, "\n");
    }
  fclose(file);


  for (i=0; i<l; i++)
    free(imagem[i]);
  free(imagem);
}

