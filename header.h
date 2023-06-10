#pragma once
#ifndef HEADER_H
#define HEADER_H

#define MAX_NAME_LENGTH 50 //12

typedef struct clan { //3, 2
    char ime[MAX_NAME_LENGTH];      //1
    char prezime[MAX_NAME_LENGTH];
    int id;
} CLAN;

void dodajClana(FILE* file);
void izbrisiClana(FILE* file,const int id);
void ispisClanova(const FILE* file);
int usporedbaClanova(const void* a, const void* b);
void sortClanova(CLAN* clanovi, int numClanova);
void ispisSortiranihClanovaPoImenu(FILE* file);
int usporedbaClanovaPoPrezimenu(const void* a, const void* b);
void sortClanovaPoPrezimenu(CLAN* clanovi, int numClanova);
void ispisSortiranihClanovaPoPrezimenu(FILE* file);
void pretrazivanje(const FILE* file, const int id);
void najveciID(const FILE* file);
#endif // !HEADER_H
