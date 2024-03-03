#include "zapis_trasy.h"

void zapis_przejscia_labiryntu(struct Znacznik_typ* znacznik, struct Punkt_typ* punkt_startowy, struct ParametryLabiryntu_typ* parametry_labiryntu){
	charakterystyka_poczatkowa_znacznika(znacznik, punkt_startowy, parametry_labiryntu);
	FILE* plik=fopen("tmp/zapis_przejsc.txt", "w");
	char kierunek;
	while(poruszanie_po_labiryncie(znacznik, parametry_labiryntu)){
		kierunek=znacznik->kierunek;
		switch(kierunek){
			case 'p':
				fprintf(plik, "RUCH_W_PRAWO\n");
				break;
			case 'l':
				fprintf(plik, "RUCH_W_LEWO\n");
				break;
			case 'g':
				fprintf(plik, "RUCH_W_GORE\n");
				break;
			case 'd':
				fprintf(plik, "RUCH_W_DOL\n");
				break;
			default:
				fprintf(stdout, "BLAD: Nieznany kierunek znacznika \'%c\'\n", kierunek);
				exit(1);
			
			
		}
	}
	//DODATKOWA ITERACJA ZEBY POKAZYWALO ZE DOSZLO DO KONCA
	kierunek=znacznik->kierunek;
		switch(kierunek){
			case 'p':
				fprintf(plik, "RUCH_W_PRAWO\n");
				break;
			case 'l':
				fprintf(plik, "RUCH_W_LEWO\n");
				break;
			case 'g':
				fprintf(plik, "RUCH_W_GORE\n");
				break;
			case 'd':
				fprintf(plik, "RUCH_W_DOL\n");
				break;
			default:
				fprintf(stdout, "BLAD: Nieznany kierunek znacznika \'%c\'\n", kierunek);
				exit(1);
			
			
		}
}