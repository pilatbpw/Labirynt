#include "odczyt_labiryntu.h"

char okreslenie_bloku_przed_znacznikiem(struct Znacznik_typ* znacznik, struct ParametryLabiryntu_typ* parametry_labiryntu, FILE * labirynt){
	
	int zmiana_linii=(parametry_labiryntu->c)+1;
	char kierunek= znacznik->kierunek;
	char znak;
	int przesuniecie_poczatkowe=(znacznik->x)+zmiana_linii*(znacznik->y);
	
	switch(kierunek){ // Sprawdzanie znaku w kierunku
		case 'p':
			fseek(labirynt, przesuniecie_poczatkowe+1, SEEK_SET);
			znak=fgetc(labirynt);
			break;
		case 'l':
			
			fseek(labirynt, przesuniecie_poczatkowe-1, SEEK_SET);
			
			znak=fgetc(labirynt);
			break;
		case 'g':
			fseek(labirynt, przesuniecie_poczatkowe-zmiana_linii, SEEK_SET);
			
			znak=fgetc(labirynt);
			break;
		case 'd':
			fseek(labirynt, przesuniecie_poczatkowe+zmiana_linii, SEEK_SET);
			
			znak=fgetc(labirynt);
			break;
		default:
			fprintf(stdout, "BLAD: Nie udało się poprawnie odczytać kierunku znacznika\n");
			exit(1);
	}
	fseek(labirynt, przesuniecie_poczatkowe, SEEK_SET);
	
	return znak;
	
}

char okreslenie_aktualnego_bloku(struct Znacznik_typ* znacznik, struct ParametryLabiryntu_typ* parametry_labiryntu, FILE* labirynt){ 
	
	char znak;
	fseek(labirynt, (znacznik->x)+(parametry_labiryntu->c+1)*(znacznik->y), SEEK_SET);
	znak = fgetc(labirynt);
	
	return znak;
}

	