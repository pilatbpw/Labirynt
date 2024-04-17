
#include "zapis_trasy.h"

void zapis_przejscia_labiryntu(struct Znacznik_typ* znacznik, struct Punkt_typ* punkt_startowy, struct ParametryLabiryntu_typ* parametry_labiryntu, FILE* plik_tmp, FILE* plik_wynikowy){
	wyznaczenie_trasy(znacznik, punkt_startowy, parametry_labiryntu, plik_tmp, plik_wynikowy);
	FILE* plik=fopen("wyniki/zapis_przejsc.txt", "w");
	charakterystyka_poczatkowa_znacznika(znacznik, punkt_startowy, parametry_labiryntu);
	
	int j = 0;
	char znak;
	while(okreslenie_aktualnego_bloku(znacznik, parametry_labiryntu, plik_tmp) != 'K')
	{
		zmiana_kierunku_znacznika('p', znacznik);
		znak=okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu, plik_tmp);
		while(znak!='*' && znak!='K')
		{
			zmiana_kierunku_znacznika('l', znacznik);
			znak=okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu, plik_tmp);
		}
		j=0;
		while(okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu, plik_tmp) == '*' || okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu, plik_tmp) == 'K')
		{
			j++;
			ruch_do_przodu(znacznik);
		}
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
		if(znak=='K')
			break;
		
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
		}
		ruch_do_przodu(znacznik);
		if(znak=='K')
		{
			break;
		}
	}
	return 0;
}
void wyznaczenie_trasy(struct Znacznik_typ* znacznik, struct Punkt_typ* punkt_startowy, struct ParametryLabiryntu_typ* parametry_labiryntu, FILE* plik_tmp, FILE* plik_wynikowy)
{
	charakterystyka_poczatkowa_znacznika(znacznik, punkt_startowy, parametry_labiryntu);
	char znak;
	while((znak = okreslenie_bloku_przed_znacznikiem(znacznik,parametry_labiryntu, plik_tmp)) != 'K')
	{
		zmiana_kierunku_znacznika('p',znacznik);
		znak = okreslenie_bloku_przed_znacznikiem(znacznik,parametry_labiryntu, plik_tmp);
		while(znak != ' ' && znak != '*'){ //znak =='P' rozpatrywany jest po to, aby jesli znacznik zawroci na sam poczatek, nie wyszedl poza plansze
			zmiana_kierunku_znacznika('l', znacznik);
			znak=okreslenie_bloku_przed_znacznikiem(znacznik, parametry_labiryntu, plik_tmp);
			if(znak=='K')
			{
				break;
			}
		}
		if(znak=='K')
		{
			break;
		}
		ruch_do_przodu(znacznik);

		if(znak == '*')
		{
			
		}
		else
		{
			fseek(plik_tmp, (znacznik->x)+(parametry_labiryntu->c+1)*(znacznik->y), SEEK_SET);
			fseek(plik_wynikowy, (znacznik->x)+(parametry_labiryntu->c+1)*(znacznik->y), SEEK_SET);
			fputc('*', plik_wynikowy);
			fputc('*', plik_tmp);
		}
		
		
	}
	fseek(plik_tmp, (znacznik->x)+(parametry_labiryntu->c+1)*(znacznik->y), SEEK_SET);
	fputc('*', plik_tmp);
	fseek(plik_wynikowy, (znacznik->x)+(parametry_labiryntu->c+1)*(znacznik->y), SEEK_SET);
	fputc('*', plik_wynikowy);
}