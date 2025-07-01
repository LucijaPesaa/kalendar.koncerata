#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "datoteka.h"

// Spremanje u binarnu datoteku
void spremiKoncerte(const char *ime, const Koncert *lista, int broj) {
    FILE *f = fopen(ime, "wb");
    if (!f) { perror("fopen"); return; }
    if (fwrite(&broj, sizeof(int), 1, f) != 1) perror("fwrite broj");
    if (fwrite(lista, sizeof(Koncert), broj, f) != (size_t)broj) perror("fwrite lista");
    fclose(f);
}

// Učitavanje iz binarne datoteke
void ucitajKoncerte(const char *ime, Koncert **lista, int *broj) {
    FILE *f = fopen(ime, "rb");
    if (!f) { perror("fopen"); *broj = 0; *lista = NULL; return; }
    if (fread(broj, sizeof(int), 1, f) != 1) { perror("fread broj"); fclose(f); return; }
    *lista = (Koncert *)malloc(*broj * sizeof(Koncert));
    if (!*lista && *broj > 0) { perror("malloc"); fclose(f); return; }
    if (fread(*lista, sizeof(Koncert), *broj, f) != (size_t)*broj) perror("fread lista");
    // Primjer korištenja ftell/fseek/rewind
    long pos = ftell(f);
    printf("[DEBUG] Pozicija u datoteci nakon čitanja: %ld\n", pos);
    rewind(f);
    fclose(f);
}

// Kopiranje datoteke (primjer za remove/rename)
int kopirajDatoteku(const char* izvor, const char* odrediste) {
    FILE *fin = fopen(izvor, "rb");
    if (!fin) { perror("fopen izvor"); return -1; }
    FILE *fout = fopen(odrediste, "wb");
    if (!fout) { perror("fopen odrediste"); fclose(fin); return -1; }
    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), fin)) > 0) {
        if (fwrite(buffer, 1, bytes, fout) != bytes) {
            perror("fwrite kopija"); fclose(fin); fclose(fout); return -1;
        }
    }
    fclose(fin); fclose(fout);
    return 0;
}
