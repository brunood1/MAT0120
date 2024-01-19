#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// int conv(unsigned char ***A, float **B, int y, int x){
void conv(int height, int length, int width, int kernelSize, unsigned char (**A)[3], float B[kernelSize][kernelSize], int y, int x, int output[width]){
    int i, j, I, J;

    int s[3] = {0,0,0};
    int m = floor(kernelSize/2);
    int n = kernelSize - m;
    for (i = y-m ; i < y+n; i++){
        for (j = x-m; j < x+n; j++){
            if (i >= 0 && i < height && j >= 0 && j < length){
                I = i - (y-m);
                J = j - (x-m);
                s[0] += A[i][j][0] * B[I][J];
                s[1] += A[i][j][1] * B[I][J];
                s[2] += A[i][j][2] * B[I][J];
            }
        }
    }

    for (i = 0; i < 3; i++){
        output[i] = floor(s[i]);
    }


}

void main(){ // int argc, char **argv
    int i, j, l, h, L, H;
    unsigned char type, cmax, caractere;
    FILE *fp;

    // TROCAR NOME DO ARQUIVO AQUI
    fp = fopen("adam.ppm", "rb");
    while ((caractere=getc(fp))=='#')
        while((caractere=getc(fp))!='\n');
    ungetc(caractere,fp);

    fscanf(fp, "P%hhu\n", &type);
    while ((caractere=getc(fp))=='#')
        while((caractere=getc(fp))!='\n');
    ungetc(caractere,fp);

    fscanf(fp, "%u %u\n%hhu\n", &l, &h, &cmax);

    unsigned char (**imagem)[3];

    j=l*sizeof(char*);
    imagem = malloc(j);

    j=h*3;
    for (i=0; i<l; i++)
    imagem[i] = malloc(j);


    if(type==3){
    for(j=0; j<h; j++)
        for(i=0; i<l; i++)
            fscanf(fp, "%hhu %hhu %hhu", &imagem[i][j][0],&imagem[i][j][1],&imagem[i][j][2]);
    fclose(fp);
    }
    else if(type==6){
    for(j=0; j<h; j++)
        for(i=0; i<l; i++)
            fscanf(fp, "%c%c%c", &imagem[i][j][0],&imagem[i][j][1],&imagem[i][j][2]);
    fclose(fp);
    }       
    else{
    printf("Formato inválido!");
    fclose(fp);
    exit(0);
    }

    unsigned char (**blur)[3];
    j=h*sizeof(char*);
    blur = malloc(j);

    j=h*3;
    for (i=0; i<l; i++)
        blur[i] = malloc(j);

    int aux[3];
    float uniform[5][5];
    for (i = 0; i < 5; i++){
        for (j = 0; j < 5; j++){
            uniform[i][j] = 0.04;
        }
    }
    
    for (i = 0; i < h; i++){
        for (j = 0; j < l; j++){
            conv(h,l,3,5,imagem,uniform,i,j,aux);
            blur[i][j][0] = aux[0];
            blur[i][j][1] = aux[1];
            blur[i][j][2] = aux[2];
        }
    }

    // unsigned char edges[h][l][3];
    // for (i = 0; i < h; i++){
    //     for (j = 0; j < l; j++){
    //         for (k = 0; k < 3; k++){
    //             edges[i][j][k] = imagem[i][j][k] - blur[i][j][k];
    //         }
    //     }
    // }
    
    
    fp = fopen("blur.ppm", "w");
    fprintf(fp, "P6\n");
        fprintf(fp, "%u %u\n255\n", l, h);
        for (j=0;j<h;j++)
            for (i=0;i<l;i++)
                fprintf(fp,"%c%c%c", blur[i][j][0],blur[i][j][1],blur[i][j][2]);
        fclose(fp);

    // fp = fopen("edges.ppm", "w");
    // fprintf(fp, "P6\n");
    //     fprintf(fp, "%u %u\n255\n", l, h);
    //     for (j=0;j<h;j++)
    //         for (i=0;i<l;i++)
    //             fprintf(fp,"%c%c%c", edges[i][j][0],edges[i][j][1],edges[i][j][2]);
    //     fclose(fp);

}
