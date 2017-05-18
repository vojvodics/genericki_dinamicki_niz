
#include "genericki_niz.h"

/**
 * Initializes the array to some max capacity
 **/
void napraviGa(genNiz ** N)
{
    genNiz * novi = malloc(sizeof(genNiz));
    // only for testing purposes, should be higher
    novi->max = 2;
    novi->brojEl = 0;
    novi->info = calloc(novi->max, sizeof(void *));
    *N = novi;
}

/**
 * Frees the memory
 **/
void oslobodiGa(genNiz * nz)
{
    free(nz->info);
    free(nz);
}

/**
 * Inserts an element to the end of the array
 * Doubles the array if maximum capacity reached
 **/
void napuniGa(genNiz * nz, void * data)
{
    if (data == NULL)
        return;
    nz->info[nz->brojEl++] = data;
    if(nz->brojEl == nz->max - 1)
    {
        nz->max *= 2;
        void * x = realloc(nz->info, nz->max * sizeof(void *));
        if(x == NULL)
        {
            printf("Neuspesno alocirana memorija\n");
            exit(1);
        }
        nz->info = x;
    }
}

/**
 * Inserts an element to the begining of the array.
 * Should not be used ever because of shifting all of the elements
 * Doubles the array if maximum capacity reached
 **/
void ubaciNaPocetak(genNiz * nz, void * data)
{
    if (data == NULL)
        return;
    (nz->brojEl)++;
    if(nz->brojEl == nz->max)
    {
        nz->max *= 2;
        void * x = realloc(nz->info, nz->max * sizeof(void *));
        if(x == NULL)
        {
            printf("Neuspesno alocirana memorija\n");
            exit(1);
        }
        nz->info = x;
    }
    
    for(int i = nz->brojEl - 1; i > 0; i--)
        nz->info[i] = nz->info[i - 1];
    
    nz->info[0] = data;
}

/**
 * Inserts an element at some particular index
 * Should not be used frequently because of shifting elements
 * Doubles the array if maximum capacity reached
 **/
void napuniPrekoIndexa(genNiz * nz, void * data, int index)
{
    if(index >= nz->brojEl || index < 0)
        return;
    nz->info[index] = data;
    if(index == nz->brojEl)
        (nz->brojEl)++;
}

/**
 * Deletes an element at given index
 **/
void * izbaciElement(genNiz * nz, int index)
{
    // if array is empty or invalid index passed
    if(index < 0 || index >= nz->brojEl || nz->brojEl == 0)
        return NULL;
        
    void *data = nz->info[index];
    // shift all the elements
    for(int i = index; i < nz->brojEl; i++)
        nz->info[i] = nz->info[i + 1];
    (nz->brojEl)--;
    return data;
}

/**
 * Reduces capacity of the array to number of elements
 * Useful when you don't need to insert elements into the array, but want to save memory
 **/
void smanjiVelicinu(genNiz * nz)
{
    void * x = realloc(nz->info, nz->brojEl * sizeof(void *));
    if(x == NULL)
    {
        printf("Neuspesno alocirana memorija\n");
        exit(1);
    }
    nz->info = x;
    // for testing purposes
    // printf("\nSmanjio sam niz!\n");
}

/**
 * Shows element at particular index
 **/
void prikaziPrekoIndexa(genNiz * nz, int index, void prikazi(void *, int))
{
    if (index < 0 || index >= nz->brojEl)
        return;
    prikazi(nz->info[index], index);
}

/**
 * Binary search implemented iteratively.
 * Requires function that compares two elements, and returns 0 if elements are equal
 * Requires sorted array to work properly.
 **/
int pronadjiBinarno(genNiz * nz, void * podatak, int uporedi(void *, void *))
{
    int dg = 0, gg = nz->brojEl - 1;
    while(gg >= dg)
    {
        int sredina = (gg + dg)/2;
        if(uporedi(nz->info[sredina], podatak) == 0)
            return sredina;
        else if(uporedi(nz->info[sredina], podatak) > 0)
            gg = sredina - 1;
        else
            dg = sredina + 1;
        
    }
    return -1;
}

/**
 * Sequential search through the array.
 * Need to pass in a function that compares two elements
 * Assumes that comparison function returns 0 if elements are equal
 **/
int pronadjiSekvencijalno(genNiz * nz, void * podatak, int uporedi(void *, void *))
{
    for(int i = 0; i < nz->brojEl; i++)
        if(uporedi(nz->info[i], podatak) == 0)
            return i;
    return -1;        
}

/**
 * Search for an element given comparator function and search function
 **/
void * pronadjiElement(genNiz * nz, void * podatak, int operacija(genNiz *, void *, int(void *, void*)), int uporedi(void *, void *))
{
    int nesto = operacija(nz, podatak, uporedi);
    if(nesto == -1)
    {
        printf("\nPodatak ne postoji u nizu.\n");
        return NULL;
    }

    printf("\nPodatak je pronadjen na indexu %d\n", nesto);
    return nz->info[nesto];
}


/**
 * Swaps two elements.
 **/
void swap(void * a, void * b, int size)
{
    void * pom = malloc(size);
    memcpy(pom, a, size);
    memcpy(a, b, size);
    memcpy(b, pom, size);
    free(pom);
}



/**
 * Sorts the array given comparator function.
 * Sorts in O(n^2) time
 **/
void sortiraj(genNiz * nz, int size, int (*uporedi)(void *, void *))
{
    // for testing
    // printf("\nSORTIRAM...\n");
    for(int i = 0; i < nz->brojEl - 1; i++)
        for(int j = i + 1; j < nz->brojEl; j++)
            if(uporedi(nz->info[i], nz->info[j]) == 1)
                swap(nz->info[i], nz->info[j], size);
}

