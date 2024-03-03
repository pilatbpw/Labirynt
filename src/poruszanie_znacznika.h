#ifndef PORUSZANIE_ZNACZNIKA
#define PORUSZANIE_ZNACZNIKA

#include "odczyt_labiryntu.h"
#include "analiza_labiryntu.h"
#include "labirynt.h"

void zmiana_kierunku_znacznika(char skret, struct Znacznik_typ* znacznik);
void ruch_do_przodu(struct Znacznik_typ* znacznik);
int poruszanie_po_labiryncie(struct Znacznik_typ* znacznik, struct ParametryLabiryntu_typ* parametry_labiryntu);

#endif