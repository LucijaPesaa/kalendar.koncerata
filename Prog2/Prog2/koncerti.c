#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "koncerti.h"

// Makro za minimum
#define MIN(a, b) ((a)<(b)?(a):(b))
// Inline funkcija za maksimum
static inline float maxf(float a, float b) { return a > b ? a : b; }

static void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Dodavanje koncerta (Create)
void dodajKoncert(Koncert **lista, int *broj) {
    if (!lista || !broj) return;
    Koncert *temp = (Koncert *)realloc(*lista, (*broj + 1) * sizeof(Koncert));
    if (!temp) { perror("realloc"); return; }
    *lista = temp;
    Koncert *novi = &(*lista)[*broj];
    printf("Unesite ID: "); scanf("%d", &novi->id); clearInputBuffer();
    printf("Unesite naziv: "); fgets(novi->naziv, sizeof(novi->naziv), stdin);
    novi->naziv[strcspn(novi->naziv, "\n")] = 0;
    printf("Unesite mjesto: "); fgets(novi->mjesto, sizeof(novi->mjesto), stdin);
    novi->mjesto[strcspn(novi->mjesto, "\n")] = 0;
    printf("Unesite cijenu: "); scanf("%f", &novi->cijena);
    printf("Unesite broj ulaznica: "); scanf("%d", &novi->brojUlaznica);
    printf("Unesite vrijeme (sat): "); scanf("%d", &novi->vrijeme);
    printf("Unesite žanr (0-ROCK, 1-POP, 2-JAZZ, 3-KLASIKA): ");
    int zanr; scanf("%d", &zanr);
    novi->zanr = (Zanr) zanr;
    (*broj)++;
}

// Ispis koncerata (Read)
void ispisiKoncerte(const Koncert *lista, int broj) {
    static const char *naziviZanrova[] = {"Rock", "Pop", "Jazz", "Klasika"};
    for (int i = 0; i < broj; i++) {
        printf("ID: %d | Naziv: %s | Mjesto: %s | Cijena: %.2f | Ulaznica: %d | Vrijeme: %02d:00 | Žanr: %s\n",
            lista[i].id, lista[i].naziv, lista[i].mjesto, lista[i].cijena,
            lista[i].brojUlaznica, lista[i].vrijeme, naziviZanrova[lista[i].zanr]);
    }
}

// Ažuriranje koncerta (Update)
void azurirajKoncert(Koncert *lista, int broj) {
    if (!lista) return;
    int id;
    printf("Unesite ID za ažuriranje: "); scanf("%d", &id); clearInputBuffer();
    for (int i = 0; i < broj; i++) {
        if (lista[i].id == id) {
            printf("Novi naziv: "); fgets(lista[i].naziv, sizeof(lista[i].naziv), stdin);
            lista[i].naziv[strcspn(lista[i].naziv, "\n")] = 0;
            printf("Novo mjesto: "); fgets(lista[i].mjesto, sizeof(lista[i].mjesto), stdin);
            lista[i].mjesto[strcspn(lista[i].mjesto, "\n")] = 0;
            printf("Nova cijena: "); scanf("%f", &lista[i].cijena);
            printf("Novi broj ulaznica: "); scanf("%d", &lista[i].brojUlaznica);
            printf("Novo vrijeme: "); scanf("%d", &lista[i].vrijeme);
            printf("Novi žanr (0-ROCK, 1-POP, 2-JAZZ, 3-KLASIKA): ");
            int zanr; scanf("%d", &zanr); lista[i].zanr = (Zanr)zanr;
            printf("Ažurirano!\n");
            return;
        }
    }
    printf("Koncert nije pronađen.\n");
}

