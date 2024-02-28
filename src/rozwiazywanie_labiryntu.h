#ifndef ROZWIAZYWANIE_LABIRYNTU
#define ROZWIAZYWANIE_LABIRYNTU
#include <stdio.h>
#include <stdlib.h>

void rozwiazywanie_labiryntu(struct ParametryLabiryntu_typ *parametry_labiryntu);
void otoczenie(int x, int y, FILE *plik, struct ParametryLabiryntu_typ *parametry_labiryntu);
#endif