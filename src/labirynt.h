
#ifndef LABIRYNT_
#define LABIRYNT_
#include <stdio.h>
#include <stdlib.h>
#include "analiza_labiryntu.h"

struct Znacznik_typ{
	int x;
	int y;
	char kierunek;
	
};

void charakterystyka_poczatkowa_znacznika(struct Znacznik_typ* znacznik, struct Punkt_typ* punkt_startowy, struct ParametryLabiryntu_typ* parametry_labiryntu);

#endif
