#include "options.h"
#include "directory.h"
#include "stack.h"

int main()
{
	dirPosition rootDir;
	rootDir = createDirectory("C");

	if (!rootDir)
		return -1;

	stackPosition headStack = malloc(sizeof(struct stack));
	if (!headStack)
		return -1;

	headStack->dirLevel = NULL;
	headStack->next = NULL;

	push(headStack, rootDir);

	runOptions(rootDir, headStack);

	freeStack(headStack);
	free(headStack);
	freeTree(rootDir);

	return 0;
}