#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person;
typedef struct Person* Position;

typedef struct Person
{
	char name[50];
	char lastName[50];
	int birthYear;
	Position next;
}Person;

int inputAtBegin(Position, int);
int inputAtEnd(Position, int);

int loop(Position);

int printInfo(Position);

int findElement(Position);
int eraseElement(Position);
int inputBeforeElement(Position);
int inputAfterElement(Position);

int sortList(Position);

int writeInFile(Position);
int printFromFile();

int main()
{
	char a = 'D', b;
	int temp, pos;

	Person head = { .next = NULL };

	if (loop(&head) == -1)
	{
		printf("Greska pri unosu broja osoba!\n");
		return -1;
	}

	while (a == 'D')
	{
		printf("Zelite li unijeti jos osoba (D ili N)? ");

		if (scanf(" %c", &a) != 1)
		{
			printf("Greska pri citanju!");
			return -1;
		}
		if (a == 'N')
			break;

		printf("Zelite li dodati ispred(1) ili iza(2) nekog elementa, ili na pocetak, odnosno kraj(3) liste? ");
		scanf("%d", &pos);

		switch (pos)
		{
		case 1:
			inputBeforeElement(&head);
			break;
		case 2:
			inputAfterElement(head.next);
			break;
		case 3:
			loop(&head);
			break;
		default:
			printf("Greska pri ucitavanju broja!\n");
			break;
		}
	}
	printInfo(head.next);

	printf("Zelite li pronaci osobu u listi (D ili N)? ");
	scanf(" %c", &b);

	if (b == 'D')
	{
		printf("Koje prezime zelite pronaci? ");
		temp = findElement(head.next);

		if (temp == NULL)
		{
			printf("Trazeno prezime se potoji u listi.\n");
			return 0;
		}
		else
			printf("Trazeno prezime je na poziciji: %d\n", temp + 1);
	}
	printInfo(head.next);

	printf("Zelite li izbrisati osobu iz liste (D ili N)? ");
	scanf(" %c", &b);

	if (b == 'D')
		eraseElement(&head);

	printInfo(head.next);

	sortList(&head);
	printf("Sortirana lista:\n");
	printInfo(head.next);

	writeInFile(head.next);
	printf("Ispis iz file-a:\n");
	printFromFile();

	return 0;
}

int inputAtBegin(Position q, int x)
{
	Position p = (Position)malloc(sizeof(Person));
	if (p == NULL)
	{
		printf("Greska u alokaciji memorije!\n ");
		return -1;
	}

	p->next = q->next;
	q->next = p;

	printf("Ime %d. osobe: ", x + 1);
	scanf(" %s", p->name);

	printf("Prezime %d. osobe: ", x + 1);
	scanf(" %s", p->lastName);

	printf("Godina rodenja %d. osobe: ", x + 1);
	scanf("%d", &p->birthYear);

	return 0;
}

int inputAtEnd(Position q, int x)
{
	Position p = (Position)malloc(sizeof(Person));
	if (p == NULL)
	{
		printf("Greska u alokaciji memorije!\n ");
		return -1;
	}

	while (q->next != NULL)
		q = q->next;

	p->next = q->next;
	q->next = p;

	printf("Ime %d. osobe: ", x + 1);
	scanf(" %s", p->name);

	printf("Prezime %d. osobe: ", x + 1);
	scanf(" %s", p->lastName);

	printf("Godina rodenja %d. osobe: ", x + 1);
	scanf("%d", &p->birthYear);

	return 0;
}

int loop(Position q)
{
	int n, i;
	char c;

	printf("Upisite koliko osoba zelite unijeti: ");
	if (scanf("%d", &n) != 1)
		return -1;

	printf("Unosite li na pocetak ili kraj liste (P ili K)? ");
	if (scanf(" %c", &c) != 1)
		return -1;

	switch (c)
	{
	case 'P':
		for (i = 0; i < n; i++)
			inputAtBegin(q, i);
		break;
	case 'K':
		for (i = 0; i < n; i++)
			inputAtEnd(q, i);
		break;
	default:
		printf("Greska pri unosu!");
		return -1;
		break;
	}

	return 0;
}

