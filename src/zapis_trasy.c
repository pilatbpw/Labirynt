
#include "zapis_trasy.h"

void zapis_przejscia_labiryntu(struct Znacznik_typ* znacznik, struct Punkt_typ* punkt_startowy, struct ParametryLabiryntu_typ* parametry_labiryntu, FILE* plik_tmp, FILE* plik_wynikowy){
	//printf("Weszlo w zapis_przejsc\n");
	wyznaczenie_trasy(znacznik, punkt_startowy, parametry_labiryntu, plik_tmp, plik_wynikowy);
	//printf("Udalo sie wyznaczyc trase\n");
	FILE* plik=fopen("wyniki/zapis_przejsc.txt", "w");
	charakterystyka_poczatkowa_znacznika(znacznik, punkt_startowy, parametry_labiryntu);
	/*
	while(ostateczna_trasa(znacznik, parametry_labiryntu)){
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
		*/
	int j = 0;
	char znak=okreslenie_bloku_przed_znacznikiem(znacznik,parametry_labiryntu,plik_tmp);
	while(znak != 'K' && znak!='\n')
	{	
		
		j=0;
		while(znak == '*' || znak == 'K')
		{
			
			//printf("Weszlo w drugie while\n");
			j++;
			ruch_do_przodu(znacznik);
			//printf("j=%d\n",j);
			znak=okreslenie_bloku_przed_znacznikiem(znacznik,parametry_labiryntu, plik_tmp);
			//printf("Znacznik w while: x=%d, y=%d, kierunek=%c, znak:%c\n", znacznik->x, znacznik->y, znacznik->kierunek, znak);
		}
		//printf("Wyszlo z drugiego while\n");
		if(j==0)
		{
			switch(znacznik->kierunek)
			{
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
					fprintf(stdout, "BLAD: Nieznany kierunek znacznika \'%c\'\n", znacznik->kierunek);
					exit(1);
			}
		}
		else
		{
			switch(znacznik->kierunek)
			{
				case 'p':
					fprintf(plik, "%d - RUCH_W_PRAWO\n", j);
					break;
				case 'l':
					fprintf(plik, "%d - RUCH_W_LEWO\n", j);
					break;
				case 'g':
					fprintf(plik, "%d - RUCH_W_GORE\n", j);
					break;
				case 'd':
					fprintf(plik, "%d - RUCH_W_DOL\n", j);
					break;
				default:
					fprintf(stdout, "BLAD: Nieznany kierunek znacznika \'%c\'\n", znacznik->kierunek);
					exit(1);
			}
		}
		if(znak=='K' || znak=='\n')
		{
			printf("K!!!!\n");
			break;
		}
		zmiana_kierunku_znacznika('p', znacznik);
		znak=okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu, plik_tmp);
		while(znak!='*' && znak!='K')
		{
			zmiana_kierunku_znacznika('l', znacznik);
			znak=okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu, plik_tmp);
		}
		znak=okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu, plik_tmp);
		
		//printf("Pelne while");
		//printf("Pozycja znacznika: x:%d, y:%d\n", znacznik->x, znacznik->y);
	}
}
int ostateczna_trasa(struct Znacznik_typ* znacznik, struct ParametryLabiryntu_typ* parametry_labiryntu, FILE *plik_tmp)
{
	char znak=okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu, plik_tmp);
	ruch_do_przodu(znacznik);
	while(znak!='K')
	{
		znak=okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu, plik_tmp);
		while(znak=='X' || znak=='P'){ 
			zmiana_kierunku_znacznika('l', znacznik);
			znak=okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu, plik_tmp);
			//printf("1");
		}
		//printf("2");
		ruch_do_przodu(znacznik);
		if(znak=='K')
		{
			break;
		}
	}
	//printf("3"); // CO TO TU ROBI?
	return 0;
}
void wyznaczenie_trasy(struct Znacznik_typ* znacznik, struct Punkt_typ* punkt_startowy, struct ParametryLabiryntu_typ* parametry_labiryntu, FILE* plik_tmp, FILE* plik_wynikowy)
{
	//printf("weszlo w wyznaczanie trasy\n");
	
	charakterystyka_poczatkowa_znacznika(znacznik, punkt_startowy, parametry_labiryntu);
	//printf("Charakterystyka udana\n");
	char znak = okreslenie_bloku_przed_znacznikiem(znacznik,parametry_labiryntu, plik_tmp);
	
	
	while(znak != 'K')
	{
		
		//printf("Pozycja to x:%d, y:%d\n", znacznik->x, znacznik->y);
		zmiana_kierunku_znacznika('p',znacznik);
		znak = okreslenie_bloku_przed_znacznikiem(znacznik,parametry_labiryntu, plik_tmp);
		while(znak=='X'){ //znak =='P' rozpatrywany jest po to, aby jesli znacznik zawroci na sam poczatek, nie wyszedl poza plansze
			//printf("ZNAK PRZED TO X!!!\n");
			zmiana_kierunku_znacznika('l', znacznik);
			znak=okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu, plik_tmp);
			//JESLI OBROCI SIE 3 RAZY TO ZNACZNY ZE JEST SLEPY ZAULEK!!! (notatka co do pozniejszego zaklejania slepych zaulkow)
		}
		ruch_do_przodu(znacznik);
		znak = okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu, plik_tmp);
		//printf("x:%d, y:%d, kierunek:%c, znak:%c \n", znacznik->x, znacznik->y, znacznik->kierunek, znak);
		if(znak=='K'|| znak=='\n')
		{
			//printf("Doszedl do konca wyjscie z wyznaczania trasy\n");
			break;
			
		}
		fseek(plik_tmp, (znacznik->x)+(parametry_labiryntu->c+1)*(znacznik->y), SEEK_SET);
		fseek(plik_wynikowy, (znacznik->x)+(parametry_labiryntu->c+1)*(znacznik->y), SEEK_SET);
		
		fputc('*', plik_wynikowy);
		fputc('*', plik_tmp);
		//printf("Gwiazdka postawiona w: x=%d, y=%d\n", znacznik->x,znacznik->y);
		
	}
	fseek(plik_tmp, (znacznik->x)+(parametry_labiryntu->c+1)*(znacznik->y), SEEK_SET);
		fseek(plik_wynikowy, (znacznik->x)+(parametry_labiryntu->c+1)*(znacznik->y), SEEK_SET);
		
		fputc('*', plik_wynikowy);
		fputc('*', plik_tmp);
		//printf("Postawiono *\n");
	
}
