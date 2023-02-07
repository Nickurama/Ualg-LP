#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "our_ints.h"
#include "our_doubles.h"
const char *author = "Diogo Fonseca";

// Programa A -----------------------------------------------------------------------------------
int covid(int *a, int n, int *b, const int x)
{
    for (int i = 0; i < n; i++)
    {
        if ((a[i] / 10000) == x)
        {
            b[0] = (a[i] % 10000) / 100;
            b[1] = a[i] % 100;
            a[i] = -1;
            return 2;
        }
    }
    return 0;
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
void blackfriday(const int *a, const int n)
{
    /*
    int buffer;
    int counter = 0;
    for (int i = 0; i < n; i++)
    {
        if (buffer == a[i])
            counter++;
        else
            buffer = a[i];
    }
    */
}

void testB()
{
    int n;
    int a[1000];
    n = ints_get(a);
    blackfriday(a, n);
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

// Programa G ----------------------------------------------------------------------
double gas_cost(double price, double discount, double max_discount, int liters)
{
    double cost = price * liters;
    if (liters > max_discount)
        cost -= max_discount * discount;
    else
        cost -= liters * discount;
    return cost;
}

int gas(const double *prices, const double *discounts, const double *max_discounts, int n, int liters)
{
    double final_price[1000];
    for (int i = 0; i < n; i++)
        final_price[i] = gas_cost(prices[i], discounts[i], max_discounts[i], liters);
    return doubles_argmin(final_price, n);
}

void test_fuel()
{
    int input;
    double prices[1000];
    double discounts[1000];
    double max_discounts[1000];
    int length;
    length = doubles_get_until(-1, prices);
    doubles_get_until(-1, discounts);
    doubles_get_until(-1, max_discounts);
    while (scanf("%d", &input) != EOF)
    {
        int index = gas(prices, discounts, max_discounts, length, input);
        double cost = gas_cost(prices[index], discounts[index], max_discounts[index], input);
        double cost_per_liter = cost / input;
        printf("%d %.2f %.3f\n", index, cost, cost_per_liter);
    }
}
//
// MAIN
// Este main esta preparado para receber um argumento quando o programa e executado.
// Esse argumento, que se espera que seja um caracter
// sera usado para determinar qual das funcoes de teste (ou problema) serao executados.
// Caso nao seja passado nenhum argumento, e invocado o teste do problema A por omissao

int main(const int argc, const char *argv[])
{
    int x = 'G';
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
    else if (x == 'G')
        test_fuel();
    else if (x == 'U')
        printf("All unit tests PASSED.\n");

    return 0;
}
