#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/time.h>
#include <unistd.h>


/* Pedro Magalhães 2009117002 */

struct poi_fields {
	int gLat, mLat, sLat,
		gLon, mLon, sLon,
		order;

	double aux;

	char name[40];
} typedef sPois;

int compare(sPois *first, sPois *second)
{
	if (first->aux < second->aux)
		return -1;
	else if (first->aux > second->aux)
		return 1;

	return 0;
}

void printPois(sPois **pois, int totalInputs)
{
	int i;

	for (i = 0; i < totalInputs; i++)
		printf("%d %d %d %d %d %d %s\n", pois[i]->gLat, pois[i]->mLat, pois[i]->sLat,
										 pois[i]->gLon, pois[i]->mLon, pois[i]->sLon,
										 pois[i]->name);
}

void swap(sPois **a, sPois **b)
{
	sPois *aux = *a;

	*a = *b;

	*b = aux;
}

sPois **removeElement(sPois **pois, int removeIndex, int *totalPois)
{
	int i;

	sPois **newArray = (sPois**) malloc( (*totalPois-1) * sizeof(sPois*));

	for (i = 0; i < removeIndex; i++)
		newArray[i] = pois[i];

	for (i++; i < *totalPois; i++)
		newArray[i - 1] = pois[i];

	free(pois);

	(*totalPois)--;

	return newArray;
}

void sortPivot(sPois **pois, int lower, int pivot, int higher)
{
	if (compare(pois[lower],pois[pivot]) > 0)
		swap(&pois[lower], &pois[pivot]);

	if (compare(pois[pivot], pois[higher]) > 0)
		swap(&pois[pivot], &pois[higher]);

	if (compare(pois[lower], pois[pivot]) > 0)
		swap(&pois[lower], &pois[pivot]);
}

void quickSort(sPois **pois, int lower, int higher)
{
	int i = lower + 1,
		j = higher - 1,
		pivotIndex = (lower + higher) >> 1;
	
	double pivot;
	
	sortPivot(pois, lower, pivotIndex, higher);
	
	pivot = pois[pivotIndex]->aux;
	
	while (i <= j)
	{
		while (pois[i]->aux < pivot)
			i++;

		while (pois[j]->aux > pivot)
			j--;

		if (i <= j)
		{
			swap(&pois[i],&pois[j]);
			i++;
			j--;
		}
	}
	
	if (lower < j)
		quickSort(pois, lower, j);
		
	if (i < higher)
		quickSort(pois, i, higher);
}

sPois** readInput(int *totalPois)
{
	sPois **pois;

	int i;

	scanf("%d", totalPois);

	pois = (sPois**) malloc( *totalPois * sizeof(sPois*));

	for (i = 0; i < *totalPois; i++)
	{
		pois[i] = (sPois*) malloc(sizeof(sPois));

		scanf("%d %d %d %d %d %d %[^\n]", &pois[i]->gLat, &pois[i]->mLat, &pois[i]->sLat, &pois[i]->gLon, &pois[i]->mLon, &pois[i]->sLon, pois[i]->name);

		pois[i]->aux = (double)pois[i]->gLat * 1000000000;
		pois[i]->aux += (double)pois[i]->mLat * 10000000;
		pois[i]->aux += (double)pois[i]->sLat * 100000;
		pois[i]->aux += (double)pois[i]->gLon * 10000;
		pois[i]->aux += (double)pois[i]->mLon * 100;
		pois[i]->aux += (double)pois[i]->sLon;
		pois[i]->order = i;
	}

	return pois;
}

sPois **freePois(sPois **pois, int totalInputs)
{
	int i;

	for (i = 0; i < totalInputs; i++)
		free(pois[i]);

	free(pois);

	return NULL;
}

sPois **removeDuplicatedEntrys(sPois **pois, int *totalPois)
{
	int i;

	for (i = 0; i < (*totalPois) - 1; i++)
	{
		if ( compare(pois[i],pois[i+1]) == 0 )
		{
			if (pois[i]->order > pois[i+1]->order)
				pois = removeElement(pois, i, totalPois);
			else
				pois = removeElement(pois, i+1, totalPois);
			i--;
		}
	}

	return pois;
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
	int totalPois;
	double start, stop;
	
	sPois **pois;

	pois = readInput(&totalPois);

	start = getCurrentTimeNano();
	quickSort(pois, 0, totalPois-1);
	stop = getCurrentTimeNano();

/*
	pois = removeDuplicatedEntrys(pois, &totalPois);

	printPois(pois, totalPois);
*/

printTimeElapsed(start, stop, "Nanosegundos");
	
	pois = freePois(pois, totalPois);

	return 0;
}
