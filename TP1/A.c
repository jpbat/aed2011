#include <stdio.h>
#include <string.h>

int main(void)
{
    char texto[256];
    int i;
    while(fgets(texto, 256, stdin))
    {
        for (i=0 ; i<strlen(texto) ; i++)
            texto[i] = toupper(texto[i]);
        printf("%s", texto);
    }
    return 0;
}
