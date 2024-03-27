#include "obsluga_argumentow.h"

char obsluga_argumentow(int argc, char* argv[], char* nazwa){
	int opt;
	while((opt = getopt(argc, argv, ":f:dk")) != -1)  
    {  
        switch(opt)  
        {    
            case 'f':  
                printf("Podany plik: %s\n", optarg);  
				strcpy(nazwa,optarg);
                break;  
            case ':':  
                printf("BLAD: Nie podano nazwy pliku!\n");  
                exit(1); 
			case 'd':
				fprintf(stdout, "Wybrano d\n");
				return 'd';
				break;
			case 'k':
				fprintf(stdout, "Wybrano k\n");
				return 'k';
				break;
            case '?':  
                printf("Podano niepoprawny argument: %c\n", optopt); 
                break;  
        }  
    }
	fprintf(stdout, "BLAD: Nie wybrano trybu programu!\n");
	exit(1);
	
}