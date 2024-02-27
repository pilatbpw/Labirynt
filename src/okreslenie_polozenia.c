#include "okreslenie_polozenia.h"

void okreslenie_parametrow_labiryntu(FILE *plik, struct ParametryLabiryntu_typ *parametry_labiryntu){
	
	int licznik_c=0;
	int licznik_r=1;
	char sprawdzany_znak=fgetc(plik);
	
	if (sprawdzany_znak==EOF){
		fprintf(stdout, "BLAD: Wczytany plik jest pusty\n");
		exit(1);
	}
	while(sprawdzany_znak!='\n' && sprawdzany_znak!=EOF){
		licznik_c++;
		sprawdzany_znak=fgetc(plik);
		
	}
	char* linia=malloc(sizeof(char)*(licznik_c +2));
	
	while(fgets(linia,licznik_c+2,plik)!=NULL){
		licznik_r++;
	}
	parametry_labiryntu->r=licznik_r;
	parametry_labiryntu->c=licznik_c;
	free(linia);
	
}