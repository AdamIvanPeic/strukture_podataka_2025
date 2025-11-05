#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct postfix* Position;
typedef struct postfix
{
	double num;
	Position next;
}postfix;

int push(Position, double);
double pop(Position);

int getPostfixValue(Position);
int calcPostfixValue(Position, char);

int main()
{
	postfix head = { .next = NULL };

	getPostfixValue(&head);
	printf("Rezultat: %lf\n", head.next->num);

	return 0;
}

int push(Position q, double n)
{
	Position p = (Position)malloc(sizeof(postfix));

	if (p == NULL)
	{
		printf("Greska pri alokaciji memorije!\n");
		return -1;
	}

	p->num = n;
	p->next = q->next;
	q->next = p;

	return 0;
}

double pop(Position q)
{
	if (q->next == NULL)
	{
		printf("Stog je prazan!\n");
		return 0;
	}

	Position temp = q->next;
	double value = temp->num;

	q->next = temp->next;
	temp->next = NULL;

	free(temp);
	return value;
}

int getPostfixValue(Position q)
{
	FILE* fp = fopen("postfix.txt", "r");

	char buffer[255];
	if (fp == NULL)
	{
		printf("Greska pri otvaranju datoteke!\n");
		return -1;
	}

	if (!fgets(buffer, sizeof(buffer), fp))
	{
		printf("Greska pri ucitavanju datoteke!\n");

		fclose(fp);
		return -1;
	}

	fclose(fp);

	char charValue;
	for (int i = 0; buffer[i] != '\0'; i++)
	{
		charValue = buffer[i];
		if (charValue >= '0' && charValue <= '9')
			push(q, charValue - '0');
		else if (charValue == '+' || charValue == '-' || charValue == '*' || charValue == '/')
			calcPostfixValue(q, charValue);
	}

	return 0;
}

int calcPostfixValue(Position q, char c)
{
	double a = pop(q);
	double b = pop(q);
	double calcOutput = 0;

	switch (c)
	{
	case '+':
		calcOutput = b + a;
		break;
	case '-':
		calcOutput = b - a;
		break;
	case '*':
		calcOutput = b * a;
		break;
	case '/':
		if (a == 0)
		{
			printf("Dijeljenje nulom!\n");
			return -1;
		}
		calcOutput = b / a;
		break;
	default:
		printf("Greska u znakovima!\n");
		return -1;
	}

	push(q, calcOutput);

	return 0;
}