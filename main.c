#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_NAME_LENGTH 50 //12

//Odradene tocke: 1, 2, 3, 4, 8, 9, 10, 12, 13, 14, 16, 17, 18, 19, 20
//Ukupan broj odradenih tocaka: 14
//Treba odraditi: 5,6,7,11,15,21

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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Brisanje Clana

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Ispis Clanova

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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Sortiranje po imenu

//strcmp
int usporedbaClanova(const void* a, const void* b) {
	const CLAN* clanA = (const CLAN*)a;
	const CLAN* clanB = (const CLAN*)b;
	return strcmp(clanA->ime, clanB->ime);
}

void sortClanova(CLAN* clanovi, int numClanova) {
	qsort(clanovi, numClanova, sizeof(CLAN), usporedbaClanova);//20
}

void ispisSortiranihClanovaPoImenu(FILE* file) {
	CLAN* clanovi;
	int numClanova = 0;

	// Broji koliko ima clanova
	while (fscanf(file, "%*s %*s %*d") == 0) {
		numClanova++;
	}

	// Alocira memoriju
	clanovi = malloc(numClanova * sizeof(CLAN));
	if (clanovi == NULL) {
		perror("Greska pri alokaciji memorije");
		return;
	}

	fseek(file, 0, SEEK_SET);

	// Cita clanove iz filea u polje
	int i;
	for (i = 0; i < numClanova; i++) {
		clanovi[i].ime = malloc(MAX_NAME_LENGTH * sizeof(char));
		clanovi[i].prezime = malloc(MAX_NAME_LENGTH * sizeof(char));
		fscanf(file, "%s %s %d", clanovi[i].ime, clanovi[i].prezime, &clanovi[i].id);
	}

	// Poziva funkciju za sortiranje
	sortClanova(clanovi, numClanova);

	// Ispisuje Sortirano
	printf("Sortirani clanovi teretane po imenu:\n");
	for (i = 0; i < numClanova; i++) {
		printf("Ime: %s %s\n", clanovi[i].ime, clanovi[i].prezime);
		printf("ID: %d\n\n", clanovi[i].id);
	}

	// freea memoriju
	for (i = 0; i < numClanova; i++) {
		free(clanovi[i].ime);
		free(clanovi[i].prezime);
	}
	free(clanovi);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Sortiranje po prezimenu

int usporedbaClanovaPoPrezimenu(const void* a, const void* b) {
	const CLAN* clanA = (const CLAN*)a;
	const CLAN* clanB = (const CLAN*)b;
	return strcmp(clanA->prezime, clanB->prezime);
}

void sortClanovaPoPrezimenu(CLAN* clanovi, int numClanova) {
	qsort(clanovi, numClanova, sizeof(CLAN), usporedbaClanovaPoPrezimenu);//20
}

void ispisSortiranihClanovaPoPrezimenu(FILE* file) {
	CLAN* clanovi;
	int numClanova = 0;

	// Broji koliko ima clanova
	while (fscanf(file, "%*s %*s %*d") == 0) {
		numClanova++;
	}

	// Alocira memoriju
	clanovi = malloc(numClanova * sizeof(CLAN));
	if (clanovi == NULL) {
		perror("Greska pri alokaciji memorije");
		return;
	}

	fseek(file, 0, SEEK_SET);

	// Cita clanove iz filea u polje
	int i;
	for (i = 0; i < numClanova; i++) {
		clanovi[i].ime = malloc(MAX_NAME_LENGTH * sizeof(char));
		clanovi[i].prezime = malloc(MAX_NAME_LENGTH * sizeof(char));
		fscanf(file, "%s %s %d", clanovi[i].ime, clanovi[i].prezime, &clanovi[i].id);
	}

	// Poziva funkciju za sortiranje
	sortClanovaPoPrezimenu(clanovi, numClanova);

	// Ispisuje Sortirano
	printf("Sortirani clanovi teretane po prezimenu:\n");
	for (i = 0; i < numClanova; i++) {
		printf("Ime: %s %s\n", clanovi[i].ime, clanovi[i].prezime);
		printf("ID: %d\n\n", clanovi[i].id);
	}

	// freea memoriju
	for (i = 0; i < numClanova; i++) {
		free(clanovi[i].ime);
		free(clanovi[i].prezime);
	}
	free(clanovi);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//pretrazivanje
void pretrazivanje(FILE* file, int id) {
	
	CLAN clan;
	clan.ime = malloc(MAX_NAME_LENGTH * sizeof(char));
	clan.prezime = malloc(MAX_NAME_LENGTH * sizeof(char));

	

	int pronaden = 0;
	while (fscanf(file, "%s %s %d", clan.ime, clan.prezime, &clan.id) != EOF) {
		if (clan.id == id) {
			pronaden = 1;
			continue;
		}
	}
	if (pronaden == 1)
	{
		printf("Clan je pronaden");
	}
	else {
		printf("Clan nije pronaden");
	}

	fclose(file);
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
		printf("4. Sortiraj po imenu\n");
		printf("5. Sortiraj po prezimenu\n");
		printf("6. Pretrazivanje\n");
        printf("7. Izlaz\n");
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
			//Sort
			fseek(file, 0, SEEK_SET);
			ispisSortiranihClanovaPoImenu(file);
			break;
		case 5:
			fseek(file, 0, SEEK_SET);
			ispisSortiranihClanovaPoPrezimenu(file);
			break;
		case 6:
			printf("Unesite ID clana kojeg pretrazujete\n");
			result = 0;
			do {
				result = scanf("%d", &id);
				if (result != 1) {
					printf("Neispravan unos za ID. Molimo unesite ponovno.\n");
					while (fgetc(stdin) != '\n');
				}
			} while (result != 1);
			fseek(file, 0, SEEK_SET);
			pretrazivanje(file, id);
			break;
		case 7:
			printf("Izlazak iz programa.\n");
			break;
        default:
            printf("Pogresan unos. Molimo unesite ponovno.\n");
            while (fgetc(stdin) != '\n'); 
            break;
        }
        printf("\n");

    } while (odabir != 7);

    fclose(file);

    return 0;
}