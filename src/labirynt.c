#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[]){
	if(argc!=2){
		fprintf(stdout,"BLAD: Podano bledna liczbe argumentow!\n");
		exit(1);
	}
	char* sciezka_do_pliku=malloc(100);
	sprintf(sciezka_do_pliku, "./dane/%s", argv[1]);
	FILE* wczytany_labirynt=fopen(sciezka_do_pliku,"r");
	if(wczytany_labirynt==NULL){
		fprintf(stdout,"BLAD: Blad wczytanego pliku\n");
		exit(1);
	}else{
		fprintf(stdout, "Wczytano poprawnie plik!\n");
	}
	
	free(sciezka_do_pliku);
	fclose(wczytany_labirynt);
	return 0;
	
}
