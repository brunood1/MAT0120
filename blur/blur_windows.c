#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// int conv(unsigned char ***A, float **B, int y, int x){
void conv(int height, int length, int width, int kernelSize, unsigned char A[height][length][width], float B[kernelSize][kernelSize], int y, int x, int output[width]){
    int i, j, I, J;

    float s[3] = {0,0,0};
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
    int i, j, k, l, h, L, H;
    unsigned char type, caractere;
    unsigned int cmax, r, g, b;
    FILE *fp;

    // TROCAR NOME DO ARQUIVO AQUI
    fp = fopen("turtle.ppm", "rb");
    // we need to use BINARY READING FORMATS, for two reasons:
    // a. it seems netpbm specifies the line feeds in its files must be plain LF
    // b. in raw formats, you may get a 0x10 (i.e. LF) character, you don't want that becoming CRLF and ruining your life

    // while ((caractere=getc(fp))=='#')
    //    while((caractere=getc(fp))!='\n');
    // ungetc(caractere,fp);
    // by its definition, comments can't come before the P3, P6, as it is its magic number

    fscanf(fp, "P%hhu\n", &type); //technically it accepts any whitespace. correct would be probably "P%hhu " (spaces important)

    printf("image type: %hhu\n", type);


    while ((caractere=getc(fp))=='#')
        while((caractere=getc(fp))!='\n');
    ungetc(caractere,fp);

    fscanf(fp, "%u %u\n%hhu\n", &l, &h, &cmax); //technically it accepts any whitespace. correct would be probably "%u %u %hhu " (spaces important)
    printf("image is %i x %i\n", l, h);

    unsigned char imagem[h][l][3];

    if(type==3){
        for(j=0; j<h; j++) {
            for(i=0; i<l; i++){
                fscanf(fp, "%u %u %u", &r, &g, &b);
                imagem[j][i][0] = (unsigned char) r;
                imagem[j][i][1] = (unsigned char) g;
                imagem[j][i][2] = (unsigned char) b;
            }
        }
        fclose(fp);
    }
    else if(type==6){
        for(j=0; j<h; j++)
            for(i=0; i<l; i++)
                fscanf(fp, "%c%c%c", &imagem[j][i][0],&imagem[j][i][1],&imagem[j][i][2]);
        fclose(fp);
    }
    else{
        printf("Formato inválido!");
        fclose(fp);
        exit(0);
    }

    unsigned char (**blur)[3];
    blur = calloc(h, sizeof(char*)); // this is equivalent, just more readable imo

    for (i=0; i<h; i++)
        blur[i] = calloc(l * 3, sizeof(char)); // this isnt't though

    printf("blur allocated\n");


    int aux[3];
    float uniform[5][5];    
    for (i = 0; i < 5; i++){
        for (j = 0; j < 5; j++){
            uniform[i][j] = 0.04f;
        }
    }

    printf("uniform made\n");


    for (i = 0; i < h; i++){
        for (j = 0; j < l; j++){
            conv(h,l,3,5,imagem,uniform,i,j,aux);
            printf("x: %i, y: %i\n", j, i);

            blur[i][j][0] = aux[0];
            blur[i][j][1] = aux[1];
            blur[i][j][2] = aux[2];
        }
    }

    unsigned char edges[h][l][3];
    for (i = 0; i < h; i++){
        for (j = 0; j < l; j++){
            for (k = 0; k < 3; k++){
                edges[i][j][k] = imagem[i][j][k] - blur[i][j][k];
            }
        }
    }

    fp = fopen("blur.ppm", "wb");
    fprintf(fp, "P6\n");
    fprintf(fp, "%u %u\n255\n", l, h);
    for (j=0;j<h;j++) {
        for (i=0;i<l;i++)
            fprintf(fp,"%c%c%c", blur[j][i][0],blur[j][i][1],blur[j][i][2]); //inverted j and i
    }
    fclose(fp);

    fp = fopen("edges.ppm", "wb");
    fprintf(fp, "P6\n");
    fprintf(fp, "%u %u\n255\n", l, h);
    for (j=0;j<h;j++) {
        for (i=0;i<l;i++)
            fprintf(fp,"%c%c%c", edges[j][i][0],edges[j][i][1],edges[j][i][2]); // inverted j and i
    }
    fclose(fp);

}
