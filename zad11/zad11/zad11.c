#include "structures.h"

int main()
{
	hashTablePos table;
	table = createHashTable(HASH_SIZE);
	if (!table)
		return -1;

	if (loadData(table) != 0)
	{
		printf("\nGreska pri ucitavanju!\n");
		return -1;
	}
	printHash(table);

	char name[MAX_NAME];
	int limit;

	printf("\nUnesite drzavu: ");
	scanf(" %s", name);

	printf("\nUnesite limit populacije: ");
	scanf("%d", &limit);

	countryPos found;
	found = findCountry(table, name);
	if (!found)
		printf("\ndrzava ne postoji");
	else
		printCityTree(found->root, limit);

	freeHash(table);
	return 0;
}