int printInfo(Position q)
{
	while (q != NULL)
	{
		printf("Ime: %s\n", q->name);
		printf("Prezime: %s\n", q->lastName);
		printf("Godina rodenja: %d\n", q->birthYear);

		q = q->next;
	}

	return 0;
}

int findElement(Position q)
{
	char find[50];
	int i = 0;

	scanf(" %s", &find);
	while (q != NULL && strcmp(q->lastName, find) != 0)
	{
		q = q->next;
		i++;
	}

	if (q == NULL)
		return NULL;

	return i;
}

int eraseElement(Position q)
{
	Position Del;
	char del[50];

	printf("Koje prezime zelite izbrisati? ");
	if (scanf(" %s", del) != 1)
	{
		printf("Greska pri citanju prezimena za brisanje!\n");
		return -1;
	}
	while (q->next != NULL && strcmp(q->next->lastName, del) != 0)
		q = q->next;

	Del = q->next;
	q->next = Del->next;

	Del->next = NULL;
	free(Del);

	return 0;
}

int inputBeforeElement(Position q)
{
	char find[50];
	Position p = (Position)malloc(sizeof(Person));

	if (p == NULL)
	{
		printf("Greska u alokaciji memorije!\n ");
		return -1;
	}

	printf("Ispred kojeg prezimena zelite upisivati? ");
	scanf(" %s", &find);

	while (q->next != NULL && strcmp(q->next->lastName, find) != 0)
		q = q->next;

	if (q == NULL)
		return NULL;

	p->next = q->next;
	q->next = p;

	printf("Ime osobe: ");
	scanf(" %s", p->name);

	printf("Prezime osobe: ");
	scanf(" %s", p->lastName);

	printf("Godina rodenja osobe: ");
	scanf("%d", &p->birthYear);

	return 0;
}

int inputAfterElement(Position q)
{
	char find[50];
	Position p = (Position)malloc(sizeof(Person));

	if (p == NULL)
	{
		printf("Greska u alokaciji memorije!\n ");
		return -1;
	}

	printf("Iza kojeg prezimena zelite upisivati? ");
	scanf(" %s", &find);

	while (q != NULL && strcmp(q->lastName, find) != 0)
		q = q->next;

	if (q == NULL)
		return NULL;

	p->next = q->next;
	q->next = p;

	printf("Ime osobe: ");
	scanf(" %s", p->name);

	printf("Prezime osobe: ");
	scanf(" %s", p->lastName);

	printf("Godina rodenja osobe: ");
	scanf("%d", &p->birthYear);

	return 0;
}

int sortList(Position q)
{
	Position p = (Position)malloc(sizeof(Person));
	if (p == NULL)
	{
		printf("Greska u alokaciji memorije!\n ");
		return -1;
	}

	Position temp = NULL, sort = NULL, first = q;
	int swap;

	do{
		swap = 0;

		q = first;
		p = first->next;

		while (p->next != sort)
			if (strcmp(p->lastName, p->next->lastName) > 0)
			{
				temp = p->next;
				p->next = temp->next;

				temp->next = p;
				q->next = temp;

				swap = 1;
				q = temp;
			}
			else {
				q = p;
				p = p->next;
			}

		sort = p;

	} while (swap);

	return 0;
}

int writeInFile(Position q)
{
	FILE* fp;
	fp = fopen("sortiranalista.txt", "w");

	if (fp == NULL)
	{
		printf("Greska pri otvaranju datoteke!\n");
		return -1;
	}

	while (q != NULL)
	{
		fprintf(fp, "%s %s %d", q->name, q->lastName, q->birthYear);
		q = q->next;
	}

	fclose(fp);

	return 0;
}

int printFromFile()
{
	FILE* fp;
	Person p;
	fp = fopen("sortiranalista.txt", "r");

	if (fp == NULL)
	{
		printf("Greska pri otvaranju datoteke!\n");
		return -1;
	}

	while (fscanf(fp, "%s %s %d", p.name, p.lastName, &p.birthYear) == 3)
		printf("%s %s (%d)\n", p.name, p.lastName, p.birthYear);

	fclose(fp);

	return 0;
}