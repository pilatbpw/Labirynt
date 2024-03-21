#include "analiza_labiryntu.h"


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

void okreslenie_poczatek_koniec_labiryntu(struct Punkt_typ* punkt_startowy, struct Punkt_typ* punkt_koncowy){
	FILE* plik=fopen("tmp/temp.txt", "r");
	
	char sprawdzany_znak=fgetc(plik);
	int aktualny_x=0;
	int aktualny_y=0;
	while(sprawdzany_znak!=EOF){
		if(sprawdzany_znak=='P'){
			punkt_startowy->x=aktualny_x;
			punkt_startowy->y=aktualny_y;
		}
		else if(sprawdzany_znak=='K'){
			punkt_koncowy->x=aktualny_x;
			punkt_koncowy->y=aktualny_y;
		}
		if(sprawdzany_znak=='\n'){
			aktualny_x=0;
			aktualny_y++;
		}else{
			aktualny_x++;
		}
		
		sprawdzany_znak=fgetc(plik);
	}
	fclose(plik);
}


void utworzenie_pliku_pomocniczego(FILE *plik, char* sciezka_pliku){
	rewind(plik);

	FILE *temp = fopen(sciezka_pliku, "w+");
	char znak;
	while((znak=fgetc(plik)) != EOF)
	{
		fprintf(temp, "%c", znak);
	}
	fclose(temp);
}

