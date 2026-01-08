#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

typedef struct tree* treePos;

struct tree {
	int value;
	treePos left;
	treePos right;
};

treePos insertTree(treePos, int);

int replace(treePos);
int inOrder(treePos);
int inOrderFile(treePos, FILE*);

treePos freeTree(treePos);


int main()
{
	treePos root = NULL;

	int value,n,i;

	FILE* fp = NULL;
	fp = fopen("inorder.txt", "w");
	if (fp == NULL)
		return 0;

	int arr[] = {2,5,7,8,11,1,4,2,3,7};
	int size = sizeof(arr) / sizeof(arr[0]);

	for (i = 0; i < size; i++)
		root = insertTree(root, arr[i]);

	printf("\nInOrder prije replace: ");
	inOrder(root);

	fprintf(fp, "\nInOrder prije replace: ");
	inOrderFile(root, fp);

	replace(root);

	printf("\nInOrder nakon replace: ");
	inOrder(root);

	fprintf(fp, "\nInOrder nakon replace: ");
	inOrderFile(root, fp);

	root = freeTree(root);

	srand((unsigned int)time(NULL));
	n = 10 + rand() % 6;

	for (i = 0; i < n; i++)
	{
		value = 10 + rand() % 80;
		root = insertTree(root, value);
	}

	replace(root);

	printf("\nInOrder random stabla: ");
	inOrder(root);

	fprintf(fp, "\nInOrder random stabla: ");
	inOrderFile(root, fp);

	fclose(fp);
	root = freeTree(root);
	return 0;
}

treePos insertTree(treePos root, int value)
{
	if (root == NULL)
	{
		root = (treePos)malloc(sizeof(struct tree));

		if (root == NULL)
			return NULL;

		root->value = value;
		root->left = NULL;
		root->right = NULL;

		return root;
	}

	if (value >= root->value)
		root->left = insertTree(root->left, value);
	else
		root->right = insertTree(root->right, value);

	return root;
}

int inOrder(treePos root)
{
	if (root != NULL)
	{
		inOrder(root->left);
		printf("%d ", root->value);
		inOrder(root->right);
	}

	return 0;
}

int replace(treePos root)
{
	if (root == NULL)
		return 0;

	int old;

	old = root->value;
	root->value = replace(root->left) + replace(root->right);

	return old + root->value;
}

int inOrderFile(treePos root, FILE* fp)
{
	if (root != NULL)
	{
		inOrderFile(root->left, fp);
		fprintf(fp, "%d ", root->value);
		inOrderFile(root->right, fp);
	}

	return 0;
}

treePos freeTree(treePos root)
{
	if (root != NULL)
	{
		freeTree(root->left);
		freeTree(root->right);
		free(root);
	}

	return NULL;
}