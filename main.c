#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//gitbash

//3 
typedef struct clan {
	char ime[50];
	char prezime[50];
	int id;
} CLAN;

void dodajClana(FILE* file) {
	CLAN clan;

	printf("Unesi podatke clana:\n");
	printf("Ime: ");
	scanf("%s", clan.ime);
	printf("Prezime: ");
	scanf("%s", clan.prezime);
	printf("ID: ");
	scanf("%d", &clan.id);

	fprintf(file, "%s %s %d\n", clan.ime, clan.prezime, clan.id);
	printf("Clan je uspjesno dodan.\n");
}

void izbrisiClana(FILE* file, int id) { //4
	FILE* tf = fopen("temp.txt", "w");
	CLAN clan;
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
		remove("gym.txt");	//17
		rename("temp.txt", "gym.txt");
		printf("Clan je izbrisan.\n");
	}
	else {
		remove("temp.txt");
		printf("Clan nije pronaden.\n");
	}

	
	file = fopen("gym.txt", "a+");
}

void ispisClanova(FILE* file) {
	CLAN clan;

	printf("Clanovi teretane:\n");
	while (fscanf(file, "%s %s %d", clan.ime, clan.prezime, &clan.id) != EOF) {
		printf("Ime: %s %s\n", clan.ime, clan.prezime);
		printf("ID: %d\n\n", clan.id);
	}

	fclose(file);
	file = fopen("gym.txt", "a+");
}

int main(void) {
	FILE* file = fopen("gym.txt", "a+");

	if (file == NULL) {
		printf("Greska pri otvaranju datoteke.\n");
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
		scanf("%d", &odabir);
		printf("\n");

		switch (odabir) {
		case 1:
			dodajClana(file);
			break;
		case 2:
			printf("Upisi ID clana kojeg zelite izbrisati: ");
			scanf("%d", &id);
			izbrisiClana(file, id);
			break;
		case 3:
			fseek(file, 0, SEEK_SET);  //17
			ispisClanova(file);
			break;
		case 4:
			printf("Izlazak iz programa.\n");
			break;
		default:
			printf("Pogresan unos. Pokusaj ponovo.\n");
			break;
		}

		printf("\n");

	} while (odabir != 4);

	fclose(file);

	return 0;
}