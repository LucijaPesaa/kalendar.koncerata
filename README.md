# kalendar.koncerata

koncerti.h
#ifndef KONCERTI_H
#define KONCERTI_H

#include <stdio.h>

typedef enum {
    ROCK,
    POP,
    JAZZ,
    KLASIKA
} Zanr;

typedef struct {
    int id;
    char naziv[100];
    char mjesto[100];
    float cijena;
    int brojUlaznica;
    int vrijeme;
    Zanr zanr;
} Koncert;

void dodajKoncert(Koncert **lista, int *broj);
void ispisiKoncerte(const Koncert *lista, int broj);
void azurirajKoncert(Koncert *lista, int broj);
void obrisiKoncert(Koncert **lista, int *broj);
void ispisiStatistiku(const Koncert *lista, int broj);
void sortirajKoncerte(Koncert *lista, int broj);
void sortirajPoVremenu(Koncert *lista, int broj);
void pretraziKoncert(const Koncert *lista, int broj);

#endif



datoteka.h
#ifndef DATOTEKA_H
#define DATOTEKA_H

#include "koncerti.h"

void spremiKoncerte(const char* nazivDatoteke, const Koncert* lista, int broj);
void ucitajKoncerte(const char* nazivDatoteke, Koncert** lista, int* broj);

#endif



izbornik.h
#ifndef IZBORNIK_H
#define IZBORNIK_H

void prikaziIzbornik();

#endif



izbornik.c
#include <stdio.h>
#include "izbornik.h"

void prikaziIzbornik() {
    printf("\n--- KONCERTNI PROGRAM ---\n");
    printf("1. Dodaj koncert\n");
    printf("2. Ispisi koncerte\n");
    printf("3. Azuriraj koncert\n");
    printf("4. Obrisi koncert\n");
    printf("5. Spremi u datoteku\n");
    printf("6. Ucitaj iz datoteke\n");
    printf("7. Statistika i sortiranje\n");
    printf("8. Pretrazi po ID-u\n");
    printf("0. Izlaz\n");
}



koncerti.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "koncerti.h"

static void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void dodajKoncert(Koncert **lista, int *broj) {
    if (!lista || !broj) return;
    Koncert *temp = (Koncert *)realloc(*lista, (*broj + 1) * sizeof(Koncert));
    if (!temp) {
        perror("realloc");
        return;
    }
    *lista = temp;

    Koncert *novi = &(*lista)[*broj];

    printf("Unesite ID: ");
    scanf("%d", &novi->id);
    clearInputBuffer();
    printf("Unesite naziv: ");
    fgets(novi->naziv, sizeof(novi->naziv), stdin);
    novi->naziv[strcspn(novi->naziv, "\n")] = 0;

    printf("Unesite mjesto: ");
    fgets(novi->mjesto, sizeof(novi->mjesto), stdin);
    novi->mjesto[strcspn(novi->mjesto, "\n")] = 0;

    printf("Unesite cijenu: ");
    scanf("%f", &novi->cijena);

    printf("Unesite broj ulaznica: ");
    scanf("%d", &novi->brojUlaznica);

    printf("Unesite vrijeme (sat): ");
    scanf("%d", &novi->vrijeme);

    printf("Unesite žanr (0-ROCK, 1-POP, 2-JAZZ, 3-KLASIKA): ");
    int zanr;
    scanf("%d", &zanr);
    novi->zanr = (Zanr) zanr;

    (*broj)++;
}

void ispisiKoncerte(const Koncert *lista, int broj) {
    static const char *naziviZanrova[] = {"Rock", "Pop", "Jazz", "Klasika"};
    for (int i = 0; i < broj; i++) {
        printf("ID: %d | Naziv: %s | Mjesto: %s | Cijena: %.2f | Ulaznica: %d | Vrijeme: %02d:00 | Žanr: %s\n",
            lista[i].id, lista[i].naziv, lista[i].mjesto, lista[i].cijena,
            lista[i].brojUlaznica, lista[i].vrijeme, naziviZanrova[lista[i].zanr]);
    }
}

void azurirajKoncert(Koncert *lista, int broj) {
    if (!lista) return;
    int id;
    printf("Unesite ID za ažuriranje: ");
    scanf("%d", &id);
    clearInputBuffer();
    for (int i = 0; i < broj; i++) {
        if (lista[i].id == id) {
            printf("Novi naziv: ");
            fgets(lista[i].naziv, sizeof(lista[i].naziv), stdin);
            lista[i].naziv[strcspn(lista[i].naziv, "\n")] = 0;

            printf("Novo mjesto: ");
            fgets(lista[i].mjesto, sizeof(lista[i].mjesto), stdin);
            lista[i].mjesto[strcspn(lista[i].mjesto, "\n")] = 0;

            printf("Nova cijena: ");
            scanf("%f", &lista[i].cijena);

            printf("Novi broj ulaznica: ");
            scanf("%d", &lista[i].brojUlaznica);

            printf("Novo vrijeme: ");
            scanf("%d", &lista[i].vrijeme);
            return;
        }
    }
    printf("Koncert nije pronađen.\n");
}

