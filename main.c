#include <stdio.h>
#include <stdlib.h>
#include <math.h>


float funcao_x(float x)
{
    return ((pow(x, 3)) - (pow(x, 2)) - 1);
}

int inversao_f_x(float x, float xn[], float acrescimo, FILE* arquivo)
{
    float menor, f_menor, maior, f_maior;

    if(funcao_x(x) >= 0.0)
    {
        return 0;
    }

    printf("\nx, f(x)\n");
    fprintf(arquivo, "\nx,f(x)\n");
    maior = 0.0;
    menor = x;
    f_menor = funcao_x(menor);

    printf("%f, %f\n", menor, f_menor);
    fprintf(arquivo, "%f,%f\n", menor, f_menor);

    do
    {
        menor = x;
        f_menor = funcao_x(menor);
        x = x + acrescimo;
        maior = x;
        f_maior = funcao_x(maior);
        printf("%f, %f\n", maior, f_maior);
        fprintf(arquivo, "%f,%f\n", maior, f_maior);
    } while ((f_menor < 0.0) && (f_maior < 0.0));
    xn[0] = menor;
    xn[1] = maior;
        
}

float dicotomia(float xa, float xb, float precisao, FILE* arquivo)
{
    float xc, xc_ant, f_xc, f_xa, f_xb;
    int iteracoes = 0;

    xc_ant = xb;
    xc = xa;

    printf("\ni, xa, xb, xc, f(xa), f(xb), f(xc), f_xa * f_xc < 0.0, f_xb * f_xc < 0.0, |xc - xc_ant|, precisao\n");
    fprintf(arquivo, "\ni,xa,xb,xc,f(xa),f(xb),f(xc),f_xa * f_xc < 0.0,f_xb * f_xc < 0.0,|xc - xc_ant|,precisao\n");

    while(fabs(xc - xc_ant) > precisao)
    {
        iteracoes ++;
        xc_ant = xc;
        xc = (xa + xb)/2.0;

        f_xa = funcao_x(xa);
        f_xb = funcao_x(xb);
        f_xc = funcao_x(xc);

        printf("%d, %f, %f, %f, %f, %f, %f, %d, %d, %f, %f\n", iteracoes, xa, xb, xc, f_xa, f_xb, f_xc, (f_xa * f_xc < 0), (f_xb * f_xc < 0), xc - xc_ant, precisao);
        fprintf(arquivo, "%d,%f,%f,%f,%f,%f,%f,%d,%d,%f,%f\n", iteracoes, xa, xb, xc, f_xa, f_xb, f_xc, (f_xa * f_xc < 0), (f_xb * f_xc < 0), xc - xc_ant, precisao);

        if(f_xa * f_xc < 0.0)
        {
            xb = xc;
        }
        else if(f_xb * f_xc < 0.0)
        {
            xa = xc;
        }
    }
    return xc;
}

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