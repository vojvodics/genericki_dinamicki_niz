
#include "genericki_niz.h"


struct elem
{
    int broj;
    char slovo;
    int drugiBroj;
};


int uporediChar(void * a, void * b);
int uporediInt(void * a, void * b);
void prikaziStruct(genNiz * nz);
void prikaziChar(genNiz * nz);
void prikaziInt(genNiz * nz);
void prikaziIntIndex(void *, int);
void prikaziStructIndex(void *, int);
void prikaziCharIndex(void *, int);

int main(void)
{
    // create elements to be tested
    int b = -5, a = 1, c = 4, aa = 500, bb = 7, cc = 8;
    char d = 'd', e = 'e', g = 'g', h = 'h', i = 'i', f = 'f';
    struct elem s1 = {5, 'a', 4};
    struct elem s2 = {54, 'c', 3};
    struct elem s3 = {32, 'd', 5};
    struct elem s4 = {6, 'h', 7};
    
    
    // for easier testing create separate arrays of the same type
    genNiz * nizInt;
    genNiz * nizChar;
    genNiz * nizStruct;
    // initialize them
    napraviGa(&nizInt);
    napraviGa(&nizChar);
    napraviGa(&nizStruct);
    
    // insert values into array of ints
    napuniGa(nizInt, &b);
    napuniGa(nizInt, &c);
    napuniGa(nizInt, &a);
    napuniGa(nizInt, &aa);
    napuniGa(nizInt, &bb);
    // insert value into specific index
    napuniPrekoIndexa(nizInt, &cc, 5);
    
    // insert values into array of chars
    napuniGa(nizChar, &i);
    napuniGa(nizChar, &h);
    napuniGa(nizChar, &g);
    napuniGa(nizChar, &f);
    napuniGa(nizChar, &e);
    // insert value into specific index
    ubaciNaPocetak(nizChar, &d);
    
    // insert values into array of structs
    napuniGa(nizStruct, &s1);
    napuniGa(nizStruct, &s2);
    napuniGa(nizStruct, &s3);
    napuniGa(nizStruct, &s4);
    
    
    prikaziInt(nizInt);
    // sort the array by comparison function passed in
    sortiraj(nizInt, sizeof(int), uporediInt);
    prikaziInt(nizInt);
    // remove an element of the array at the index position
    izbaciElement(nizInt, 2);
    prikaziInt(nizInt);
    // show value at
    prikaziPrekoIndexa(nizInt, 2, prikaziIntIndex);
    smanjiVelicinu(nizInt);
    prikaziInt(nizInt);
    // testing binary and sequential search
    for(int z = 0; z < 10; z++)
    {
        if(z % 2 == 0)
            pronadjiElement(nizInt, &z, pronadjiBinarno, uporediInt);
        else
            pronadjiElement(nizInt, &z, pronadjiSekvencijalno, uporediInt);
    }
    
    // similar as array of ints
    prikaziChar(nizChar);
    sortiraj(nizChar, sizeof(char), uporediChar);
    prikaziChar(nizChar);
    izbaciElement(nizChar, 2);
    prikaziChar(nizChar);
    prikaziPrekoIndexa(nizChar, 2, prikaziCharIndex);
    smanjiVelicinu(nizChar);
    prikaziChar(nizChar);
    for(int z = 97; z < 108; z++)
    {
        if(z % 2 == 0)
            pronadjiElement(nizChar, &z, pronadjiBinarno, uporediChar);
        else
            pronadjiElement(nizChar, &z, pronadjiSekvencijalno, uporediChar);
    }
    
    // insert delete testing...
    prikaziStruct(nizStruct);
    izbaciElement(nizStruct, 2);
    prikaziStruct(nizStruct);
    smanjiVelicinu(nizStruct);
    prikaziStruct(nizStruct);
    prikaziPrekoIndexa(nizStruct, 2, prikaziStructIndex);
    
    
    // free the memory
    oslobodiGa(nizStruct);
    oslobodiGa(nizChar);
    oslobodiGa(nizInt);
    
    
    return 0;
}

void prikaziCharIndex(void * podatak, int index)
{
    printf("\nNiz[%d] = %c\n", index, *(char *)podatak);
}

void prikaziStructIndex(void * podatak, int index)
{
    printf("\nNiz[%d] = %d %c %d\n", index, (*(struct elem *)(podatak)).broj, (*(struct elem *)(podatak)).slovo, (*(struct elem *)(podatak)).drugiBroj);
}

void prikaziIntIndex(void * podatak, int index)
{
    printf("\nNiz[%d] = %d\n", index, *(int *)podatak);
}

void prikaziInt(genNiz * nz)
{
    printf("\nNiz celih brojeva:\n");
    for(int i = 0; i < nz->brojEl; i++)
        printf("%d ", *(int *)nz->info[i]);
    printf("\n");
}

void prikaziChar(genNiz * nz)
{
    printf("\nNiz karaktera:\n");
    for(int i = 0; i < nz->brojEl; i++)
        printf("%c ", *(char *)nz->info[i]);
    printf("\n");
}

void prikaziStruct(genNiz * nz)
{
    printf("\nNiz struktura:\n");
    for(int i = 0; i < nz->brojEl; i++)
        printf("%d %c %d\n", (*(struct elem *)(nz->info[i])).broj, (*(struct elem *)(nz->info[i])).slovo, (*(struct elem *)(nz->info[i])).drugiBroj);
    printf("\n");
}

int uporediInt(void * a, void * b)
{
    int x = *(int *)a;
    int y = *(int *)b;
    if(x > y)
        return 1;
    else if(x == y)
        return 0;
    else
        return -1;
}

int uporediChar(void * a, void * b)
{
    char x = *(char *)a;
    char y = *(char *)b;
    
    if(x > y)
        return 1;
    else if(x == y)
        return 0;
    else
        return -1;
}