
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
	//fprintf(stdout, "PORUSZYŁEM SIĘ HURRA!");
	
}

int poruszanie_po_labiryncie(struct Znacznik_typ* znacznik, struct ParametryLabiryntu_typ* parametry_labiryntu, FILE* plik){
	
	//fprintf(stdout, "ŻYJĘ!");
	char znak_przed_znacznikiem=okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu, plik);
	
	if(ile_przejsc(znacznik, parametry_labiryntu,plik) == 1 && znak_przed_znacznikiem != 'P'&& znak_przed_znacznikiem!='K') 
	{
		zalepianie(znacznik, parametry_labiryntu,plik);
	}
	else
	{
		zmiana_kierunku_znacznika('p', znacznik);
		znak_przed_znacznikiem=okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu,plik);
		while(znak_przed_znacznikiem=='X' || znak_przed_znacznikiem=='P'){ 
			zmiana_kierunku_znacznika('l', znacznik);
			znak_przed_znacznikiem=okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu,plik);
		}
	}
	switch(znak_przed_znacznikiem){
		case 'X':
			
			break;
		case ' ':  
			ruch_do_przodu(znacznik);
			break;
		case 'K': 
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
	
	
