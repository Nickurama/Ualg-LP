#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "our_ints.h"
#include "our_doubles.h"

// Programa A -----------------------------------------------------------------------------------
int covid(int *a, int n, int *b, int x)
{
    for (int i = 0; i < n; i++)
    {
        if ((a[i] / 10000) == x)
        {
            // store values in b variable
        }
    }
}

void testA()
{
    int n, x, m;
    int a[1000];
    int b[1000];
    n = ints_get_until(-1, a);
    while (scanf("%d", &x) != EOF)
    {
        m = covid(a, n, b, x);
        ints_println_special(b, m);
    }
}

// Programa B ---------------------------------------------------------------------------------
void testB()
{
}

// Programa C ----------------------------------------------------------------------------------

void testC()
{
}

// Programa D --------------------------------------------------------------------------------------------------

void testD()
{
}

// Programa E ----------------------------------------------------------------------

void testE()
{
}

// MAIN
// Este main esta preparado para receber um argumento quando o programa e executado.
// Esse argumento, que se espera que seja um caracter
// sera usado para determinar qual das funcoes de teste (ou problema) serao executados.
// Caso nao seja passado nenhum argumento, e invocado o teste do problema A por omissao

int main(const int argc, const char *argv[])
{
    int x = 'A';
    if (argc > 1)
        x = *argv[1];

    if (x == 'A')
        testA();
    else if (x == 'B')
        testB();
    else if (x == 'C')
        testC();
    else if (x == 'D')
        testD();
    else if (x == 'E')
        testE();
    else if (x == 'U')
        printf("All unit tests PASSED.\n");

    return 0;
}
