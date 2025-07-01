#ifndef IZBORNIK_H
#define IZBORNIK_H

typedef enum {
    IZBORNIK_DODAJ = 1,
    IZBORNIK_ISPIS,
    IZBORNIK_AZURIRAJ,
    IZBORNIK_OBRISI,
    IZBORNIK_STATISTIKA,
    IZBORNIK_PRETRAZI_BSEARCH,
    IZBORNIK_IZLAZ
} IzbornikOpcije;

void prikaziIzbornik();

#endif
