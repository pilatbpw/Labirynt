#ifndef ODCZYT_LABIRYNTU
#define ODCZYT_LABIRYNTU

#include <stdio.h>
#include <stdlib.h>
#include "labirynt.h"
#include "analiza_labiryntu.h"

char okreslenie_bloku_przed_znacznikiem(struct Znacznik_typ* znacznik, struct ParametryLabiryntu_typ* parametry_labiryntu, FILE * plik);
char okreslenie_aktualnego_bloku(struct Znacznik_typ* znacznik, struct ParametryLabiryntu_typ* parametry_labiryntu, FILE * plik);



#endif