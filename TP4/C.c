/*
 * JoÃ£o Paulo Batista Ferreira
 * 2009113274
 * Algoritmos e Estruturas de Dados - TP4 exC
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct coord {
	int d;
	int m;
	int s;
}coord;

typedef struct node {
	coord lat;
	coord lon;
	double la;
	double lo;
	int ind;
	int printable;
	char text[50];
}node;

typedef struct node* nodePtr;

void print(nodePtr n)
{
	printf("%d %d %d %d %d %d%s\n", 
		n->lat.d, n->lat.m, n->lat.s, 
		n->lon.d, n->lon.m, n->lon.s, 
		n->text);
}

int compare(nodePtr a, nodePtr b)
{
	if (a->la > b->la)
		return 1;
		
	if (a->la < b->la)
		return -1;
	
	if (a->lo > b->lo)
		return 1;
		
	if (a->lo < b->lo)
		return -1;
		
	return 0;
}

void swap(nodePtr a, nodePtr b)
{
	node tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

nodePtr* rem(nodePtr *POIs, int del, int *size)
{
	int i;

	nodePtr *n = (nodePtr*) malloc( (*size-1) * sizeof(nodePtr));

	for (i = 0; i < del; i++)
		n[i] = POIs[i];

	for (i++; i < *size; i++)
		n[i - 1] = POIs[i];

	free(POIs);

	(*size)--;

	return n;
}

void sortPivot(nodePtr* POIs, int lower, int pivot, int higher)
{
	if (compare(POIs[lower],POIs[pivot]) > 0)
		swap(POIs[lower], POIs[pivot]);

	if (compare(POIs[pivot], POIs[higher]) > 0)
		swap(POIs[pivot], POIs[higher]);

	if (compare(POIs[lower], POIs[pivot]) > 0)
		swap(POIs[lower], POIs[pivot]);
}

void bubblesort(nodePtr *POIs, int size)
{
	int i, j, change = 1, comp;

	for (i = 0 ; i<size && change ; i++)
	{
		change = 0;
		for (j = 0; j < size - i -1; j++)
		{
			comp = compare( POIs[j], POIs[j+1]);
			if ( comp == 1 )
			{
				swap(POIs[j], POIs[j+1]);
				change = 1;
			}
		}
	}
}

void quicksort(nodePtr* POIs, int m, int n)
{
	nodePtr pivot;
	int i,j,k;
	
	if( m < n)
	{	
		k = (m+n)/2;
		i = m+1;
		j = n;

		sortPivot(POIs, i, k, j);

		pivot = POIs[m];

		while(i <= j)
		{
			while((i <= n) && (compare(POIs[i],pivot)!=1))
				i++;
			while((j >= m) && (compare(POIs[j], pivot)==1))
				j--;
			if( i < j)
				swap(POIs[i], POIs[j]);
		}
		swap(POIs[m], POIs[j]);
		quicksort(POIs,m,j-1);
		quicksort(POIs,j+1,n);
	}
}

double toDouble(coord n)
{
	double result=0.0;
	
	result += n.s;
	result /= 60;
	result += n.m;
	result /= 60;
	result += n.d;
	
	return result;
}

int main(int argc, char **argv)
{
	int size, i;
	nodePtr* POIs;
	
	scanf("%d", &size);
	
	POIs = (nodePtr*) malloc (size*sizeof(nodePtr));
	
	for (i=0 ; i<size ; i++)
	{	
		POIs[i] = (nodePtr) malloc (sizeof(node));
		scanf("%d", &POIs[i]->lat.d);
		scanf("%d", &POIs[i]->lat.m);
		scanf("%d", &POIs[i]->lat.s);
		scanf("%d", &POIs[i]->lon.d);
		scanf("%d", &POIs[i]->lon.m);
		scanf("%d", &POIs[i]->lon.s);
		POIs[i]->la = toDouble(POIs[i]->lat);
		POIs[i]->lo = toDouble(POIs[i]->lon);
		POIs[i]->printable = 1;
		POIs[i]->ind = i;
		scanf("%[^\n]",POIs[i]->text);
	}
	
 	quicksort(POIs, 0, size-1);
	
	for (i = 0; i < size - 1; i++)
	{
		if ( compare(POIs[i],POIs[i+1]) == 0 )
		{
			if (POIs[i]->ind > POIs[i+1]->ind)
				POIs = rem(POIs, i, &size);
			else
				POIs = rem(POIs, i+1, &size);
			i--;
		}
	}
	
	for (i=0 ; i<size ; i++)
	{	
		print(POIs[i]);
		free(POIs[i]);
	}	
	
	free(POIs);
	
	return 0;
}
