#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "lista.h"
const char *author = "Diogo Fonseca";

// Problem A

int potencia(int x, int n)
{
    return n == 0 ? 1 : x * potencia(x, n - 1);
}

int ocorre(int d, int n)
{
    return n < 10 ? (d == n) : (d == (n % 10)) + ocorre(d, n / 10);
}

int mdc(int x, int y)
{
    if (x == y)
        return x;
    else if (x > y)
        return mdc(x - y, y);
    else
        return mdc(y, x);
}

int divisao_inteira(int x, int y)
{
    return x < y ? 0 : 1 + divisao_inteira(x - y, y);
}

// Problem B

double array_max(double a[], int n)
{
    if (n == 1)
        return a[0];

    double max = array_max(a + 1, n - 1);
    return a[0] > max ? a[0] : max;
}

double soma_array(double a[], int n)
{
    return n == 1 ? a[0] : a[0] + soma_array(a + 1, n - 1);
}

double produto_array(double a[], int n)
{
    return n == 1 ? a[0] : a[0] * produto_array(a + 1, n - 1);
}

int array_contem(double a[], int n, double el)
{
    return n == 1 ? (a[0] == el) : (a[0] == el) || array_contem(a + 1, n - 1, el);
}

int todos_pares(int a[], int n)
{
    return n == 1 ? (a[0] % 2 == 0) : (a[0] % 2 == 0) && todos_pares(a + 1, n - 1);
}

int tudo_minusculas(char *s)
{
    return (s[0] == '\0') ? 1 : ((s[0] >= 'a') && tudo_minusculas(s + 1));
}

// Problem C

double lista_min(Lista *l)
{
    if (lista_vazia(l->next))
        return l->value;

    double min = lista_min(l->next);
    return l->value < min ? l->value : min;
}

double lista_produto(Lista *l)
{
    return (lista_vazia(l->next)) ? l->value : l->value * lista_produto(l->next);
}

Lista *lista_pares(Lista *l)
{
    if (lista_vazia(l))
        return lista();

    return (int)l->value % 2 == 0 ? lista_insere(lista_pares(l->next), l->value) : lista_pares(l->next);
}

Lista *lista_junta(Lista *l1, Lista *l2)
{
    if (lista_vazia(l2))
        return l1;

    return lista_junta(lista_insere_fim(l1, l2->value), l2->next);
}

int lista_iguais(Lista *l1, Lista *l2)
{
    if (lista_vazia(l1) && lista_vazia(l2))
        return 1;
    else if (lista_vazia(l1) || lista_vazia(l2))
        return 0;

    return (l1->value == l2->value) && lista_iguais(l1->next, l2->next);
}

// Test Functions

void testA()
{
    int x, y;
    scanf("%d %d", &x, &y);
    printf("%d raised to %d is %d!\n", x, y, potencia(x, y));
    printf("%d occurs %d times in %d!\n", x, ocorre(x, y), y);
    printf("the mdc between %d and %d is %d!\n", x, y, mdc(x, y));
    printf("%d divided by %d is %d", x, y, divisao_inteira(x, y));
}
void testB()
{
    // double in;
    // double a[100];
    // int n = 0;
    // while (scanf("%lf", &in) != EOF)
    //     a[n++] = in;
    // double el;
    // scanf("%lf", &el);
    // printf("the max value in the array is: %.2lf!\n", array_max(a, n));
    // printf("the sum of the array is: %.2lf!\n", soma_array(a, n));
    // printf("the mul of the array is: %.2lf!\n", produto_array(a, n));
    // if (array_contem(a, n, el))
    //     printf("the array contains %.2lf!\n", el);
    // else
    //     printf("the array doesn't contain %.2lf!\n", el);

    // int a[100];
    // while (scanf("%lf", &in) != EOF)
    //     a[n++] = in;

    // if (todos_pares(a, n))
    //     printf("all the elements in the array are even!");
    // else
    //     printf("not all elements of the array are even!");

    char a[100];
    scanf("%s%*c", a);
    if (tudo_minusculas(a))
        printf("everything is in lowercase!");
    else
        printf("not everything is in lowercase");
}
void testC()
{
    Lista *l = lista();
    l = lista_insere(l, 1);
    l = lista_insere(l, 2);
    l = lista_insere(l, 3);
    l = lista_insere(l, 4);
    l = lista_insere(l, 5);
    l = lista_insere(l, 6);

    Lista *l2 = lista();
    l2 = lista_insere(l2, 1);
    l2 = lista_insere(l2, 2);
    l2 = lista_insere(l2, 3);
    l2 = lista_insere(l2, 4);
    l2 = lista_insere(l2, 5);
    l2 = lista_insere(l2, 6);
    // l2 = lista_insere(l2, 7);

    // Lista *l2 = lista();
    // l2 = lista_insere(l2, 11);
    // l2 = lista_insere(l2, 12);
    // l2 = lista_insere(l2, 13);
    // l2 = lista_insere(l2, 14);
    // l2 = lista_insere(l2, 15);
    // l2 = lista_insere(l2, 16);

    printf("min value: %.2lf\n", lista_min(l));
    printf("multiplication: %.2lf\n", lista_produto(l));

    printf("list of even numbers: ");
    Lista *pares = lista_pares(l);
    lista_println(pares);

    printf("list 1: ");
    lista_println(l);
    printf("list 2: ");
    lista_println(l2);
    if (lista_iguais(l, l2))
        printf("lists are equal!\n");
    else
        printf("lists are different\n");
    printf("jointed version of both lists: ");
    Lista *jointed = lista_junta(l, l2);
    lista_println(jointed);

    lista_free(l);
    lista_free(pares);
    lista_free(jointed);
}

// Main

typedef void (*TestFunction)(void);
int main(const int argc, const char *argv[])
{
    TestFunction functions[] = {testA, testB, testC};

    int x = 'C';
    if (argc > 1)
        x = *argv[1];

    // vou buscar a funcao correta ao array a partir da letra (letra A = posicao 0, letra B = posicao 1, etc)
    TestFunction f = functions[x - 'A'];
    // mando executar f
    (*f)();

    return 0;
}