//------------------------
// Universidade Federal de Sergipe
// Departamento de Matemática
// Biblioteta simples para o curso de Introdução à Computação Gráfica
// Desenha uma reta em uma imagem pbm
// Sintaxe: ./reta
// Prof Evilson Vieira
// Aracaju-SE 06/12/2023
//------------------------

#include <stdio.h>
#include <stdlib.h>

// função que retorna o valor absoluto de um inteiro, ou seja, o módulo do número
int abs(int a){
  if (a<0) a=-a;
  return a;
}

void sum(int *x, int *a, int*b){
    x[0]=(a[0]+b[0]); // divisão por 2 arredondada para o inteiro mais próximo
    x[1]=(a[1]+b[1]); // idem
}

// Essa função é recursiva (ela chama ela própria)
void casteljau(int *a, int *b, int *c, int *d, unsigned char **im){
    int p[5][2];
    sum(p[0],a,b);
    sum(p[1],b,c);
    sum(p[2],c,d);
    sum(p[3],p[0],p[1]);
    sum(p[4],p[1],p[2]);
    sum(p[1],p[3],p[4]); // p[1] já está liberado

    p[0][0]+=1; p[0][0]>>=1;
    p[0][1]+=1;p[0][1]>>=1; 

    p[2][0]+=1; p[2][0]>>=1;
    p[2][1]+=1; p[2][1]>>=1; 

    p[3][0]+=2;p[3][0]>>=2;
    p[3][1]+=2;p[3][1]>>=2;  

    p[4][0]+=2;p[4][0]>>=2;
    p[4][1]+=2;p[4][1]>>=2;

    p[1][0]+=4;p[1][0]>>=3;
    p[1][1]+=4;p[1][1]>>=3;

    im[p[1][0]][p[1][1]]=1;

    if ((abs(a[0]-p[1][0])>1)||(abs(a[1]-p[1][1])>1))
        casteljau(a, p[0], p[3], p[1], im);
    if ((abs(d[0]-p[1][0])>1)||(abs(d[1]-p[1][1])>1))
        casteljau(p[1], p[4], p[2], d, im);
}

void main(int argc, char **argv)
{
  int i, j, l, h;
  FILE *file;

  l=200; //largura: número de colunas
  h=150; //altura : número de linhas

  //---------------------------------------------
  // Carregando a imagem
  //---------------------------------------------
  // Alocanco memória para a imagem
  unsigned char **imagem;           // ponteiro para um vetor de ponteiros (parecido com a estrutura de matriz)
  imagem = malloc(l*sizeof(char*)); // alocando ponteiros para as colunas: x
  for (i=0; i<l; i++)               // alocando ponteiros para cada coordenada da coluna: y
    imagem[i] = malloc(h);          // Seria malloc(h*sizeof(unsigned char)) mas sizeof(unsigned char)=1 pois um unsigned char ocupa apenas 1 byte
  // Nessa estrutura o píxel imagem[i][j] têm coordenadas (i,j)  
  
  // pintando de branco
  for(i=0; i<l; i++)
    for(j=0; j<h; j++)
      imagem[i][j]=0; 
  //---------------------------------------------

  //---------------------------------------------
  // Desenhando a reta
  //---------------------------------------------
  int p0[2]={13,17},   q0[2]={13,37},    // ponto+controle inicial e final da curva
      p1[2]={190,130}, q1[2]={190,50};

  // pinta as extremidades de preto
  imagem[p0[0]][p0[1]]=1;
  imagem[p1[0]][p1[1]]=1;
  
  casteljau(p0,q0,q1,p1,imagem); // Executa a função recursiva
  //---------------------------------------------

  //---------------------------------------------
  // Gravando o arquivo de imagem no formato pbm
  //---------------------------------------------
  file = fopen("bezier.pbm", "w");
  fprintf(file, "P1\n# Curva de Bézier no plano - Prof Evilson\n");
  fprintf(file, "%u %u\n", l, h);
  for (j=0;j<h;j++){
    for (i=0;i<l;i++)
        fprintf(file, "%hhu", imagem[i][j]);
    fprintf(file, "\n");
    }
  fclose(file);
  //---------------------------------------------

  //---------------------------------------------
  // Liberando a memória alocada
  //---------------------------------------------
  for (i=0; i<l; i++)
    free(imagem[i]);
  free(imagem);
}

