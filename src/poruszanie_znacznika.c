
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

int poruszanie_po_labiryncie(struct Znacznik_typ* znacznik, struct ParametryLabiryntu_typ* parametry_labiryntu, FILE* plik){
	
	char znak_przed_znacznikiem=okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu, plik);
	
	if(ile_przejsc(znacznik, parametry_labiryntu,plik) == 1 && znak_przed_znacznikiem != 'P'&& znak_przed_znacznikiem!='K') 
	{
		zalepianie(znacznik, parametry_labiryntu,plik);
		//skrzyzowanie(znacznik, parametry_labiryntu);
		
	}
	else
	{
		char zmienna_do_skasowania_potem=znacznik->kierunek; //TYLKO DLA KOMENTARZA W FINALNYM NALEZY TO SKASOWAC!!!
		zmiana_kierunku_znacznika('p', znacznik);
		znak_przed_znacznikiem=okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu,plik);
		while(znak_przed_znacznikiem=='X' || znak_przed_znacznikiem=='P'){ //znak =='P' rozpatrywany jest po to, aby jesli znacznik zawroci na sam poczatek, nie wyszedl poza plansze
			zmiana_kierunku_znacznika('l', znacznik);
			znak_przed_znacznikiem=okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu,plik);
			//JESLI OBROCI SIE 3 RAZY TO ZNACZNY ZE JEST SLEPY ZAULEK!!! (notatka co do pozniejszego zaklejania slepych zaulkow)
		}
			//Ten fragment to tylko w ramach komentarza, zeby wiadomo bylo co sie dzieje ze znacznikiem:
		if(zmienna_do_skasowania_potem!=znacznik->kierunek){
			//fprintf(stdout, "Zmiana kierunku! (\'%c\' -> \'%c\')\n", zmienna_do_skasowania_potem, znacznik->kierunek);
		}
	}
	switch(znak_przed_znacznikiem){
		case 'X':
			
			break;
		case ' ':
		//case 'L':
		//case 'R':
		//case 'U':
		//case 'D':     
			ruch_do_przodu(znacznik);
			break;
		case 'K': //TEN CASE OZNACZA ZE MOZE NIE BYC WCALE POTRZEBNE ZAPISYWANIE ZMIENNEJ "punkt_koncowy" znajdujacej sie w analiza_labiryntu.c ROZWAZ TO!!!
			ruch_do_przodu(znacznik);
			fprintf(stdout, "ZNACZNIK DOSZEDL DO KONCA!\n");
			return 0; //0 oznacza ze doszedl do konca
			break;
		default:
			fprintf(stdout, "BLAD: Nieznany element labiryntu: \'%c\'\n", znak_przed_znacznikiem);
			exit(1);
	}

	return 1; //1 oznacza ze nie doszedl do konca
}
void zalepianie(struct Znacznik_typ* znacznik, struct ParametryLabiryntu_typ* parametry_labiryntu, FILE * plik)
{
    
    
    char znak2;
    while(ile_przejsc(znacznik, parametry_labiryntu, plik)==1)
    {
        zmiana_kierunku_znacznika('p', znacznik);
        znak2 = okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu,plik);
        while(znak2 == 'X' || znak2 == 'P' || znak2=='K')
        {
            zmiana_kierunku_znacznika('l', znacznik);
            znak2 = okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu, plik);
        }
        fseek(plik, (znacznik->x)+(parametry_labiryntu->c+1)*(znacznik->y), SEEK_SET);
        fputc('X', plik);
		//printf("Zalepiono: x=%d, y=%d\n", znacznik->x, znacznik->y);
        ruch_do_przodu(znacznik);
        
    }
    
}
/*void skrzyzowanie(struct Znacznik_typ* znacznik, struct ParametryLabiryntu_typ* parametry_labiryntu)
{
	FILE* maze = fopen("tmp/temp.txt", "r+");
	char znak = okreslenie_aktualnego_bloku(znacznik, parametry_labiryntu);
	char znak2;
	switch(znak){
		case ' ':
			znak2 = okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu);
			
			zmiana_kierunku_znacznika('p', znacznik);
			while(znak2 == 'X' || znak2 == 'P')
			{
				zmiana_kierunku_znacznika('l', znacznik);
				znak2 = okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu);
			}
			fseek(maze, (znacznik->x)+(parametry_labiryntu->c+1)*(znacznik->y), SEEK_SET);
			switch(znacznik->kierunek)
			{
				case 'l':
					fputc('L', maze);
					break;
				case 'p':
					fputc('R', maze);
					break;
				case 'g':
					fputc('U', maze);
					break;
				case 'd':
					fputc('D', maze);
					break;
				default:
					exit(1);
			}
			break;
		case 'U':
			znacznik->kierunek='l';
			znak2 = okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu);
			while(znak2 == 'X' || znak2 == 'P')
			{
				zmiana_kierunku_znacznika('l', znacznik);
				znak2 = okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu);
			}
			fseek(maze, (znacznik->x)+(parametry_labiryntu->c+1)*(znacznik->y), SEEK_SET);
			switch(znacznik->kierunek)
			{
				case 'l':
					fputc('L', maze);
					break;
				case 'p':
					fputc('R', maze);
					break;
				case 'g':
					fputc('U', maze);
					break;
				case 'd':
					fputc('D', maze);
					break;
				default:
					exit(1);
			}
			break;
		case 'D':
			znacznik->kierunek='p';
			znak2 = okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu);
			while(znak2 == 'X' || znak2 == 'P')
			{
				zmiana_kierunku_znacznika('l', znacznik);
				znak2 = okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu);
			}
			fseek(maze, (znacznik->x)+(parametry_labiryntu->c+1)*(znacznik->y), SEEK_SET);
			switch(znacznik->kierunek)
			{
				case 'l':
					fputc('L', maze);
					break;
				case 'p':
					fputc('R', maze);
					break;
				case 'g':
					fputc('U', maze);
					break;
				case 'd':
					fputc('D', maze);
					break;
				default:
					exit(1);
			}
			break;
		case 'L':
			znacznik->kierunek='d';
			znak2 = okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu);
			while(znak2 == 'X' || znak2 == 'P')
			{
				zmiana_kierunku_znacznika('l', znacznik);
				znak2 = okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu);
			}
			fseek(maze, (znacznik->x)+(parametry_labiryntu->c+1)*(znacznik->y), SEEK_SET);
			switch(znacznik->kierunek)
			{
				case 'l':
					fputc('L', maze);
					break;
				case 'p':
					fputc('R', maze);
					break;
				case 'g':
					fputc('U', maze);
					break;
				case 'd':
					fputc('D', maze);
					break;
				default:
					exit(1);
			}
			break;
		case 'R':
			znacznik->kierunek='g';
			znak2 = okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu);
			while(znak2 == 'X' || znak2 == 'P')
			{
				zmiana_kierunku_znacznika('l', znacznik);
				znak2 = okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu);
			}
			fseek(maze, (znacznik->x)+(parametry_labiryntu->c+1)*(znacznik->y), SEEK_SET);
			switch(znacznik->kierunek)
			{
				case 'l':
					fputc('L', maze);
					break;
				case 'p':
					fputc('R', maze);
					break;
				case 'g':
					fputc('U', maze);
					break;
				case 'd':
					fputc('D', maze);
					break;
				default:
					exit(1);
			}
			break;
		default:
			fprintf(stdout, "BLAD: Nieznany element labiryntu \'%c\'\n", znak);

	}
	fclose(maze);
}
*/


int ile_przejsc(struct Znacznik_typ* znacznik, struct ParametryLabiryntu_typ* parametry_labiryntu, FILE * plik)
{
	int j = 0;
	char znak;
	for(int i = 0; i<4; i++)
	{
		znak=okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu,plik);
		if(znak!= 'X' )
			j++;
		zmiana_kierunku_znacznika('l', znacznik);
	}
	return j;
}
	
	
