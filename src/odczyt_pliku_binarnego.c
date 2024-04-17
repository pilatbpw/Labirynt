#include "odczyt_pliku_binarnego.h"
#include "znalezienie_dowolnego_przejscia.h"

void odczyt_pliku_binarnego(FILE* plik){
    FILE* przetlumaczony_plik_binarny=fopen("tmp/przetlumaczony_plik_binarny","w");
    unsigned int file_id;
    unsigned char escape;
    short int kolumny;
    short int rzedy;
    short int X_start;
    short int Y_start;
    short int X_koniec;
    short int Y_koniec;
    
    int licznik_slow_kodowych;
    int solution_offset;
    char separator;
    char sciana;
    char sciezka;
    printf("Sizeof UnsignedInt:%ld, Sizeof ShortInt:%ld, Sizeof Int:%ld, Sizeof LongInt:%ld\n",sizeof(unsigned int),sizeof(short int), sizeof(int),sizeof(long int));
    fread(&file_id, 4, 1, plik);
    fread(&escape,1,1,plik);
    fread(&kolumny, 2, 1, plik);
    fread(&rzedy, 2, 1, plik);
    fread(&X_start, 2, 1, plik);
    fread(&Y_start, 2, 1, plik);
    fread(&X_koniec, 2, 1, plik);
    fread(&Y_koniec, 2, 1, plik);
    fseek(plik, 12,SEEK_CUR);
    fread(&licznik_slow_kodowych, 4, 1, plik);
    fread(&solution_offset, 4, 1, plik);
    fread(&separator, 1, 1, plik);
    fread(&sciana, 1, 1, plik);
    fread(&sciezka, 1, 1, plik);
    fprintf(stdout,"Wielkosc:%ld\n", sizeof(escape));
    fprintf(stdout,"File_ID=0x%04X\nEscape:0x%0X \nKolumny:%d\nRzedy:%d\nX_start:%d\nY_start:%d\nX_koniec:%d\nY_koniec:%d\nLicznik_slow_kodowych:%d\nSolution_offset:%d\nSeparator:%c\nSciana:%c\nSciezka:%c\n", file_id,escape,kolumny,rzedy,X_start,Y_start,X_koniec,Y_koniec,licznik_slow_kodowych,solution_offset,separator,sciana,sciezka);
    fprintf(stdout,"\n");
    char znak;
    unsigned char liczba_znakow;
    int pozostale_znaki_w_linii=kolumny;
	int liczba_znakow_int;
    for(int i=licznik_slow_kodowych;i>0;i--){ // przetlumaczenie labiryntu z pliku binarnego do pliku tekstowego
       
        fseek(plik,1,SEEK_CUR);
        fread(&znak,1,1,plik);
        fread(&liczba_znakow,1,1,plik);
        liczba_znakow_int=(int)(liczba_znakow)+1;
        
        for(int k=0;k<liczba_znakow_int;k++){
            fprintf(przetlumaczony_plik_binarny,"%c", znak);
            pozostale_znaki_w_linii--;
            if(pozostale_znaki_w_linii<1){
                fprintf(przetlumaczony_plik_binarny,"\n");
                pozostale_znaki_w_linii=kolumny;
            }
            
        }
    }
    fseek(przetlumaczony_plik_binarny, (X_start-1)+((Y_start-1)*(kolumny+1)),SEEK_SET);
	fprintf(przetlumaczony_plik_binarny,"P");
	fseek(przetlumaczony_plik_binarny, (X_koniec-1)+((Y_koniec-1)*(kolumny+1)),SEEK_SET);
	fprintf(przetlumaczony_plik_binarny,"K");
    fclose(przetlumaczony_plik_binarny);
		
    fprintf(stdout,"\n");
    if(solution_offset!=0){
        fprintf(stdout, "Rozwiazanie zostalo zawarte w pliku binarnym\n");
        FILE * Rozwiazanie_z_pliku_binarnego=fopen("tmp/Rozwiazanie_z_pliku_binarnego", "w");
        unsigned int Solution_Id;
        short int Steps;
        fseek(plik, 43, SEEK_SET);
        fread(&Solution_Id,4,1,plik);
        fprintf(stdout, "Sol_ID: %i\n", Solution_Id);
        fseek(plik, 47, SEEK_SET);
        fread(&Steps, 1,1,plik);
        fprintf(stdout, "Steps: %i\n", Steps);
        char kierunek;
        unsigned char liczba_pol_do_przejscia;
        int liczba_pol_do_przejscia_int;
        fseek(plik, 48, SEEK_SET);
        for(int i=Steps;i>0;i--){ // przetlumaczenie rozwiazania labiryntu z pliku binarnego do pliku tekstowego
    
            
            fread(&kierunek,1, 1,plik);
            fread(&liczba_pol_do_przejscia,1,1,plik);
            liczba_pol_do_przejscia_int=(int)(liczba_pol_do_przejscia)+1;
            
            fprintf(Rozwiazanie_z_pliku_binarnego,"%c - %d\n", kierunek, liczba_pol_do_przejscia_int);
            
        }
    }
    else {
        FILE* maze=fopen("tmp/przetlumaczony_plik_binarny","r+");
        fprintf(stdout, "Rozwiazanie nie zostalo zawarte w pliku binarnym\n");
        znalezienie_dowolnego_przejscia(maze);
        fclose(maze);
        /*
        FILE * trasa = fopen("wyniki/zapis_przejsc.txt", "r");
        char linia[200];
        char direction[sizeof(char) *12];
        int steps=-1;
        int counter;
        while(fgets(linia, 200, trasa))
        {
            sscanf(linia, "%i - %s", &counter, direction);
            if(strcmp(direction, "RUCH_W_LEWO") == 0)
            {
                fputc((unsigned int)'W', plik);
            }
            if(strcmp(direction, "RUCH_W_PRAWO") == 0)
            {
                fputc((unsigned int)'E', plik);  
            }
            if(strcmp(direction, "RUCH_W_GORE") == 0)
            {
                fputc((unsigned int)'N', plik);
            }
            if(strcmp(direction, "RUCH_W_DOL") == 0)
            {
                fputc((unsigned int)'S', plik);
            }
            fseek(plik, 1, SEEK_CUR);
            fputc(counter, plik);
            steps++;
            fseek(plik, 1, SEEK_CUR);
        }
        fprintf(stdout, "3");
        if(steps > 0)
        {
            fseek(plik, 33,SEEK_SET);
            fwrite("1", 4, 1, plik);
            fseek(plik, 48, SEEK_SET);

            fseek(plik, 47, SEEK_SET);
            fprintf(stdout, "steps: %i", steps);
            //fputc(steps, plik);
            fwrite(&steps, 1, 1, plik);
            fseek(plik, 43, SEEK_SET);
            //fputc(1, plik);
            fwrite("1", 4, 1, plik);
        }
        fclose(trasa);
        */
    }
}
    
