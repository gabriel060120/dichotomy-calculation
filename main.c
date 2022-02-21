#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dichotomy.h"


int main()
{
    float x;
    float xn[2];
    float precisao = 0.0001;
    float acrescimo = 0.1;
    float raiz;
    FILE *arquivo = NULL;
    
    arquivo = fopen("Tabela_Dicotomia.csv", "wt");
    if(arquivo == NULL)
    {
        exit(0);
    }

    printf("Digite o valor inicial:");
    scanf("%f", &x);

    while(!(inversao_f_x(x, xn, acrescimo, arquivo)))
    {
        printf("\nEntre com um valor negativo:");
        scanf("%f", &x);
    }
    
    raiz = dicotomia(xn[0], xn[1], precisao, arquivo);

    printf("\nraiz, %f\n", raiz);
    fprintf(arquivo, "\nraiz,%f\n", raiz);

    fclose(arquivo);

    return 0;
}