void obrisiKoncert(Koncert **lista, int *broj) {
    if (!lista || !broj) return;
    int id;
    printf("Unesite ID za brisanje: ");
    scanf("%d", &id);
    for (int i = 0; i < *broj; i++) {
        if ((*lista)[i].id == id) {
            for (int j = i; j < *broj - 1; j++)
                (*lista)[j] = (*lista)[j + 1];
            Koncert *temp = (Koncert *)realloc(*lista, (*broj - 1) * sizeof(Koncert));
            if (!temp && *broj - 1 > 0) {
                perror("realloc");
                return;
            }
            *lista = temp;
            (*broj)--;
            printf("Koncert obrisan.\n");
            return;
        }
    }
    printf("Koncert nije pronađen.\n");
}

void ispisiStatistiku(const Koncert *lista, int broj) {
    if (!lista || broj == 0) {
        printf("Nema koncerata.\n");
        return;
    }
    float suma = 0, min = lista[0].cijena, max = lista[0].cijena;
    for (int i = 0; i < broj; i++) {
        suma += lista[i].cijena;
        if (lista[i].cijena < min) min = lista[i].cijena;
        if (lista[i].cijena > max) max = lista[i].cijena;
    }
    printf("Prosječna cijena: %.2f | Min: %.2f | Max: %.2f\n", suma / broj, min, max);
}

int usporediCijenu(const void *a, const void *b) {
    return ((Koncert*)a)->cijena - ((Koncert*)b)->cijena;
}

void sortirajKoncerte(Koncert *lista, int broj) {
    qsort(lista, broj, sizeof(Koncert), usporediCijenu);
}

int usporediVrijeme(const void *a, const void *b) {
    return ((Koncert*)a)->vrijeme - ((Koncert*)b)->vrijeme;
}

void sortirajPoVremenu(Koncert *lista, int broj) {
    qsort(lista, broj, sizeof(Koncert), usporediVrijeme);
}

void pretraziKoncert(const Koncert *lista, int broj) {
    int id;
    printf("Unesite ID: ");
    scanf("%d", &id);
    for (int i = 0; i < broj; i++) {
        if (lista[i].id == id) {
            printf("Pronađen: %s, %.2f EUR\n", lista[i].naziv, lista[i].cijena);
            return;
        }
    }
    printf("Nema rezultata.\n");
}




datoteka.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "datoteka.h"

void spremiKoncerte(const char *ime, const Koncert *lista, int broj) {
    FILE *f = fopen(ime, "wb");
    if (!f) { perror("fopen"); return; }
    fwrite(&broj, sizeof(int), 1, f);
    fwrite(lista, sizeof(Koncert), broj, f);
    fclose(f);
}

void ucitajKoncerte(const char *ime, Koncert **lista, int *broj) {
    FILE *f = fopen(ime, "rb");
    if (!f) { perror("fopen"); return; }
    fread(broj, sizeof(int), 1, f);
    *lista = (Koncert *)malloc(*broj * sizeof(Koncert));
    fread(*lista, sizeof(Koncert), *broj, f);
    fclose(f);
}




main.c
#include <stdio.h>
#include <stdlib.h>
#include "koncerti.h"
#include "datoteka.h"
#include "izbornik.h"

int main() {
    Koncert *lista = NULL;
    int broj = 0;
    int izbor;
    char dat1[] = "koncerti.bin";

    do {
        prikaziIzbornik();
        printf("Izbor: ");
        scanf("%d", &izbor);
        switch (izbor) {
            case 1: dodajKoncert(&lista, &broj); break;
            case 2: ispisiKoncerte(lista, broj); break;
            case 3: azurirajKoncert(lista, broj); break;
            case 4: obrisiKoncert(&lista, &broj); break;
            case 5: spremiKoncerte(dat1, lista, broj); break;
            case 6: ucitajKoncerte(dat1, &lista, &broj); break;
            case 7: {
                int podizbor;
                ispisiStatistiku(lista, broj);
                printf("\nDodatne opcije:\n");
                printf("1. Sortiraj po cijeni\n");
                printf("2. Sortiraj po vremenu održavanja\n");
                printf("0. Nazad\n");
                printf("Izbor: ");
                scanf("%d", &podizbor);
                switch (podizbor) {
                    case 1:
                        sortirajKoncerte(lista, broj);
                        printf("Sortirano po cijeni:\n");
                        ispisiKoncerte(lista, broj);
                        break;
                    case 2:
                        sortirajPoVremenu(lista, broj);
                        printf("Sortirano po vremenu održavanja:\n");
                        ispisiKoncerte(lista, broj);
                        break;
                    case 0:
                        break;
                    default:
                        printf("Nepoznata opcija.\n");
                }
                break;
            }
            case 8: pretraziKoncert(lista, broj); break;
        }
    } while (izbor != 0);

    free(lista);
    return 0;
}

