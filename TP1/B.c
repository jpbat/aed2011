#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int found=0, i, j, z, tamanho, valor=1, *array, soma;

    while (valor!= 0 && tamanho!=0) {
        scanf("%d", &tamanho);
        scanf("%d", &valor);

        if (valor == 0 && tamanho == 0)
            break;

        array = (int*) malloc (tamanho*sizeof(int));

        for (i=0 ; i<tamanho ; i++)
            scanf("%d", &array[i]);

        found = 0;

        for (i=0 ; i<tamanho && found==0 ; i++) {
            for (j=i ; j<tamanho ; j++) {
                soma = 0;
                for (z=i ; z<=j ; z++) {
                    soma = soma + array[z];
                }

                if (soma == valor) {
                    printf("SUBSEQUENCIA NA POSICAO %d\n", i+1);
                    found = 1;
                    break;
                }
            }
        }
        if(found==0) {
            printf("SUBSEQUENCIA NAO ENCONTRADA\n");
        }
        found=0;
    }
    return 0;
}
