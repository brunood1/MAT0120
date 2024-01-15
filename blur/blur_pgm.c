#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// int conv(unsigned char ***A, float **B, int y, int x){
void conv(int height, int length, int width, int kernelSize, unsigned char A[height][length][width], float B[kernelSize][kernelSize], int y, int x, int output){
    int i, j, I, J;

    int s = 0;
    int m = floor(kernelSize/2);
    int n = kernelSize - m;
    for (i = y-m ; i < y+n; i++){
        for (j = x-m; j < y+n; j++){
            if (i >= 0 && i < height && j >= 0 && j < width){
                I = i - (y-m);
                J = j - (x-m);
                s += A[i][j] * B[I][J];
            }
        }
    }
    s = floor(s);
    output = s
}

void main(){
    int i, j, l, h, L, H;
    unsigned char type, cmax, caractere;
    FILE *fp;

    // TROCAR NOME DO ARQUIVO AQUI
    fp = fopen("adam.ppm", "r");
    while ((caractere=getc(fp))=='#')
        while((caractere=getc(fp))!='\n');
    ungetc(caractere,fp);

    fscanf(fp, "P%hhu\n", &type);
    while ((caractere=getc(fp))=='#')
        while((caractere=getc(fp))!='\n');
    ungetc(caractere,fp);

    fscanf(fp, "%u %u\n%hhu\n", &l, &h, &cmax);

    unsigned char imagem[h][l];


    // unsigned char (**imagem)[3];

    // j=l*sizeof(char*);
    // imagem = malloc(j);

    // j=h*3;
    // for (i=0; i<l; i++)
    // imagem[i] = malloc(j);


    if(type==2){
    for(i=0; i<h; i++)
      for(j=0; j<l; j++)
        fscanf(fp, "%hhd ", &g[i][j]);
    fclose(fp);
    }
    else if(type==5){
        for(i=0; i<h; i++)
        for(j=0; j<l; j++)
            fscanf(fp, "%c", &g[i][j]);
        fclose(fp);
    }       
    else{
        printf("Formato inválido!");
        fclose(fp);
        exit(0);
    }

    unsigned char blur[h][l];

    int aux[3];
    float uniform[5][5];
    for (i = 0; i < 5; i++){
        for (j = 0; j < 5; i++){
            uniform[i][j] = 1/25;
        }
    }
    
    for (i = 0; i < h; i++){
        for (j = 0; j < l; i++){
            conv(h,l,3,5,imagem,uniform,i,j,aux);
            blur[i][j] = aux;
        }
    }
    
    fp = fopen("blurC.ppm", "w");
    fprintf(fp, "P6\n");
        fprintf(fp, "%u %u\n255\n", L, H);
        for (j=0;j<H;j++)
            for (i=0;i<L;i++)
                fprintf(fp,"%c%c%c", blur[i][j][0],blur[i][j][1],blur[i][j][2]);
        fclose(fp);

}
