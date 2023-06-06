#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
//#include "funkcije.c"
#include "header.h"



//Odradene tocke: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21
//Ukupan broj odradenih tocaka: 21
//Treba odraditi: 


//4


int main(void) {
    FILE* file = fopen("gym.txt", "a+");
    if (file == NULL) {
        perror("Greska pri otvaranju datoteke");
        return 1;
    }

    int odabir, id;
    char ch[2];

    do {
        printf("Izbornik:\n"); //8
        printf("1. Dodaj clanove\n");
        printf("2. Izbrisi clanove\n");
        printf("3. Ispisi listu clanova\n");
		printf("4. Sortiraj po imenu\n");
		printf("5. Sortiraj po prezimenu\n");
		printf("6. Pretrazivanje\n");
		printf("7. Ispis brojeva\n");
        printf("8. Izlaz\n");
        printf("Tvoj odabir: ");

        static int result = 0;
        //do {
        //    result = scanf("%d", &odabir);
        //    if (result != 1) {
        //        printf("Neispravan unos. Molimo unesite ponovno.\n");
        //        while (fgetc(stdin) != '\n');
        //    }
        //} while (result != 1);
        static int duzina; //5
        do
        {
            scanf("%s", ch);
            duzina = strlen(ch);
            if (duzina>1)
            {
                printf("Krivi unos. Molimo unesute ponovo.\n");
            }
        } while (duzina>1);
        printf("\n");





        switch (ch[0]) {
        case '1':
            dodajClana(file);
            break;
        case '2':
            printf("Upisi ID clana kojeg zelite izbrisati: ");

            result = 0;
            do {
                result = scanf("%d", &id);
				int c;
				while ((c = getchar()) != '\n' && c != EOF);
                if (result != 1) {
                    printf("Neispravan unos za ID. Molimo unesite ponovno.\n");
                    while (fgetc(stdin) != '\n');
                }
            } while (result != 1);

            izbrisiClana(file, id);
            break;
        case '3':
            fseek(file, 0, SEEK_SET); //17
            ispisClanova(file);
            break;
        
		case '4':
			//Sort
			fseek(file, 0, SEEK_SET);
			ispisSortiranihClanovaPoImenu(file);
			break;
        case '5':
			fseek(file, 0, SEEK_SET);
			ispisSortiranihClanovaPoPrezimenu(file);
			break;
        case '6':
			printf("Unesite ID clana kojeg pretrazujete\n");
			result = 0;
			do {
				result = scanf("%d", &id);
				int c;
				while ((c = getchar()) != '\n' && c != EOF);
				if (result != 1) {
					printf("Neispravan unos za ID. Molimo unesite ponovno.\n");
					while (fgetc(stdin) != '\n');
				}
			} while (result != 1);
			fseek(file, 0, SEEK_SET);
			pretrazivanje(file, id);
			break;
		case '7':
			printf("Ispis brojeva\n");
			ispisBrojeva();
			break;
        case '8':
			printf("Izlazak iz programa.\n");
			break;
        default:
            printf("Pogresan unos. Molimo unesite ponovno.\n");
            while (fgetc(stdin) != '\n'); 
            break;
        }
        printf("\n");

    } while (ch[0] != '8');
    fclose(file);

    return 0;
}