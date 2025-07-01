#ifndef DATOTEKA_H
#define DATOTEKA_H

#include "koncerti.h"

void spremiKoncerte(const char* nazivDatoteke, const Koncert* lista, int broj);
void ucitajKoncerte(const char* nazivDatoteke, Koncert** lista, int* broj);
int kopirajDatoteku(const char* izvor, const char* odrediste);

#endif
