#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person;
typedef struct Person* Position;

typedef struct Person
{
	char name[50];
	char surname[50];
	int birthYear;
	Position next;
}Person;

Person* insert();
int Print(Person*);
int sameString(const char*, const char*);

Person* Start(Person*, Person*);
Person* End(Person*, Person*);

Person* Find(Person*, const char*);
Person* deleteSurname(Person*, const char*);

Person* clean(Person*);

int main()
{

	Person Head = { .name = "",.surname = "",.birthYear = 0, .next = NULL };

	printf("\nUnesite 4 osobe: ");
	printf("\nOsoba br 1.:");
	Person* P1 = insert();
	Head.next = P1;

	printf("\nOsoba br 2.:");
	Person* P2 = insert();
	End(Head.next, P2);

	printf("\nOsoba br 3.:");
	Person* P3 = insert();
	End(Head.next, P3);

	printf("\nOsoba br 4.:");
	Person* P4 = insert();
	End(Head.next, P4);
	Print(Head.next);
	
	char findSurname[50];
	printf("\nUpisite prezime: ");
	scanf(" %s", &findSurname);

	Person* Found = Find(Head.next, findSurname);
	if (Found)
		printf("\nTrazena osoba: %s %s %d", Found->name, Found->surname, Found->birthYear);
	else
		printf("\nOsoba nije pronadena!");

	char delSurname[50];
	printf("\nUpisite prezime za izbrisati: ");
	scanf(" %s", &delSurname);
	Head.next = deleteSurname(Head.next, delSurname);

	Print(Head.next);

	Head.next = clean(Head.next);

	return 0;
}

Person* insert()
{
	Person* new = (Person*)malloc(sizeof(Person));

	if (!new)
	{
		printf("\nGreska pri alokaciji memorije!");
		return NULL;
	}

	printf("\nUnesi ime: ");
	scanf(" %s", new->name);

	printf("\nUnesi prezime: ");
	scanf(" %s", new->surname);

	printf("\nUnesi godinu rodenja: ");
	scanf("%d", &new->birthYear);

	new->next = NULL;
	return new;
}

int Print(Person* head)
{
	if (head == NULL)
	{
		printf("\nLista je prazna.");
		return -1;
	}

	printf("\nLista osoba: ");
	Person* temp = head;
	while (temp != NULL)
	{
		printf("\nIme: %s\nPrezime: %s\n Godina rodenja: %d", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}
	return 0;
}
Person* Start(Person* head, Person* nP)
{
	nP->next = head;
	return nP;
}

Person* End(Person* head, Person* nP)
{
	Person* temp = head;
	if (head == NULL)
		return nP;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = nP;
	return head;
}
int sameString(const char* word1, const char* word2)
{
	while (*word1 && *word2)
	{
		if (*word1 != *word2)
			return 0;
		word1++;
		word2++;
	}
	return 1;
}
Person* Find(Person* head, const char* findSurname)
{
	while (head != NULL)
	{
		if (sameString(head->surname, findSurname))
			return head;
		head = head->next;
	}
	return NULL;
}
Person* deleteSurname(Person* head, const char* delSurname)
{
	Person* temp = NULL;
	Person* anoth = head;

	while (anoth != NULL)
	{
		if (sameString(anoth->surname, delSurname))
		{
			if (temp == NULL)
			{
				Person* newHead = anoth->next;
				free(anoth);
				return newHead;
			}
			else
			{
				temp->next = anoth->next;
				free(anoth);
				return head;
			}
		}
		temp = anoth;
		anoth = anoth->next;
	}

	printf("\nPrezime %s nije pronadeno!", delSurname);
	return head;
}

Person* clean(Person* head)
{
	Person *temp;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
	return NULL;
}