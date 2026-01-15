#include "structures.h"

cityListPos createCityList(char* name, int population)
{
	cityListPos newCity;
	newCity = malloc(sizeof(struct cityList));

	if (!newCity)
		return NULL;

	strcpy(newCity->name, name);
	newCity->population = population;
	newCity->next = NULL;

	return newCity;
}

int insertCityListSorted(cityListPos head, cityListPos newCity)
{
	if (head == NULL)
	{
		printf("\nLista gradova nije odredena!\n");
		return -1;
	}
	if (newCity == NULL)
	{
		printf("\nNovi grad nije odreden!\n");
		return -1;
	}

	cityListPos p;
	p = head;
	while (p->next != NULL && (p->next->population > newCity->population || (p->next->population == newCity->population && strcmp(p->next->name, newCity->name) < 0)))
		p = p->next;

	newCity->next = p->next;
	p->next = newCity;

	return 0;
}

int printCityList(cityListPos head)
{
	cityListPos p;
	p = head->next;

	while (p != NULL)
	{
		printf("\n %s (%d)\n", p->name, p->population);
		p = p->next;
	}

	return 0;
}

int findCityList(cityListPos head, int limit)
{
	cityListPos p;
	p = head->next;

	while (p != NULL)
	{
		if (p->population > limit)
			printf("\n %s (%d)\n", p->name, p->population);
		p = p->next;
	}

	return 0;
}

int freeCityList(cityListPos head)
{
	cityListPos temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}

	return 0;
}