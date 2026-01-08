#include "racuni.h"
#include "artikl.h"

int main()
{
	billList* list = listForBills();

	FILE* fp = fopen("racuni.txt", "r");
	if (!fp)
	{
		printf("\nDatoteka nije otvorena!\n");
		return -1;
	}

	char fileName[50];
	while (fscanf(fp, "%49s", fileName) == 1)
	{
		Bill fresh = billFromFile(fileName);

		if (fresh)
			sortBill(list, fresh);
		else
			printf("\nNe moze se otvoriti %s\n", fileName);
	}

	fclose(fp);

	int choice;
	do{
		printf("\n-----------MENU-----------\n");
		printf("1 - Pronadi potrosnju za artikl u nekom periodu.\n");
		printf("2 - Najskuplji artikl.\n");
		printf("3 - Najjeftiniji artikl.\n");
		printf("4 - Najcesci artikl.\n");
		printf("5 - Najrijedi artikl.\n");
		printf("6 - Ukupna potrosnja.\n");
		printf("7 - Ispisi sortirano sve artikle.\n");
		printf("8 - Artikl s najvecom potrosnjom.\n ");
		printf("9 - Artikl s najmanjom potrosnjom.\n ");
		printf("10 - Prosjecna cijena artikla.\n ");
		printf("0 - Izlaz.\n");
		printf("--------------------------\n");

		printf("Odaberite: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1: {
			findArticle(list);
		}break;
		case 2: {
			priciest(list);
		}break;
		case 3: {
			cheapest(list);
		}break;
		case 4:
			mostCommon(list);
			break;
		case 5:
			rarest(list);
			break;
		case 6:
			total(list);
			break;
		case 7:
			printAllArticlesSorted(list);
			break;
		case 8: {
			maxConsumption(list);
		}break;
		case 9: {
			minConsumption(list);
		}break;
		case 10:{
			averagePrice(list);
		}break;
		case 0:
			printf("\nIzasli ste iz programa.");
			break;
		default:
			printf("\nOvaj broj nije jedna od opcija!\n");
			break;
		}
	} while (choice != 0);

	freeBill(list);
	return 0;
}