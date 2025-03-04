#include "operations.h"
#include <stdlib.h>
#include <string.h>

//functia de sortare a vectorului de senzori
//creez un nou vector in care pun mai intai toti vectorii
//de tip pmu, apoi pe cei tire
void sort(int nrofsensor, sensor *v2, sensor *v)
{
	//retin pozitia la care trebuie adaugat urmatorul senzor
	int count = 0;
	//adaug senzorii pmu in v2, vectorul sortat
	for (int j = 0; j < nrofsensor; ++j) {
		if (v[j].sensor_type == 1) {
			v2[count] = v[j];
			count++;
		}
	}
	//de la pozitia la care am ramas adaug senzorii tire
	for (int j = 0; j < nrofsensor; ++j) {
		if (v[j].sensor_type == 0) {
			v2[count] = v[j];
			count++;
		}
	}
	free(v);
}

//functia de printare a senzorilor
void print(int nrofsensor, sensor *v2, int *ok, sensor *v)
{
//a si b sunt variabile folosite pentru coding style
int i, b;
double a;
scanf("%d", &i);
//verific daca indicele primit este corect
if (i < 0 || i > nrofsensor) {
	printf("Index not in range!\n");
//daca indicele este corect, trec la printare
} else {
	//afisez caracteristicile senzorilor in functie de tipul lor
	if (v2[i].sensor_type == 0) {
		//senzor de tip tire
		printf("Tire Sensor\n");
		a = ((tire_sensor *)v2[i].sensor_data)->pressure;
		printf("Pressure: %.2lf\n", a);
		a = ((tire_sensor *)v2[i].sensor_data)->temperature;
		printf("Temperature: %.2lf\n", a);
		b = ((tire_sensor *)v2[i].sensor_data)->wear_level;
		printf("Wear Level: %d%%\n", b);
		b = ((tire_sensor *)v2[i].sensor_data)->performace_score;
		if (((tire_sensor *)v2[i].sensor_data)->performace_score != 0)
			printf("Performance Score: %d\n", b);
		else
			printf("Performance Score: Not Calculated\n");
	} else {
		//senzor de tip pmu
		printf("Power Management Unit\n");
		a = ((power_management_unit *)v2[i].sensor_data)->voltage;
		printf("Voltage: %.2lf\n", a);
		a = ((power_management_unit *)v2[i].sensor_data)->current;
		printf("Current: %.2lf\n", a);
		a = ((power_management_unit *)v2[i].sensor_data)->power_consumption;
		printf("Power Consumption: %.2lf\n", a);
		b = ((power_management_unit *)v2[i].sensor_data)->energy_regen;
		printf("Energy Regen: %d%%\n", b);
		b = ((power_management_unit *)v2[i].sensor_data)->energy_storage;
		printf("Energy Storage: %d%%\n", b);
	}
	}
}

//functia de mutare la stanga a elementelor pentru redimensionare
void move(int i, int *nrofsensor, sensor **v2)
{
	int j;
	//eliberez senzorul cerut
	free((*v2)[i].sensor_data);
	free((*v2)[i].operations_idxs);
	//le mut pe restul la stanga
	for (j = i; j < *nrofsensor - 1; ++j)
		(*v2)[j] = (*v2)[j + 1];
	//realoc vectorul sa fie cu un element in minus
	*v2 = realloc(*v2, (*nrofsensor - 1) * sizeof(sensor));
	(*nrofsensor)--;
}

