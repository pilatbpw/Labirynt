#include "poruszanie_znacznika.h"

void zmiana_kierunku_znacznika(char skret, struct Znacznik_typ* znacznik){
	char kierunek= znacznik->kierunek;
	switch(skret){
		case 'l':
			
			switch(kierunek){
				case 'l':
					znacznik->kierunek='d';
					break;
				case 'p':
					znacznik->kierunek='g';
					break;
				case 'g':
					znacznik->kierunek='l';
					break;
				case 'd':
					znacznik->kierunek='p';
					break;
				default:
					fprintf(stdout, "BLAD: Nieznany kierunek: \'%c\'\n", kierunek);
					exit(1);
				
				
			}
			break;
		case 'p':
			switch(kierunek){
				case 'l':
					znacznik->kierunek='g';
					break;
				case 'p':
					znacznik->kierunek='d';
					break;
				case 'g':
					znacznik->kierunek='p';
					break;
				case 'd':
					znacznik->kierunek='l';
					break;
				default:
					fprintf(stdout, "BLAD: Nieznany kierunek: \'%c\'\n", kierunek);
					exit(1);
				
				
			}
			break;
		default:
			fprintf(stdout, "BLAD: Nieznany skret: \'%c\'\n", skret);
			exit(1);
		
	}
	
}

void ruch_do_przodu(struct Znacznik_typ* znacznik){
	char kierunek=znacznik->kierunek;
	switch(kierunek){
		case 'p':
			(znacznik->x)++;
			break;
		case 'l':
			(znacznik->x)--;
			break;
		case 'g':
			(znacznik->y)--;
			break;
		case 'd':
			(znacznik->y)++;
			break;
		
	}
	
}

int poruszanie_po_labiryncie(struct Znacznik_typ* znacznik, struct ParametryLabiryntu_typ* parametry_labiryntu){
	char zmienna_do_skasowania_potem=znacznik->kierunek; //TYLKO DLA KOMENTARZA W FINALNYM NALEZY TO SKASOWAC!!!
	zmiana_kierunku_znacznika('p', znacznik);
	char znak=okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu);
	while(znak=='X' || znak=='P'){ //znak =='P' rozpatrywany jest po to, aby jesli znacznik zawroci na sam poczatek, nie wyszedl poza plansze
		zmiana_kierunku_znacznika('l', znacznik);
		znak=okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu);
		//JESLI OBROCI SIE 3 RAZY TO ZNACZNY ZE JEST SLEPY ZAULEK!!! (notatka co do pozniejszego zaklejania slepych zaulkow)
		
	}
	//Ten fragment to tylko w ramach komentarza, zeby wiadomo bylo co sie dzieje ze znacznikiem:
	if(zmienna_do_skasowania_potem!=znacznik->kierunek){
		fprintf(stdout, "Zmiana kierunku! (\'%c\' -> \'%c\')\n", zmienna_do_skasowania_potem, znacznik->kierunek);
	}
		
	switch(znak){
		case 'X':
			fprintf(stdout, "BLAD: Brak mozliwosci poruszenia sie znacznika!\n");
			break;
		case ' ':
			ruch_do_przodu(znacznik);
			break;
		case 'K': //TEN CASE OZNACZA ZE MOZE NIE BYC WCALE POTRZEBNE ZAPISYWANIE ZMIENNEJ "punkt_koncowy" znajdujacej sie w analiza_labiryntu.c ROZWAZ TO!!!
			ruch_do_przodu(znacznik);
			fprintf(stdout, "ZNACZNIK DOSZEDL DO KONCA!\n");
			return 0; //0 oznacza ze doszedl do konca
			break;
		default:
			fprintf(stdout, "BLAD: Nieznany element labiryntu: \'%c\'\n", znak);
			exit(1);
		
	}
	return 1; //1 oznacza ze nie doszedl do konca
}
	
	
