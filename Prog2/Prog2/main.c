#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "koncerti.h"
#include "datoteka.h"
#include "izbornik.h"

// Globalna varijabla (primjer za extern)
int globalniBrojac = 0;

int main() {
    Koncert *lista = NULL;
    int broj = 0;
    int izbor;
    char dat1[] = "koncerti.bin";

    // Učitavanje iz datoteke na početku
    ucitajKoncerte(dat1, &lista, &broj);

    do {
        prikaziIzbornik();
        printf("Izbor: ");
        if (scanf("%d", &izbor) != 1) { printf("Neispravan unos.\n"); break; }

        switch (izbor) {
            case IZBORNIK_DODAJ:
                dodajKoncert(&lista, &broj);
                spremiKoncerte(dat1, lista, broj);
                break;
            case IZBORNIK_ISPIS:
                ispisiKoncerte(lista, broj);
                break;
            case IZBORNIK_AZURIRAJ:
                azurirajKoncert(lista, broj);
                spremiKoncerte(dat1, lista, broj);
                break;
            case IZBORNIK_OBRISI:
                obrisiKoncert(&lista, &broj);
                spremiKoncerte(dat1, lista, broj);
                break;
                case IZBORNIK_STATISTIKA:
                ispisiStatistiku(lista, broj);
                printf("\nDodatne opcije:\n");
                printf("1. Sortiraj po cijeni\n");
                printf("2. Sortiraj po vremenu održavanja\n");
                printf("3. Rekurzivni ispis\n");
                printf("4. Kopiraj datoteku\n");
                printf("0. Nazad\n");
                int podizbor;
                scanf("%d", &podizbor);
                if (podizbor == 1) {
                    sortirajKoncerte(lista, broj);
                    printf("Sortirano po cijeni:\n");
                    ispisiKoncerte(lista, broj);
                } else if (podizbor == 2) {
                    sortirajPoVremenu(lista, broj);
                    printf("Sortirano po vremenu održavanja:\n");
                    ispisiKoncerte(lista, broj);
                } else if (podizbor == 3) {
                    rekurzivnoIspisiKoncerte(lista, broj);
                } else if (podizbor == 4) {
                    char novaDat[100];
                    printf("Unesi ime za kopiju: ");
                    scanf("%s", novaDat);
                    if (kopirajDatoteku(dat1, novaDat) == 0)
                        printf("Kopija uspješna!\n");
                }
                break;
            case IZBORNIK_PRETRAZI_BSEARCH:
                pretraziKoncertBsearch(lista, broj);
                break;
            case IZBORNIK_IZLAZ:
                break;
            default:
                printf("Nepoznata opcija.\n");
        }
    } while (izbor != 0);
               

    // Sigurno oslobađanje memorije
    free(lista); 

    // Primjer remove/rename
    // remove("koncerti_stari.bin");
    // rename("koncerti.bin", "koncerti_stari.bin");

    return 0;
}
