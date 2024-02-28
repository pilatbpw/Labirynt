#include "okreslenie_polozenia.h"
#include "rozwiazywanie_labiryntu.h"

char plansza[3][3];

void rozwiazywanie_labiryntu(struct ParametryLabiryntu_typ *parametry_labiryntu)
{
    FILE *plik = fopen("tmp/temp.txt", "a+");
    otoczenie(0,1, plik, parametry_labiryntu); // pierwszy parametr x, drugi y
    printf("%c%c%c\n", plansza[0][0], plansza[0][1], plansza[0][2]);
    printf("%c%c%c\n", plansza[1][0], plansza[1][1], plansza[1][2]);
    printf("%c%c%c\n", plansza[2][0], plansza[2][1], plansza[2][2]);

    for(int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            //printf("x:%d, y:%d, %c\n", i+1, j+1, plansza[j][i]);
        }
    }
    fclose(plik);
}
void otoczenie(int x, int y, FILE *plik, struct ParametryLabiryntu_typ *parametry_labiryntu)
{
    if(x>parametry_labiryntu->c-1 || y>parametry_labiryntu->r-1)
    {
        exit(1);
    }
    
    for(int j = 0; j < 3; j++)
    {
        for(int i = 0; i < 3; i++)
        {
            fseek(plik, x+i + (parametry_labiryntu->c+1) * (y+j-1)-1, SEEK_SET);
            if(fgetc(plik) == '\n')
            {
                fseek(plik, 0, SEEK_CUR);
            }
            //printf("%ld\n", ftell(plik));
            plansza[j][i]=fgetc(plik);
        }
    }
}