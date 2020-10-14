#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// Para usar strings

// SOIL é a biblioteca para leitura das imagens
#include "SOIL.h"

// Um pixel RGB
typedef struct {
    unsigned char r, g, b;
} RGB;

// Uma imagem em RGB
typedef struct {
    int width, height;
    RGB* img;
} Img;

// Protótipos
void load(char* name, Img* pic);
unsigned char changeToGray(r,g,b);
char changeToASC(int collor);

// Carrega uma imagem para a struct Img
void load(char* name, Img* pic)
{
    int chan;
    pic->img = (unsigned char*) SOIL_load_image(name, &pic->width, &pic->height, &chan, SOIL_LOAD_RGB);
    if(!pic->img)
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
        exit(1);
    }
    printf("Load: %d x %d x %d\n", pic->width, pic->height, chan);
}

unsigned char changeToGray(r,g,b)
{
	unsigned char i = (0.3*r + 0.59*g +0.11*b);
	return i;
}

char changeToASC(int color)
{
	char map[10]=" .,:;ox%#@";
	// 255/10 = 25,5 então arrendondando para steps de 25

	if(color == 255){
		return map[10];
	}
	else if(color >= 225){
		return map[9];
	}
	else if(color >= 200 && color < 225){
		return map[8];
	}
	else if(color >= 175 && color < 200){
		return map[7];
	}
	else if(color >= 150 && color < 175){
		return map[6];
	}
	else if(color >= 125 && color < 150){
		return map[5];
	}
	else if(color >= 100 && color < 125){
		return map[4];
	}
	else if(color >= 75 && color < 100){
		return map[3];
	}
	else if(color >= 50 && color < 75){
		return map[2];
	}
	else if(color >= 25 && color < 50 ){
		return map[1];
	}
	else{
		return map[0];
	} 
}

int main(int argc, char** argv)
{
	int reduction;

    Img pic;
    if(argc == 1) {
        printf("loader [img]\n");
        exit(1);
    }
    load(argv[1], &pic);

    //printf("Primeiros 10 pixels da imagem:\n");
     //for(int i=0; i<10; i++) {
     //    printf("[%d %d %d] ", pic.img[i].r, pic.img[i].g, pic.img[i].b);
     //}
     //printf("\n");
	printf("pixeis:[%d] " ,sizeof(pic.img));
	//printf("altura:[%d] e comprimento:[%d] " ,pic.width,pic.height);

	
	

    // Inverte as cores
    //for(int i=0; i<pic.width*pic.height; i++) {
    //    pic.img[i].r = 255 - pic.img[i].r;
    //   pic.img[i].g = 255 - pic.img[i].g;
    //  pic.img[i].b = 255 - pic.img[i].b;
    //}

	// tranforma em tons de cinza

	printf("digite um fator de redução\n");
	scanf("%d",&reduction);

	


	for(int i=0; i<pic.width*pic.height; i++) 
	{
		unsigned char gray; 
		gray = changeToGray(pic.img[i].r, pic.img[i].g, pic.img[i].b);
		pic.img[i].r = gray;
    	pic.img[i].g = gray;
    	pic.img[i].b = gray;
	}

	int l;
	if(reduction == 50){
		for(int i=0; i<pic.height; i=i+2){
			for(int j=0; j<pic.width; j=j+2){
				pic.img[l].r = pic.img[i*(pic.width) + j].r;
				pic.img[l].b = pic.img[i*(pic.width) + j].b;
				pic.img[l].g = pic.img[i*(pic.width) + j].g;
				l++;
			}
		}
	}

	
	/*int cont = 0;
	unsigned char x;
	unsigned char grey = 0;
	int l = 0;
	int c = 0;
	int matrix[pic.height][pic.width];
	if(reduction == 50){
		for(int i=0; i<pic.height; i=i+2){
			for(int j=0; j<pic.width; j=j+2){
			//if(j >= pic.width ){
			//	cont = cont + (pic.width/2);
			//}
			grey = (pic.img[i].r + pic.img[i+1].r + pic.img[i+pic.width].r + pic.img[i+pic.width + 1].r)/4;
			//grey += pic.img[i+1].r;
			//gray = grey/510;
			pic.img[j].r = grey;
			pic.img[j].g = grey;
			pic.img[j].b = grey;
			pic.img[j+1].r = grey;
			pic.img[j+1].g = grey;
			pic.img[j+1].b = grey;
			pic.img[j + i*pic.width].r = grey;
			pic.img[j + i*pic.width].g = grey;
			pic.img[j + i*pic.width].b = grey;

			pic.img[(j+1) + i*pic.width].r = grey;
			pic.img[(j+1) + i*pic.width].g = grey;
			pic.img[(j+1) + i*pic.width].b = grey;
			
			matrix[l][c] = grey;
			
			if(c >= pic.width/2){
				l++;
				c = 0;
			}

			c++;
			}
		}
	}
	*/


    // Exemplo: gravando um arquivo de saída com a imagem (não é necessário para o trabalho, apenas
    // para ver o resultado intermediário, por ex, da conversão para tons de cinza)
    SOIL_save_image("out.bmp", SOIL_SAVE_TYPE_BMP, pic.width/2, pic.height/2,
        3, (const unsigned char*) pic.img);


    // Exemplo: gravando um arquivo saida.html
    FILE* arq = fopen("saida.html", "w"); // criar o arquivo: w
    if(arq == NULL) // 0, falso
    {
        printf("Erro abrindo arquivo de saída\n");
        exit(1);
    }

    fprintf(arq, "<html>\n");
    fprintf(arq,"<head>\n");
    fprintf(arq,"</head>\n");
    fprintf(arq,"<body style=\"background:black;\" leftmargin=0; topmargin=0 >");
    fprintf(arq,"<style> pre { color: white; font-family:Courier; font-size:8px; letter-spacing:1px}</style>");
	fprintf(arq,"<pre>");
	for(int i=0; i<pic.height; i++) 
	{
		
		for(int j=0; j<pic.width; j++) 
		{
			
			// podemos passar qualquer parametro, pois eles são iguais
			// multiplico o i pela altura para ter a linha e é somado com a largura 
			fprintf(arq,"%c", changeToASC(pic.img[(i*pic.width) +j].r));
		}
		fprintf(arq,"<br>");
	}
	fprintf(arq,"</pre>");
	
    fprintf(arq,"</body>\n");
	fprintf(arq, "</html>\n");

    fclose(arq);
    free(pic.img);
}
