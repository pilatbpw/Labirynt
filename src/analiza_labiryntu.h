#ifndef OKRESLENIE_POLOZENIA
#define OKRESLENIE_POLOZENIA
#include <stdio.h>
#include <stdlib.h>
struct ParametryLabiryntu_typ{
	int c; //liczba kolumn
	int r; //liczba rzedow
	
};

struct Punkt_typ{
	int x;
	int y;
};

void okreslenie_parametrow_labiryntu(FILE *plik, struct ParametryLabiryntu_typ *parametry_labiryntu);
void utworzenie_pliku_pomocniczego(FILE *plik, struct ParametryLabiryntu_typ *parametry_labiryntu);
void okreslenie_poczatek_koniec_labiryntu(struct Punkt_typ* punkt_startowy, struct Punkt_typ* punkt_koncowy);
#endif