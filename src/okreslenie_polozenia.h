#ifndef OKRESLENIE_POLOZENIA
#define OKRESLENIE_POLOZENIA
#include <stdio.h>
#include <stdlib.h>
struct ParametryLabiryntu_typ{
	int c; //liczba kolumn
	int r; //liczba rzedow
	
};

void okreslenie_parametrow_labiryntu(FILE *plik, struct ParametryLabiryntu_typ *parametry_labiryntu);
void utworzenie_pliku_pomocniczego(FILE *plik, struct ParametryLabiryntu_typ *parametry_labiryntu);
#endif