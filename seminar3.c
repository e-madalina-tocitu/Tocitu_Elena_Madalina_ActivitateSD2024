#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

struct Aeroport {
	int id;
	char* nume;
	int nrTerminale;
};

struct Aeroport* adaugareAeroport(struct Aeroport* vector, struct Aeroport aeroport, int* dimensiune)
{
	struct Aeroport* copie = (struct Aeroport*)malloc(sizeof(struct Aeroport) * ((*dimensiune) + 1));
	copie[(*dimensiune)] = aeroport;
	for (int i = 0; i < (*dimensiune); i++) {
		copie[i] = vector[i];
	}
	if (vector != NULL) {
		free(vector);
	}


	(*dimensiune)++;

	return copie;

};


struct Aeroport* citireFisier(const char* numeFsier, int* nrAeroporuri)
{

	struct Aeroport* vectorAeroporturi;
	vectorAeroporturi = NULL;

	FILE* f = fopen(numeFsier, "r");
	if (f != NULL) {
		(*nrAeroporuri) = 0;
		char buffer[100];
		while ((fgets(buffer, 99, f)) != NULL)
		{
			struct Aeroport aeroport;
			char demilitator[] = ",\n";
			char* token = strtok(buffer, demilitator);
			aeroport.id = atoi(token);
			token = strtok(NULL, demilitator);
			aeroport.nume = malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(aeroport.nume, token);
			token = strtok(NULL, demilitator);
			aeroport.nrTerminale = atoi(token);

			vectorAeroporturi = adaugareAeroport(vectorAeroporturi, aeroport, nrAeroporuri);

		}
	}
	fclose(f);
	return vectorAeroporturi;
}

void afisareAeroport(struct Aeroport* aeroport) {
	printf("Aeroportul cu ID: %d, nume:%s, numar terminale:%d.\n", aeroport->id, aeroport->nume, aeroport->nrTerminale);
}

void afisareVectorAeroporturi(struct Aeroport* aeroporturi, int dim) {
	printf("AFISARE VECTOR\n\n");
	for (int i = 0; i < dim; i++)
	{
		afisareAeroport(&aeroporturi[i]);
	}
}

void dezalocare(struct Aeroport** vect, int* dim) {
	for (int i = 0; i < (*dim); i++)
	{
		free((*vect)[i].nume);
	}
	free(*vect);
	*vect = NULL;
	*dim = 0;
}

void main()
{
	int dimensiune = 3;
	struct Aeroport* aeroporturi = NULL;
	aeroporturi = citireFisier("aeroport.txt", &dimensiune);
	afisareVectorAeroporturi(aeroporturi, dimensiune);


}