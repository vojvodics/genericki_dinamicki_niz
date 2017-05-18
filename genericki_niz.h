
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




#ifndef GENERICKI_NIZ_H_
#define GENERICKI_NIZ_H_

// structure for the array
typedef struct genNiz
{
    // the actual array
    void ** info;
    // counter for capacity
    int max;
    // counter for num of elements
    int brojEl;
} genNiz;

void napraviGa(genNiz **);
void oslobodiGa(genNiz *);
void napuniGa(genNiz *, void *);
void ubaciNaPocetak(genNiz *, void *);
void napuniPrekoIndexa(genNiz *, void *, int);
void *izbaciElement(genNiz *, int);
void smanjiVelicinu(genNiz *);
void prikaziPrekoIndexa(genNiz *, int, void prikazi(void *, int));
int pronadjiBinarno(genNiz *, void *, int uporedi(void *, void *));
int pronadjiSekvencijalno(genNiz *, void *, int uporedi(void *, void *));
void *pronadjiElement(genNiz *, void *, int operacija(genNiz *, void *, int(void *, void*)), int uporedi(void *, void *));
void swap(void *, void *, int);
void sortiraj(genNiz *, int, int (*uporedi)(void *, void *));

#endif