#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int utn_getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
    int bufferInt;
    if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0)
    {
        do
        {
            printf("\n%s",mensaje);
            fflush(stdin);
            scanf("%d",&bufferInt);
            if(bufferInt >= minimo && bufferInt <= maximo)
            {
                *pResultado = bufferInt;
                return 0;
            }
            else
            {
                printf("\n%s",mensajeError);
                reintentos--;
//                system("pause>nul");
            }
        }
        while(reintentos >= 0);
    }
    return -1;
}

