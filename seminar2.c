#include<stdio.h>
#include<malloc.h>



struct Calculator {
	char* serie;
	float ptret;
	int nrPorturi;
};

struct Calculator initializare(const char* serie, float pret, int nrPorturi) {
	struct Calculator c;
	c.serie = (char*)malloc(sizeof(char) * strlen(serie) + 1);
	strcpy(c.serie, serie);
	c.ptret = pret;
	c.nrPorturi = nrPorturi;
	return c;

}

struct Calculator* copiazaNCalculatoare(struct Calculator* calculatoare, int nrCalculatoare, int nrCalculatoareCopiate)
{
	struct Calculator* copiate = (struct Calculator*)malloc(sizeof(struct Calculator) * nrCalculatoareCopiate);
	for (int i = 0; i < nrCalculatoareCopiate; i++) {
		copiate[i] = calculatoare[i];
		copiate[i].serie = (char*)malloc(sizeof(char) * (1 + strlen(calculatoare[i].serie)));
		strcpy(copiate[i].serie, calculatoare[i].serie);
	}
	return copiate;
};

void afisareCalculator(struct Calculator c) {
	printf("Calculatorul cu seria %s, costa %f si are %d porturi\n", c.serie, c.ptret, c.nrPorturi);
}

void afisareVectorCalculatoare(struct Calculator* vector, int nrCalculatoare) {
	if (nrCalculatoare > 0 && vector != NULL) {
		for (int i = 0; i < nrCalculatoare; i++)
		{
			afisareCalculator(vector[i]);
		}
	}
}

struct Calculator* copiazaCalculatoareCuMultePorturi(struct Calculator* calculatoare, int nrCalculatoare, int pragNrPorturi, int* nrCalculatoaarePorturi) {
	*nrCalculatoaarePorturi = 0;
	for (int i = 0; i < nrCalculatoare; i++) {
		if (calculatoare[i].nrPorturi > pragNrPorturi) {
			(*nrCalculatoaarePorturi)++;
		}
	}
	struct Calculator* v = (struct Calculator*)malloc(sizeof(struct Calculator) * (*nrCalculatoaarePorturi));
	int k = 0;
	for (int i = 0; i < nrCalculatoare; i++) {
		if (calculatoare[i].nrPorturi > pragNrPorturi) {
			v[k++] = initializare(calculatoare[i].serie, calculatoare[i].ptret, calculatoare[i].nrPorturi);

		}
	}
	return v;
}

struct Calculator* CopiazaCalculatorPret(struct Calculator* vector, int nrCalculatoare, float pret) {
	for (int i = 0; i < nrCalculatoare; i++) {
		if (vector[i].ptret == pret) {
			return &vector[i];
		}
	}
	return NULL;
}

void dezalocare(struct Calculator** vector, int* dim) {
	for (int i = 0; i < (*dim); i++) {
		free((*vector)[i].serie);
	}

	free(*vector);
	*vector = NULL;
	*dim = 0;
}


void main() {

	int nrCalculatoare = 5;
	struct Calculator* calculatoare = (struct Calculator*)malloc(sizeof(struct Calculator) * nrCalculatoare);
	for (int i = 0; i < nrCalculatoare; i++) {
		calculatoare[i] = initializare("1234567890", i * 20 + 10, i + 1);
	}
	afisareVectorCalculatoare(calculatoare, nrCalculatoare);

	int nrCalculatoareCopiate = 3;
	struct Calculator* calculatoareCopiate = copiazaNCalculatoare(calculatoare, nrCalculatoare, nrCalculatoareCopiate);

	printf("\n \n");

	afisareVectorCalculatoare(calculatoareCopiate, nrCalculatoareCopiate);

	printf("\n \n");
	int nrCalculatoarePorturi = 0;
	struct Calculator* calculatoarePorturi = copiazaCalculatoareCuMultePorturi(calculatoare, nrCalculatoare, 3, &nrCalculatoarePorturi);
	afisareVectorCalculatoare(calculatoarePorturi, nrCalculatoarePorturi);

	printf("\n \n");
	int pretM = 90.0;
	struct Calculator* calculatorPret = CopiazaCalculatorPret(calculatoare, nrCalculatoare, pretM);
	if (calculatorPret != NULL) {
		afisareCalculator(*calculatorPret);
	}
	else {
		printf("Nu exista calculator cu pretul %.2f.\n", pretM);
	}


}