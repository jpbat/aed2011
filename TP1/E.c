#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int found=0, i, j, tamanho, valor=1, *array, soma=1;

    while (valor!= 0 && tamanho!=0)
    {
        scanf("%d", &tamanho);
        scanf("%d", &valor);

        if (valor == 0 && tamanho == 0)
            break;

        array = (int*) malloc (tamanho*sizeof(int));

        for (i=0 ; i<tamanho ; i++)
            scanf("%d", &array[i]);

        found = 0;
        soma = 0;
        j=0;
        for(i=0; (soma != valor) && (i<tamanho) && (found == 0) ; i++)
        {
            for (; (soma<valor) && (j<tamanho) ; j++)
            {
                soma = soma + array[j];
                if (soma == valor)
                {
                    printf("SUBSEQUENCIA NA POSICAO %d\n", i+1);
                    found = 1;
                    break;
                }
            }
            soma = soma - array[i];
        }
        if (soma == valor)
        {
            printf("SUBSEQUENCIA NA POSICAO %d\n", i+1);
        }
        else
        {
            printf("SUBSEQUENCIA NAO ENCONTRADA\n");
        }
        found=0;
    }
    return 0;
}
