#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct tree* treePos;

struct tree {
	int value;
	treePos left;
	treePos right;
};

treePos insertTree(treePos, int);
treePos findMin(treePos);
treePos deleteTree(treePos, int);
treePos searchTree(treePos, int);

int inOrder(treePos);
int preOrder(treePos);
int postOrder(treePos);
int height(treePos);
int printLevel(treePos, int);
int levelOrder(treePos);

treePos freeTree(treePos);

int main()
{
	treePos root = NULL;
	treePos found = NULL;

	int choice = 1;
	int value;

	while (choice != 0)
	{
		printf("\n-----IZBORNIK-----\n");
		printf("\n1 - Unos elementa\n");
		printf("\n2 - InOrder ispis\n");
		printf("\n3 - PreOrder ispis\n");
		printf("\n4 - PostOrder ispis\n");
		printf("\n5 - LevelOrder ispis\n");
		printf("\n6 - Pretrazivanje elementa\n");
		printf("\n7 - Brisanje elementa\n");
		printf("\n8 - Brisanje cijelog stabla\n");
		printf("\n0 - Izlaz\n");
		printf("\nOdaberite: \n");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1: {
			printf("\nUnesite vrijednost: ");
			scanf("%d", &value);

			root = insertTree(root, value);
			break;
		}
		case 2: {
			printf("\nInOrder: \n");
			inOrder(root);

			printf("\n");
			break;
		}
		case 3: {
			printf("\nPreOrder: \n");
			preOrder(root);

			printf("\n");
			break;
		}
		case 4: {
			printf("\nPostOrder: \n");
			postOrder(root);

			printf("\n");
			break;
		}
		case 5: {
			printf("\nLevelOrder: \n");
			levelOrder(root);

			break;
		}
		case 6: {
			printf("\nElement kojeg trazite: ");
			scanf("%d", &value);

			found = searchTree(root, value);

			if (found != NULL)
				printf("\nElement %d postoji u stablu.\n", found->value);
			else
				printf("\nElement %d nije pronaden.\n", value);

			break;
		}
		case 7: {
			printf("\nUnesite element za brisanje: ");
			scanf("%d", &value);

			root = deleteTree(root, value);
			break;
		}
		case 8: {
			root = freeTree(root);
			printf("Stablo je obrisano.\n");

			break;
		}
		case 0: {
			root = freeTree(root);
			printf("\nIzasli ste iz programa.\n");

			break;
		}
		default:
			printf("\nUnijeli ste netocan broj.\n");
		}
	}

	return 0;
}

treePos insertTree(treePos root, int value)
{
	if (root == NULL)
	{
		root = (treePos)malloc(sizeof(struct tree));

		root->value = value;
		root->left = NULL;
		root->right = NULL;

		return root;
	}

	if (value < root->value)
		root->left = insertTree(root->left, value);
	else if (value > root->value)
		root->right = insertTree(root->right, value);
	else
		printf("\nVrijednost vec postoji u stablu.\n");

	return root;
}

treePos findMin(treePos root)
{
	if (root == NULL)
		return NULL;
	while (root->left != NULL)
		root = root->left;

	return root;
}

treePos deleteTree(treePos root, int value)
{
	treePos temp;

	if (root == NULL)
		return NULL;

	if (value < root->value)
		root->left = deleteTree(root->left, value);
	else if (value > root->value)
		root->right= deleteTree(root->right, value);
	else
	{
		if (root->left != NULL && root->right != NULL)
		{
			temp = findMin(root->right);

			root->value = temp->value;
			root->right = deleteTree(root->right, temp->value);
		}
		else
		{
			temp = root;

			if (root->left == NULL)
				root = root->right;
			else
				root = root->left;

			free(temp);
		}
	}

	return root;
}

treePos searchTree(treePos root, int value)
{
	if (root == NULL || root->value == value)
		return root;

	if (value < root->value)
		return searchTree(root->left, value);
	else
		return searchTree(root->right, value);
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

int preOrder(treePos root)
{
	if (root != NULL)
	{
		printf("%d ", root->value);
		preOrder(root->left);
		preOrder(root->right);
	}

	return 0;
}

int postOrder(treePos root)
{
	if (root != NULL)
	{
		postOrder(root->left);
		postOrder(root->right);
		printf("%d ", root->value);
	}

	return 0;
}

int height(treePos root)
{
	int l, r;

	if (root == NULL)
		return 0;

	l = height(root->left);
	r = height(root->right);

	if (l > r)
		return l + 1;
	else
		return r + 1;
}

int printLevel(treePos root, int level)
{
	if (root == NULL)
		return 0;

	if (level == 1)
		printf("%d ", root->value);
	else if (level > 1)
	{
		printLevel(root->left, level - 1);
		printLevel(root->right, level - 1);
	}

	return 0;
}

int levelOrder(treePos root)
{
	if (root == NULL)
	{
		printf("\nStablo je prazno.\n");
		return 0;
	}

	int h, i;
	h = height(root);

	for (int i = 1; i <= h; i++)
	{
		printLevel(root, i);
		printf("\n");
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