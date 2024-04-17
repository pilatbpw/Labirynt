#include "znalezienie_dowolnego_przejscia.h"
#include "labirynt.h"
#include "analiza_labiryntu.h"
#include "odczyt_labiryntu.h"
#include "poruszanie_znacznika.h"
#include "zapis_trasy.h"
#include "obsluga_argumentow.h"
#include "znalezienie_dowolnego_przejscia.h"
#define SCIEZKA_PLIKU_WYNIKOWEGO "wyniki/sciezka_rozwiazujaca_labirynt.txt"

int znalezienie_dowolnego_przejscia(FILE* wczytany_labirynt){
struct ParametryLabiryntu_typ *parametry_labiryntu;
	parametry_labiryntu=malloc(sizeof(struct ParametryLabiryntu_typ));
	okreslenie_parametrow_labiryntu(wczytany_labirynt,parametry_labiryntu);
	
	fprintf(stdout, "Liczba wierszy labiryntu: %d\nLiczba kolumn labiryntu: %d\n", parametry_labiryntu->r, parametry_labiryntu->c);
	
	
	utworzenie_pliku_pomocniczego(wczytany_labirynt, "tmp/temp");
	utworzenie_pliku_pomocniczego(wczytany_labirynt, SCIEZKA_PLIKU_WYNIKOWEGO);
	FILE* tmp = fopen("tmp/temp", "r+");
	FILE* plik_wynikowy = fopen(SCIEZKA_PLIKU_WYNIKOWEGO, "r+");
	

	fclose(wczytany_labirynt);
	
	struct Punkt_typ* punkt_startowy=malloc(sizeof(struct Punkt_typ));
	struct Punkt_typ* punkt_koncowy=malloc(sizeof(struct Punkt_typ));
	
	okreslenie_poczatek_koniec_labiryntu(punkt_startowy, punkt_koncowy);
	
	fprintf(stdout, "Poczatek labiryntu znajduje sie w punkcie P(%d,%d)\nKoniec labiryntu znajduje sie w punkcie K(%d,%d)\n",punkt_startowy->x,punkt_startowy->y,punkt_koncowy->x,punkt_koncowy->y);
	
	struct Znacznik_typ* znacznik=malloc(sizeof(struct Znacznik_typ));
	
	charakterystyka_poczatkowa_znacznika(znacznik, punkt_startowy, parametry_labiryntu);
	
	fprintf(stdout, "Charakterystyka znacznika na poczatku:\nx=%d, y=%d, kierunek=%c\n", znacznik->x,znacznik->y, znacznik->kierunek);

	while(poruszanie_po_labiryncie(znacznik, parametry_labiryntu, tmp)){
		
	}
	zapis_przejscia_labiryntu(znacznik, punkt_startowy, parametry_labiryntu, tmp, plik_wynikowy);
	fprintf(stdout, "Udalo sie utworzyc zapis przejsc!\n");
	fclose(tmp);
	fclose(plik_wynikowy);
	
	return 0;
}