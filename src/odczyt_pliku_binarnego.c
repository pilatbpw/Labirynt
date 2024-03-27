#include "odczyt_pliku_binarnego.h"
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
    fprintf(stdout,"File_ID=0x%04X\nEscape:0x%0X \nKolumny:%d\nRzedy:%d\n,X_start:%d\nY_start:%d\nX_koniec:%d\nY_koniec:%d\nLicznik_slow_kodowych:%d\nSolution_offset:%d\nSeparator:%c\nSciana:%c\nSciezka:%c\n", file_id,escape,kolumny,rzedy,X_start,Y_start,X_koniec,Y_koniec,licznik_slow_kodowych,solution_offset,separator,sciana,sciezka);
    fprintf(stdout,"\n");
    char znak;
    char liczba_znakow;
    int pozostale_znaki_w_linii;
    for(int i=4;i>0;i--){
        pozostale_znaki_w_linii=kolumny;
            while(pozostale_znaki_w_linii>0){
                fseek(plik,1,SEEK_CUR);
                fread(&znak,1,1,plik);
                fread(&liczba_znakow,1,1,plik);
                fprintf(stdout, "Znak:%c, Liczba:%c\n", znak,liczba_znakow);
                for(int k=0;k<liczba_znakow;k++){
                  fprintf(przetlumaczony_plik_binarny,"%c", znak);
               }
               pozostale_znaki_w_linii-=liczba_znakow;

            }
            fprintf(przetlumaczony_plik_binarny,"\n");
            
            

        }
        fprintf(stdout,"\n");
        fclose(przetlumaczony_plik_binarny);
    }
    
