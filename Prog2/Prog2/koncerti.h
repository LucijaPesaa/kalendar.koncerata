#ifndef KONCERTI_H
#define KONCERTI_H

#include <stdio.h>
#include <stdlib.h>

typedef enum { ROCK, POP, JAZZ, KLASIKA } Zanr;

typedef struct {
    int id;
    char naziv[100];
    char mjesto[100];
    float cijena;
    int brojUlaznica;
    int vrijeme;
    Zanr zanr;
} Koncert;

// CRUID funkcije
void dodajKoncert(Koncert **lista, int *broj);
void ispisiKoncerte(const Koncert *lista, int broj);
void azurirajKoncert(Koncert *lista, int broj);
void obrisiKoncert(Koncert **lista, int *broj);

// Ostalo
void ispisiStatistiku(const Koncert *lista, int broj);
void sortirajKoncerte(Koncert *lista, int broj);
void sortirajPoVremenu(Koncert *lista, int broj);
void pretraziKoncert(const Koncert *lista, int broj);
void pretraziKoncertBsearch(const Koncert *lista, int broj);

#endif
