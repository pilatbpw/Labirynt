
#include "labirynt.h"
#include "analiza_labiryntu.h"
#include "odczyt_labiryntu.h"
#include "poruszanie_znacznika.h"
#include "zapis_trasy.h"
#include "obsluga_argumentow.h"
#include "znalezienie_dowolnego_przejscia.h"
#include "odczyt_pliku_binarnego.h"
#define SCIEZKA_PLIKU_WYNIKOWEGO "wyniki/sciezka_rozwiazujaca_labirynt.txt"


void charakterystyka_poczatkowa_znacznika(struct Znacznik_typ* znacznik, struct Punkt_typ* punkt_startowy, struct ParametryLabiryntu_typ* parametry_labiryntu){
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
	
	
	char* sciezka_do_pliku=malloc(100);
	char* nazwa=malloc(50);
	
	char tryb=obsluga_argumentow(argc,argv, nazwa);
	sprintf(sciezka_do_pliku, "./dane/%s", nazwa);
	free(nazwa);
	

	
	if(tryb=='d'){
		FILE* wczytany_labirynt=fopen(sciezka_do_pliku,"r");
		if(wczytany_labirynt==NULL){
			fprintf(stdout,"BLAD: Blad wczytanego pliku\n");
			exit(1);
		}else{
			fprintf(stdout, "Wczytano poprawnie plik!\n");
		}
		free(sciezka_do_pliku);
		return znalezienie_dowolnego_przejscia(wczytany_labirynt);
	}
	else if(tryb=='k'){
		FILE* wczytany_labirynt=fopen(sciezka_do_pliku,"rb+");
		if(wczytany_labirynt==NULL){
			fprintf(stdout,"BLAD: Blad wczytanego pliku binarnego\n");
			exit(1);
		}else{
			fprintf(stdout, "Wczytano poprawnie plik binarny!\n");
		}
		free(sciezka_do_pliku);
		odczyt_pliku_binarnego(wczytany_labirynt);
	} 
	
	return 0;
}