//functia de stergere a senzorilor eronati
void clear(int *nrofsensor, sensor **v2)
{
int i;
//verific daca fiecare senzor este corect
for (i = 0; i < *nrofsensor; ++i) {
	int wear_level, energy_reg, energy;
	double temperature, pressure, voltage, current, pow;
	//variabile pentru coding style
	wear_level = ((tire_sensor *)(*v2)[i].sensor_data)->wear_level;
	energy_reg = ((power_management_unit *)(*v2)[i].sensor_data)->energy_regen;
	energy = ((power_management_unit *)(*v2)[i].sensor_data)->energy_storage;
	temperature = ((tire_sensor *)(*v2)[i].sensor_data)->temperature;
	pow = ((power_management_unit *)(*v2)[i].sensor_data)->power_consumption;
	voltage = ((power_management_unit *)(*v2)[i].sensor_data)->voltage;
	pressure = ((tire_sensor *)(*v2)[i].sensor_data)->pressure;
	current = ((power_management_unit *)(*v2)[i].sensor_data)->current;
	//verific daca valorile cerute se afla in limite, iar daca nu sterg senzorul
	//apoi scad numarul total de senzori si verific senzorul urmator
	if ((*v2)[i].sensor_type == 0) {
		if (pressure < 19 || pressure > 28) {
			move(i, nrofsensor, v2);
			i--;
		} else if (temperature < 0 || temperature > 120) {
			move(i, nrofsensor, v2);
			i--;
		} else if (wear_level < 0 || wear_level > 100) {
			move(i, nrofsensor, v2);
			i--;
		}
	} else {
		if (voltage < 10 || voltage > 20) {
			move(i, nrofsensor, v2);
			i--;
		} else if (current < -100 || current > 100) {
			move(i, nrofsensor, v2);
			i--;
		} else if (pow < 0 || pow > 1000 || energy < 0 || energy > 100) {
			move(i, nrofsensor, v2);
			i--;
		} else if (energy_reg < 0 || energy_reg > 100) {
			move(i, nrofsensor, v2);
			i--;
		}
	}
	}
}

int main(int argc, char const *argv[])
{
	//am deschis fisierul si am citit caracteristicile senzorilor
	FILE *file = fopen(argv[1], "rb");
	int nrofsensor, i;
	fread(&nrofsensor, sizeof(int), 1, file);
	sensor *v = malloc(nrofsensor * sizeof(sensor));
	for (i = 0; i < nrofsensor; ++i) {
		//am citit tipul, apoi caracteristicile in functie de tip
		fread(&v[i].sensor_type, sizeof(int), 1, file);
		if (v[i].sensor_type == 0) {
			v[i].sensor_data = malloc(sizeof(tire_sensor));
			fread(v[i].sensor_data, sizeof(tire_sensor), 1, file);
			fread(&v[i].nr_operations, sizeof(int), 1, file);
			v[i].operations_idxs = malloc(v[i].nr_operations * sizeof(int));
			fread(v[i].operations_idxs, sizeof(int), v[i].nr_operations, file);
		} else {
			v[i].sensor_data = malloc(sizeof(power_management_unit));
			fread(v[i].sensor_data, sizeof(power_management_unit), 1, file);
			fread(&v[i].nr_operations, sizeof(int), 1, file);
			v[i].operations_idxs = malloc(v[i].nr_operations * sizeof(int));
			fread(v[i].operations_idxs, sizeof(int), v[i].nr_operations, file);
		}
	}
	//inchid fisierul, apoi adaug operatiile intr-un vector
	fclose(file);
	void *ops[8];
	get_operations((void **)ops);
	//aloc vectorul sortat si sortez vectorul v initial
	sensor *v2 = malloc(nrofsensor * sizeof(sensor));
	sort(nrofsensor, v2, v);
	char *op = malloc(100 * sizeof(char));
	int ok = 1;
	while (scanf("%s", op)) {
		if (strcmp(op, "print") == 0)
			print(nrofsensor, v2, &ok, v);
		//pentru senzorul cerut efectuez operatiile sale, cu
		//ajutorul vectorului de pointeri la functii creat
		if (strcmp(op, "analyze") == 0) {
			scanf("%d", &i);
			for (int j = 0; j < v2[i].nr_operations; ++j) {
				int idx = v2[i].operations_idxs[j];
				((void (*)(void *))ops[idx])(v2[i].sensor_data);
			}
		}
		if (strcmp(op, "clear") == 0)
			clear(&nrofsensor, &v2);
		//operatia de exit, eliberez fiecare senzor cu caracteristicile
		//lui, apoi eliberez vectorul de senzori
		if (strcmp(op, "exit") == 0) {
			for (i = 0; i < nrofsensor; ++i) {
				free(v2[i].operations_idxs);
				free(v2[i].sensor_data);
			}
			free(v2);
			free(op);
			break;
		}
	}
	return 0;
}
