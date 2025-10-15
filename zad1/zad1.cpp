#define _CRT_SECURE_NO_WARNINGS
#define FILE_NOT_OPENED (-1)
#define MAX_LINE (1024)
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define MAX_POINTS_NUM 120
#define MAX_LENGTH 100

typedef struct Student
{
	char firstName[MAX_LENGTH];
	char lastName[MAX_LENGTH];
	double absPoints;
} Student;

int lineCounter();
int studentDataInput(Student*, int);
int studentDataOutput(Student);

int main()
{
	Student* student;

	int counter = lineCounter();
	if (!counter)
	{
		printf("Greska pri racunanju redova!\n");
		return 0;
	}

	student = (Student*)malloc(sizeof(Student) * counter);
	if (student == NULL)
	{
		printf("Greska pri postavljanju podataka studenata!\n");
		return 0;
	}
	studentDataInput(student, counter);

	for (int i = 0; i < counter; i++)
		studentDataOutput(student[i]);

	free(student);

	return 0;
}

int lineCounter()
{
	FILE* file = fopen("studenti.txt", "r");
	if (file == NULL)
		return 0;
	
	int counter = 0;
	char ch;

	while ((ch = fgetc(file)) != EOF)
		if (ch == '\n')
			counter++;

	fclose(file);

	return counter;
}

int studentDataInput(Student* student, int n)
{
	FILE* file = fopen("studenti.txt", "r");

	for (int i = 0; i < n; i++)
		fscanf(file, "%s %s %lf", student[i].firstName, student[i].lastName, &student[i].absPoints);

	fclose(file);
	
	return 0;
}
int studentDataOutput(Student student)
{
	if (student.absPoints > MAX_POINTS_NUM)
	{
		printf("Student %s %s ima vise bodova od maximalnih!\n", student.firstName, student.lastName);
		printf("\n");
	}
	else
	{
		printf("Ime: %s\n", student.firstName);
		printf("Prezime: %s\n", student.lastName);
		printf("Broj absolutnih bodova: %.2lf\n", student.absPoints);
		printf("Broj relativnih bodova: %.2lf\n", (student.absPoints / MAX_POINTS_NUM) * 100);
		printf("\n");
	}

	return 0;
}
