#include "labirynt.h"
#include "analiza_labiryntu.h"
#include "odczyt_labiryntu.h"

void scharakteryzowanie_znacznika(struct Znacznik_typ* znacznik, struct Punkt_typ* punkt_startowy, struct ParametryLabiryntu_typ* parametry_labiryntu){
	znacznik->x=punkt_startowy->x;
	znacznik->y=punkt_startowy->y;
	
	if(znacznik->x==0 && znacznik->y!=0 && znacznik->y!=((parametry_labiryntu->r)-1)){
		znacznik->kierunek='p';
	} else if(znacznik->x==((parametry_labiryntu->c)-1) && znacznik->y!=0 && znacznik->y!=((parametry_labiryntu->r)-1)){
		znacznik->kierunek='l';
	} else if(znacznik->y==0 && znacznik->x!=0 && znacznik->x!=((parametry_labiryntu->c)-1)){
		znacznik->kierunek='d';
	} else if(znacznik->y==((parametry_labiryntu->r)-1) && znacznik->x!=0 && znacznik->x!=((parametry_labiryntu->c)-1)){
		znacznik->kierunek='g';
	} else{
		fprintf(stdout, "BLAD: Labirynt blednie skonstruowany (poczatek labiryntu znajduje sie w niepoprawnym miejscu)\n");
	}
		
	
	
}

int main(int argc, char* argv[]){
	if(argc!=2){
		fprintf(stdout,"BLAD: Podano bledna liczbe argumentow!\n");
		exit(1);
	}
	char* sciezka_do_pliku=malloc(100);
	sprintf(sciezka_do_pliku, "./dane/%s", argv[1]);
	FILE* wczytany_labirynt=fopen(sciezka_do_pliku,"r");
	if(wczytany_labirynt==NULL){
		fprintf(stdout,"BLAD: Blad wczytanego pliku\n");
		exit(1);
	}else{
		fprintf(stdout, "Wczytano poprawnie plik!\n");
	}
	
	struct ParametryLabiryntu_typ *parametry_labiryntu;
	parametry_labiryntu=malloc(sizeof(struct ParametryLabiryntu_typ));
	okreslenie_parametrow_labiryntu(wczytany_labirynt,parametry_labiryntu);
	
	fprintf(stdout, "Liczba wierszy labiryntu: %d\nLiczba kolumn labiryntu: %d\n", parametry_labiryntu->r, parametry_labiryntu->c);
	
	
	utworzenie_pliku_pomocniczego(wczytany_labirynt, parametry_labiryntu);
	free(sciezka_do_pliku);
	fclose(wczytany_labirynt);
	
	struct Punkt_typ* punkt_startowy=malloc(sizeof(struct Punkt_typ));
	struct Punkt_typ* punkt_koncowy=malloc(sizeof(struct Punkt_typ));
	
	okreslenie_poczatek_koniec_labiryntu(punkt_startowy, punkt_koncowy);
	
	fprintf(stdout, "Poczatek labiryntu znajduje sie w punkcie P(%d,%d)\nKoniec labiryntu znajduje sie w punkcie K(%d,%d)\n",punkt_startowy->x,punkt_startowy->y,punkt_koncowy->x,punkt_koncowy->y);
	
	struct Znacznik_typ* znacznik=malloc(sizeof(struct Znacznik_typ));
	
	scharakteryzowanie_znacznika(znacznik, punkt_startowy, parametry_labiryntu);
	
	fprintf(stdout, "Charakterystyka znacznika na poczatku:\nx=%d, y=%d, kierunek=%c\n", znacznik->x,znacznik->y, znacznik->kierunek);
	
	fprintf(stdout, "Znak przed znacznikiem to: \"%c\"\n", okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu));
	
	
	return 0;
	
}

