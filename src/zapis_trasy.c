#include "zapis_trasy.h"

void zapis_przejscia_labiryntu(struct Znacznik_typ* znacznik, struct Punkt_typ* punkt_startowy, struct ParametryLabiryntu_typ* parametry_labiryntu){
	wyznaczenie_trasy(znacznik, punkt_startowy, parametry_labiryntu);
	FILE* plik=fopen("tmp/zapis_przejsc.txt", "w");
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
	char znak;
	while(okreslenie_aktualnego_bloku(znacznik, parametry_labiryntu) != 'K')
	{
		j=0;
		while(okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu) == 'O')
		{
			j++;
			ruch_do_przodu(znacznik);
		}
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
		zmiana_kierunku_znacznika('p', znacznik);
		znak=okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu);
		while(znak!='O' && znak!='K')
		{
			zmiana_kierunku_znacznika('l', znacznik);
			znak=okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu);
		}
		if(znak=='K')
		{
			break;
		}
	}
}
int ostateczna_trasa(struct Znacznik_typ* znacznik, struct ParametryLabiryntu_typ* parametry_labiryntu)
{
	char znak=okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu);
	ruch_do_przodu(znacznik);
	while(znak!='K')
	{
		znak=okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu);
		while(znak=='X' || znak=='P'){ 
			zmiana_kierunku_znacznika('l', znacznik);
			znak=okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu);
			//printf("1");
		}
		//printf("2");
		ruch_do_przodu(znacznik);
		if(znak=='K')
		{
			break;
		}
	}
	printf("3");
	return 0;
}
void wyznaczenie_trasy(struct Znacznik_typ* znacznik, struct Punkt_typ* punkt_startowy, struct ParametryLabiryntu_typ* parametry_labiryntu)
{
	FILE* maze = fopen("tmp/temp.txt", "r+");
	charakterystyka_poczatkowa_znacznika(znacznik, punkt_startowy, parametry_labiryntu);
	char znak = okreslenie_aktualnego_bloku(znacznik, parametry_labiryntu);
	char znak2;
	while(znak != 'K')
	{
		znak2=okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu);
		while(znak2=='X' || znak2=='P' || znak2=='O'){ //znak =='P' rozpatrywany jest po to, aby jesli znacznik zawroci na sam poczatek, nie wyszedl poza plansze
			zmiana_kierunku_znacznika('l', znacznik);
			znak2=okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu);
			//JESLI OBROCI SIE 3 RAZY TO ZNACZNY ZE JEST SLEPY ZAULEK!!! (notatka co do pozniejszego zaklejania slepych zaulkow)
		}
		ruch_do_przodu(znacznik);
		znak = okreslenie_aktualnego_bloku(znacznik, parametry_labiryntu);
		if(znak=='K')
		{
			break;
		}
		fseek(maze, (znacznik->x)+(parametry_labiryntu->c+1)*(znacznik->y), SEEK_SET);
		fputc('O', maze);
		switch(znak)
		{
			case ' ':
				break;
			case 'U':
				znacznik->kierunek = 'g';
				break;
			case 'D':
				znacznik->kierunek = 'd';
				break;
			case 'L':
				znacznik->kierunek = 'l';
				break;
			case 'R':
				znacznik->kierunek = 'p';
				break;
			default:
				exit(1);			
		}
	}
	fclose(maze);
}