#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_NAME_LENGTH 50 //12

//Odradene tocke: 1, 2, 3, 4, 8, 9, 10, 12, 13, 14, 16, 17, 18, 19
//Ukupan broj odradenih tocaka: 14
//Treba odraditi: 5,6,7,11,15,20,21

typedef struct clan { //3, 2
    char* ime;      //1
    char* prezime;
    int id;
} CLAN;

//4
void dodajClana(FILE* file) {
    CLAN clan;
    clan.ime = malloc(MAX_NAME_LENGTH * sizeof(char));
    clan.prezime = malloc(MAX_NAME_LENGTH * sizeof(char));

    printf("Unesi podatke clana:\n");
    printf("Ime: ");
    scanf("%s", clan.ime);
    printf("Prezime: ");
    scanf("%s", clan.prezime);

    int result = 0;
    int id;
    int duplicateID = 0; // Koristi se da se zna ako je duplikat naden

    do {
        duplicateID = 0; 

        printf("ID: ");
        result = scanf("%d", &clan.id);
        if (result != 1) {
            printf("Neispravan unos za ID. Molimo unesite ponovno.\n");
            while (fgetc(stdin) != '\n');
            continue;
        }

        // gleda dali ima isti ID
        fseek(file, 0, SEEK_SET);
        while (fscanf(file, "%*s %*s %d", &id) == 1) {
            if (id == clan.id) {
                printf("Clan s unesenim ID-om vec postoji. Odaberi drugi ID.\n");
                duplicateID = 1;
                break;
            }
        }

    } while (duplicateID);

    fprintf(file, "%s %s %d\n", clan.ime, clan.prezime, clan.id);
    printf("Clan je uspjesno dodan.\n");

    free(clan.ime);
    free(clan.prezime);
}

void izbrisiClana(FILE* file, int id) {
    FILE* tf = fopen("temp.txt", "w");
    if (tf == NULL) {
        perror("Greska pri otvaranju temp.txt");
        return;
    }

    CLAN clan;
    clan.ime = malloc(MAX_NAME_LENGTH * sizeof(char));
    clan.prezime = malloc(MAX_NAME_LENGTH * sizeof(char));

    int pronaden = 0;

    while (fscanf(file, "%s %s %d", clan.ime, clan.prezime, &clan.id) != EOF) {
        if (clan.id == id) {
            pronaden = 1;
            continue;
        }

        fprintf(tf, "%s %s %d\n", clan.ime, clan.prezime, clan.id);
    }

    fclose(file);
    fclose(tf);

    if (pronaden) {
        if (remove("gym.txt") != 0) {
            perror("Greska pri brisanju gym.txt"); //19
            return;
        }

        if (rename("temp.txt", "gym.txt") != 0) {
            perror("Greska pri preimenovanju temp.txt");
            return;
        }

        printf("Clan je izbrisan.\n");
    }
    else {
        remove("temp.txt"); //18
        printf("Clan nije pronaden.\n");
    }

    file = fopen("gym.txt", "a+");
    if (file == NULL) {
        perror("Greska pri otvaranju gym.txt");
    }

    free(clan.ime);
    free(clan.prezime);
}

void ispisClanova(FILE* file) { //9, 10
    CLAN clan;
    clan.ime = malloc(MAX_NAME_LENGTH * sizeof(char)); //13, 14
    clan.prezime = malloc(MAX_NAME_LENGTH * sizeof(char));

    printf("Clanovi teretane:\n");
    while (fscanf(file, "%s %s %d", clan.ime, clan.prezime, &clan.id) != EOF) {
        printf("Ime: %s %s\n", clan.ime, clan.prezime);
        printf("ID: %d\n\n", clan.id);
    }

    fclose(file); 
    file = fopen("gym.txt", "a+"); //16
    if (file == NULL) {
        perror("Greska pri otvaranju gym.txt");
    }

    free(clan.ime);
    free(clan.prezime);
}

int main(void) {
    FILE* file = fopen("gym.txt", "a+");
    if (file == NULL) {
        perror("Greska pri otvaranju datoteke");
        return 1;
    }

    int odabir, id;

    do {
        printf("Izbornik:\n"); //8
        printf("1. Dodaj clanove\n");
        printf("2. Izbrisi clanove\n");
        printf("3. Ispisi listu clanova\n");
        printf("4. Izlaz\n");
        printf("Tvoj odabir: ");

        int result = 0;
        do {
            result = scanf("%d", &odabir);
            if (result != 1) {
                printf("Neispravan unos. Molimo unesite ponovno.\n");
                while (fgetc(stdin) != '\n');
            }
        } while (result != 1);

        printf("\n");

        switch (odabir) {
        case 1:
            dodajClana(file);
            break;
        case 2:
            printf("Upisi ID clana kojeg zelite izbrisati: ");

            result = 0;
            do {
                result = scanf("%d", &id);
                if (result != 1) {
                    printf("Neispravan unos za ID. Molimo unesite ponovno.\n");
                    while (fgetc(stdin) != '\n');
                }
            } while (result != 1);

            izbrisiClana(file, id);
            break;
        case 3:
            fseek(file, 0, SEEK_SET); //17
            ispisClanova(file);
            break;
        case 4:
            printf("Izlazak iz programa.\n");
            break;
        default:
            printf("Pogresan unos. Molimo unesite ponovno.\n");
            while (fgetc(stdin) != '\n'); 
            break;
        }

        printf("\n");

    } while (odabir != 4);

    fclose(file);

    return 0;
}