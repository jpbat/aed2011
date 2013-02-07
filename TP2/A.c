/*Joao Paulo Batista Ferreira*/
/*2009113274*/

#include <stdio.h>
#include <stdlib.h>

int* calculaTroco(int valor, int *valores, int tamanho)
{
	int i, *troco, end=0;

    troco = (int*) calloc (tamanho, sizeof(int));

	for (i=0 ; i<tamanho && end!=1 ; i++)
	{
	    while (1)
        {
            if (valor < valores[i])
                break;

            valor -= valores[i];
            troco[i]++;
        }
        if (valor <= 0)
            end=1;
    }

    if (valor>0)
        troco[tamanho-1]++;

	return troco;
}

void mostraTroco(int* valores, int* troco, int tamanho, int exacto)
{
    int i, soma=0;
    for (i=0 ; i<tamanho ; i++)
    {
        printf("%d %d\n", troco[i], valores[i]);
        soma+=troco[i];
    }

    printf("%d\n", soma);

    if (exacto == 1)
        printf("TROCO EXATO\n");
    else
        printf("SEM TROCO EXATO\n");
}

int main(void)
{
	int i=0, *valores, *troco, valor, aux, exacto=0, j;

	scanf("%d", &valor);

    valores = (int*) malloc (0*sizeof(int));

    while( (scanf("%d", &aux)) != EOF )
    {
        valores = realloc(valores, (i+1)*sizeof(int));
        valores[i] = aux;
        i++;
    }

    troco = calculaTroco(valor, valores, i);

    for(j=0 ; j<i ; j++)
        exacto += troco[j]*valores[j];

    if (exacto == valor)
        exacto = 1;
    else
        exacto = 0;

    mostraTroco(valores, troco, i, exacto);
    printf("\n");

    return 0;
}
