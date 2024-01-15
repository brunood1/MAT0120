
// Sintaxe: ./ppmtopgm image.ppm image.pgm

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void main(int argc, char **argv){
  int i, j, k, r, l, h;
  unsigned char type, cmax, caractere;
  FILE *fp;
  
  fp = fopen(argv[1], "r");
  while ((caractere=getc(fp))=='#')
    while((caractere=getc(fp))!='\n');
  ungetc(caractere,fp);

  fscanf(fp, "P%hhu\n", &type);
  while ((caractere=getc(fp))=='#')
    while((caractere=getc(fp))!='\n');
  ungetc(caractere,fp);
  
  fscanf(fp, "%u %u\n%hhu\n", &l, &h, &cmax);
  unsigned char p[h][l][3];

  if(type==3){
    for(i=0; i<h; i++)
      for(j=0; j<l; j++)
        fscanf(fp, "%hhu %hhu %hhu", &p[i][j][0],&p[i][j][1],&p[i][j][2]);
    fclose(fp);
  }
  else if(type==6){
    for(i=0; i<h; i++)
      for(j=0; j<l; j++)
        fscanf(fp, "%c%c%c", &p[i][j][0],&p[i][j][1],&p[i][j][2]);
    fclose(fp);
  }       
  else{
    printf("Formato inválido!");
    fclose(fp);
    exit(0);
  }

  int X = 2;

  int H = h*X;
  int L = l*X;

  int I,J;

  int A[2][2] = {2,0,0,2};
  int Ainv[2][2] = {0.5,0,0,0.5};


  unsigned char g[H][L][3];
  for (i=0; i<H; i++){
    for (j=0; j<L; j++){
        I = i*Ainv[0][0] + j*Ainv[0][1];
        J = i*Ainv[1][0] + j*Ainv[1][1];

        I = floor(I);
        J = floor(J);

        g[i][j][0] = p[I][J][0];
        g[i][j][1] = p[I][J][1];
        g[i][j][2] = p[I][J][2];
    }
  }

  fp = fopen(argv[2], "w");

  fprintf(fp, "P3\n");
  fprintf(fp, "%u %u\n%hhu\n", L, H, cmax);
  for (i=0; i<H; i++)
    for (j=0; j<L; j++)
      fprintf(fp, "%hhu\n%hhu\n%hhu\n", g[i][j][0],g[i][j][1],g[i][j][2]);
  fclose(fp);
}
