#include "structures.h"

int main()
{
	countryListPos headList;
	headList = malloc(sizeof(struct countryList));
	if (!headList)
		return -1;

	headList->next = NULL;
	headList->root = NULL;

	countryTreePos rootTree;
	rootTree = NULL;

	if (loadData(headList, &rootTree) != 0)
	{
		printf("\nGreska pri ucitavanju podataka!\n");
		return -1;
	}

	printCountryList(headList);
	printCountryTree(rootTree);

	runMenu(headList, rootTree);
	deleteAll(headList, rootTree);

	return 0;
}