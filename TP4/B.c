/*
 * João Paulo Batista Ferreira
 * 2009113274
 * Algoritmos e Estruturas de Dados - TP4 exB
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/time.h>
#include <unistd.h>

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
	char text[50];
	struct node* next;
}node;

typedef struct node* nodePtr;

nodePtr* aux;

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

void merge(nodePtr* POIs, int size) 
{
	int mid, comp, i, j, k;

	mid = size / 2;

	i = 0;
	j = mid;
	k = 0;

	for (k=0 ; i<mid && j<size ; k++) 
	{
		comp = compare(POIs[i], POIs[j]);
		
		if (comp == -1) 
			aux[k]=POIs[i++];
		
		else if (comp == 1)
			aux[k]=POIs[j++];
		
		else
			aux[k]=POIs[j++];
	}

	if (i == mid)
		while (j < size)
			aux[k++]= POIs[j++];
	
	else
		while (i < mid)
			aux[k++]= POIs[i++];
			
	for (i = 0; i < size; ++i)
		POIs[i]= aux[i];
}
 
void mergesort(nodePtr* vec, int size)
{
	int mid;

	if (size > 1) 
	{
		mid = size / 2;
		mergesort(vec, mid);
		mergesort(vec + mid, size - mid);
		merge(vec, size);
	}
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

double getCurrentTimeNano()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec*1000000000.0 + t.tv_usec;
}

void printTimeElapsed(double start, double stop, char* unit)
{
	double elapsed = stop - start;
	printf("Tempo Gasto: %.3f %s\n", elapsed, unit);
}

int main(int argc, char **argv)
{
	int size, i;
	nodePtr* POIs;
	double start, stop;
	
	scanf("%d", &size);
	
	POIs = (nodePtr*) malloc (size*sizeof(nodePtr));

	aux = (nodePtr*) malloc(size * sizeof(nodePtr));
	
	for (i=0 ; i<size ; i++)
	{	
		POIs[i]= (nodePtr) malloc (sizeof(node));
		aux[i]=(nodePtr) malloc (sizeof(node));
		scanf("%d", &POIs[i]->lat.d);
		scanf("%d", &POIs[i]->lat.m);
		scanf("%d", &POIs[i]->lat.s);
		scanf("%d", &POIs[i]->lon.d);
		scanf("%d", &POIs[i]->lon.m);
		scanf("%d", &POIs[i]->lon.s);
		POIs[i]->la = toDouble(POIs[i]->lat);
		POIs[i]->lo = toDouble(POIs[i]->lon);
		POIs[i]->ind = i;
		scanf("%[^\n]",POIs[i]->text);
	}
	
	start = getCurrentTimeNano();
 	mergesort(POIs, size);
	stop = getCurrentTimeNano();
 	
 	/*
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
	*/
	for (i=0 ; i<size ; i++)
		/*print(POIs[i]), */free(POIs[i]);

	free(POIs);
	
	printTimeElapsed(start, stop, "Nanosegundos");
	
	return 0;
}
