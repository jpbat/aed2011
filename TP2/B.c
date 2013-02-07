/*Joao Paulo Batista Ferreira*/
/*2009113274*/

#include <stdio.h>
#include <stdlib.h>

int calculaSoma(int *valores, int *quantidades, int tamanho)
{
	int i, soma=0;
	for (i=0 ; i<tamanho ; i++)
	{
		soma += valores[i]*quantidades[i];
	}
	return soma;
}

void mostraTroco(int* valores, int* troco, int tamanho, int valor)
{
    int i, soma=0, v=0;
    for (i=0 ; i<tamanho ; i++)
    {
        printf("%d %d\n", troco[i], valores[i]);
        soma+=troco[i];
        v+=valores[i]*troco[i]; 
    }

    printf("%d\n", soma);

    if (v != valor)
        printf("SEM ");
	
	printf("TROCO EXATO\n");
}

void calculaTroco(int valor, int *valores, int tamanho, int* troco, int posicao)
{	
	int i;
	
	for (i=posicao ; i<tamanho ; i++)
	{
		
	}
	
	calculaTroco(valor, valores, tamanho, troco, posicao);
}

int main(void)
{
	int i=0, *valores, *troco, valor, aux;
	
	scanf("%d", &valor);

    valores = (int*) malloc (0*sizeof(int));

    while( (scanf("%d", &aux)) != EOF )
    {
        valores = realloc(valores, (i+1)*sizeof(int));
        valores[i] = aux;
        i++;
    }
    
    troco = (int*) calloc (i, sizeof(int));

    calculaTroco(valor, valores, i, troco, 0, 1);

    return 0;
}
