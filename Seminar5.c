#include<stdio.h>
#include<malloc.h>

typedef struct Biblioteca Biblioteca;
typedef struct Nod Nod;

struct Biblioteca
{
    char* nume;
    int nrCarti;
    int nrCititori;
};

struct Nod
{
    Biblioteca info;
    Nod* next;
};

Biblioteca initialzare(const char* nume, int nrCarti, int nrCititori) {
    Biblioteca b;
    b.nume = (char*)malloc((strlen(nume) + 1) * sizeof(char));
    strcpy(b.nume, nume);
    b.nrCarti = nrCarti;
    b.nrCititori = nrCititori;
    return b;
}

Nod* inserareInceput(Nod* cap, Biblioteca b) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = initialzare(b.nume, b.nrCarti, b.nrCititori);
    nou->next = cap;
    return nou;
}

void afisareLista(Nod* cap) {
    while (cap != NULL)
    {
        printf("Biblioteca %s are %d carti si %d cititori\n", cap->info.nume, cap->info.nrCarti, cap->info.nrCititori);
        cap = cap->next;
    }
}

char* getBibliotecaNrCartiPerCititor(Nod* cap) {
    float max = 0;

    char* nume_aux = NULL;
    while (cap) {
        if (cap->info.nrCarti / cap->info.nrCititori > max) {
            max = cap->info.nrCarti / cap->info.nrCititori;
            nume_aux = cap->info.nume;

        }
        cap = cap->next;
    }
    char* nume = (char*)malloc(sizeof(char) * (strlen(nume_aux) + 1));
    strcpy(nume, nume_aux);
    return nume;
}

void inserareLaSfarsit(Nod** cap, Biblioteca b) {
    Nod* sfarsit = (Nod*)malloc(sizeof(Nod));
    sfarsit->info = initialzare(b.nume, b.nrCarti, b.nrCititori);
    if ((*cap) != NULL) {
        Nod* capA = (*cap);
        while (capA->next)
        {
            capA = capA->next;
        }
        capA->next = sfarsit;
    }
    else {
        (*cap) = sfarsit;

    }
}

void stergeLista(Nod** cap) {
    while ((*cap) != NULL) {
        free((*cap)->info.nume);
        Nod* copie = *cap;
        *cap = (*cap)->next;
        free(copie);

    }
}

void main() {
    Nod* cap = NULL;
    Biblioteca b1 = initialzare("Mihai Eminescu", 150, 20);
    cap = inserareInceput(cap, b1);
    Biblioteca b2 = initialzare("Ioan Slavici", 200, 30);
    cap = inserareInceput(cap, b2);
    Biblioteca b3 = initialzare("Tudor Arghezi", 100, 50);
    cap = inserareInceput(cap, b3);

    afisareLista(cap);
    char* nuumeDeafisat = getBibliotecaNrCartiPerCititor(cap);
    printf("Biblioteca cu media maxima  este %s \n", nuumeDeafisat);
    free(nuumeDeafisat);

    Biblioteca b4 = initialzare("ultimul", 2, 43);
    inserareLaSfarsit(&cap, b4);
    afisareLista(cap);
    stergeLista(&cap);
    afisareLista(cap);


    free(b1.nume);
    free(b2.nume);
    free(b3.nume);
    free(b4.nume);

}