// Brisanje koncerta (Delete)
void obrisiKoncert(Koncert **lista, int *broj) {
    if (!lista || !broj) return;
    int id;
    printf("Unesite ID za brisanje: "); scanf("%d", &id);
    for (int i = 0; i < *broj; i++) {
        if ((*lista)[i].id == id) {
            for (int j = i; j < *broj - 1; j++)
                (*lista)[j] = (*lista)[j + 1];
            Koncert *temp = (Koncert *)realloc(*lista, (*broj - 1) * sizeof(Koncert));
            if (!temp && *broj - 1 > 0) { perror("realloc"); return; }
            *lista = temp;
            (*broj)--;
            printf("Koncert obrisan.\n");
            return;
        }
    }
    printf("Koncert nije pronađen.\n");
}

// Statistika
void ispisiStatistiku(const Koncert *lista, int broj) {
    if (!lista || broj == 0) { printf("Nema koncerata.\n"); return; }
    float suma = 0, min = lista[0].cijena, max = lista[0].cijena;
    for (int i = 0; i < broj; i++) {
        suma += lista[i].cijena;
        min = MIN(min, lista[i].cijena);
        max = maxf(max, lista[i].cijena);
    }
    printf("Prosječna cijena: %.2f | Min: %.2f | Max: %.2f\n", suma / broj, min, max);
}

// Sortiranje po cijeni (qsort, pokazivač na funkciju)
static int usporediCijenu(const void *a, const void *b) {
    float razlika = ((Koncert*)a)->cijena - ((Koncert*)b)->cijena;
    return (razlika > 0) - (razlika < 0);
}
void sortirajKoncerte(Koncert *lista, int broj) {
    qsort(lista, broj, sizeof(Koncert), usporediCijenu);
}

// Sortiranje po vremenu (qsort, pokazivač na funkciju)
static int usporediVrijeme(const void *a, const void *b) {
    return ((Koncert*)a)->vrijeme - ((Koncert*)b)->vrijeme;
}
void sortirajPoVremenu(Koncert *lista, int broj) {
    qsort(lista, broj, sizeof(Koncert), usporediVrijeme);
}

// Pretraga po ID-u (ručno)
void pretraziKoncert(const Koncert *lista, int broj) {
    int id;
    printf("Unesite ID: "); scanf("%d", &id);
    for (int i = 0; i < broj; i++) {
        if (lista[i].id == id) {
            printf("Pronađen: %s, %.2f EUR\n", lista[i].naziv, lista[i].cijena);
            return;
        }
    }
    printf("Nema rezultata.\n");
}

// Pretraga po ID-u (bsearch, pokazivač na funkciju, sortiranje prije)
static int usporediID(const void *a, const void *b) {
    return ((Koncert*)a)->id - ((Koncert*)b)->id;
}
void pretraziKoncertBsearch(const Koncert *lista, int broj) {
    if (!lista || broj == 0) { printf("Nema koncerata.\n"); return; }
    int id;
    printf("Unesite ID za bsearch: "); scanf("%d", &id);
    Koncert key = {.id = id};
    // Binarna pretraga zahtijeva sortirani niz po ID-u
    Koncert *sorted = malloc(broj * sizeof(Koncert));
    if (!sorted) { perror("malloc"); return; }
    memcpy(sorted, lista, broj * sizeof(Koncert));
    qsort(sorted, broj, sizeof(Koncert), usporediID);
    Koncert *found = bsearch(&key, sorted, broj, sizeof(Koncert), usporediID);
    if (found)
        printf("Pronađen (bsearch): %s, %.2f EUR\n", found->naziv, found->cijena);
    else
        printf("Nema rezultata (bsearch).\n");
    free(sorted);
}

// Rekurzivni ispis (rekurzija)
static void rekurzivniIspis(const Koncert *lista, int broj, int i) {
    if (i >= broj) return;
    printf("ID: %d | Naziv: %s\n", lista[i].id, lista[i].naziv);
    rekurzivniIspis(lista, broj, i + 1);
}
void rekurzivnoIspisiKoncerte(const Koncert *lista, int broj) {
    rekurzivniIspis(lista, broj, 0);
}
