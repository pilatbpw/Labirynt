
#ifndef ZAPIS_TRASY
#define ZAPIS_TRASY
#include "labirynt.h"

#include "poruszanie_znacznika.h"

void zapis_przejscia_labiryntu(struct Znacznik_typ* znacznik, struct Punkt_typ* punkt_startowy, struct ParametryLabiryntu_typ* parametry_labiryntu, FILE* plik_tmp, FILE* plik_wynikowy);
int ostateczna_trasa(struct Znacznik_typ* znacznik, struct ParametryLabiryntu_typ* parametry_labiryntu, FILE* plik_tmp);
void wyznaczenie_trasy(struct Znacznik_typ* znacznik, struct Punkt_typ* punkt_startowy, struct ParametryLabiryntu_typ* parametry_labiryntu, FILE* plik_tmp, FILE* plik_wynikowy);


#endif
