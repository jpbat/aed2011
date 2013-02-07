/*
 * João Paulo Batista Ferreira
 * 2009113274
 * Algoritmos e Estruturas de Dados - TP3 exE
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct item {
	char word[256];
	int counter;
}item;

typedef struct node {
	item info;
	struct node *left;
	struct node *right;
}node;

typedef struct node* nodePtr;

void visita (nodePtr leaf)
{
	printf("%s %d\n", leaf->info.word, leaf->info.counter);
}

void emOrdem (nodePtr leaf)
{
	if (leaf != NULL)
	{
		emOrdem(leaf->left);
		visita (leaf);
		emOrdem(leaf->right);
	}
}

void eraseTree(nodePtr leaf)
{
	if (leaf == NULL)
		return;
	eraseTree(leaf->left);
	eraseTree(leaf->right);
	free(leaf);
}

nodePtr createNode(char* word)
{
	nodePtr aux;
	aux = (nodePtr) malloc(sizeof(node));
	strcpy(aux->info.word, word);
	aux->info.counter = 1;
	return aux;
}

nodePtr rightRotation(nodePtr t)
{
	nodePtr t2 = t->left;
	t->left = t2->right;
	t2->right = t;
	return t2;	
}

nodePtr leftRotation(nodePtr t)
{
	nodePtr t2 = t->right;
	t->right = t2->left;
	t2->left = t;
	return t2;	
}
	
nodePtr splay(char* word, nodePtr leaf)
{
	if(leaf->left != NULL && strcmp(leaf->left->info.word, word)==0)
		return rightRotation(leaf);

	else if (leaf->right != NULL && strcmp(leaf->right->info.word, word)==0)
		return leftRotation(leaf);
	
	return leaf;
}

nodePtr addNode(char* word, nodePtr leaf)
{
	if(leaf == NULL)
		return createNode(word);
	
	else if(strcmp(word,leaf->info.word) > 0)
		leaf->right = addNode(word, leaf->right);
	
	else if(strcmp(word,leaf->info.word ) < 0)
		leaf->left = addNode(word, leaf->left);
		
	else
		leaf->info.counter++;
	
	return splay(word, leaf);
}

nodePtr worker(char* word, nodePtr tree)
{
	int i, size = strlen(word);
	
	for (i = 0; i < size; i++)
		word[i] = tolower(word[i]);
		
	tree = addNode(word, tree);
	
	return tree;
}

int main()
{
	nodePtr tree=NULL;
	char word[256];
	
	while( (scanf("%s", word)) != EOF )
		tree = worker (word, tree);
	
	emOrdem(tree);
	
	eraseTree(tree);

	return 0;
}
