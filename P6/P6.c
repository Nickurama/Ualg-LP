#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "lista.h"
const char *author = "Diogo Fonseca";

// Problem A

Lista *lista_get_doubles()
{
    Lista *list = lista();
    double d;
    while (scanf("%lf", &d) != EOF)
        list = lista_insere(list, d);
    return list;
}

Lista *lista_get_line(char *line, const char *delimiters)
{
    Lista *l = lista();
    char *token = strtok(line, delimiters);

    while (token != NULL)
    {
        l = lista_insere(l, atof(token));
        token = strtok(NULL, delimiters);
    }

    return l;
}

void lista_writeln_file(FILE *f, Lista *l, const char *delimiter)
{
    if (!lista_vazia(l))
    {
        fprintf(f, "%.2lf", l->value);
        l = l->next;
    }
    while (!lista_vazia(l))
    {
        fprintf(f, "%s%.2lf", delimiter, l->value);
        l = l->next;
    }
    fprintf(f, "\n");
}

// Problem B

double lista_max(Lista *l)
{
    assert(!lista_vazia(l));

    double max_value = l->value;
    while (!lista_vazia(l))
    {
        if (l->value > max_value)
            max_value = l->value;
        l = l->next;
    }
    return max_value;
}

double lista_sum(Lista *l)
{
    double sum = 0;
    while (!lista_vazia(l))
    {
        sum += l->value;
        l = l->next;
    }
    return sum;
}

Lista *lista_filtra_positivos(Lista *l)
{
    Lista *positive = lista();
    while (!lista_vazia(l))
    {
        if (l->value > 0)
            positive = lista_insere_fim(positive, l->value);
        l = l->next;
    }

    return positive;
}

Lista *lista_inverte(Lista *l)
{
    Lista *inverted = lista();
    Lista *l_start = l;

    while (!lista_vazia(l))
    {
        inverted = lista_insere(inverted, l->value);
        l = l->next;
    }

    l = l_start;
    while (!lista_vazia(l))
    {
        l->value = inverted->value;
        l = l->next;
        inverted = inverted->next;
    }

    lista_free(inverted);
    return l_start;
}

// Problem C

typedef double (*DoubleOperator)(double);
typedef double (*DoubleBinaryOperator)(double, double);
typedef int (*DoublePredicate)(double);

Lista *map(Lista *l, DoubleOperator op)
{
    Lista *start = l;
    while (!lista_vazia(l))
    {
        l->value = op(l->value);
        l = l->next;
    }
    return start;
}

int all(Lista *l, DoublePredicate p)
{
    while (!lista_vazia(l))
    {
        if (p(l->value) == 0)
            return 0;
        l = l->next;
    }
    return 1;
}

int any(Lista *l, DoublePredicate p)
{
    while (!lista_vazia(l))
    {
        if (p(l->value) == 1)
            return 1;
        l = l->next;
    }
    return 0;
}

int count_if(Lista *l, DoublePredicate p)
{
    int count = 0;
    while (!lista_vazia(l))
    {
        if (p(l->value) == 1)
            count++;
        l = l->next;
    }
    return count;
}

Lista *filter(Lista *l, DoublePredicate p)
{
    Lista *new_l = lista();
    while (!lista_vazia(l))
    {
        if (p(l->value) == 1)
            new_l = lista_insere_fim(new_l, l->value);
        l = l->next;
    }
    return new_l;
}

double find_first(Lista *l, DoublePredicate p)
{
    while (!lista_vazia(l))
    {
        if (p(l->value) == 1)
            return l->value;
        l = l->next;
    }
    return -1;
}

// Test Functions

void testA()
{
    char s[1000];
    scanf("%[^\n]%*c", s);
    Lista *l = lista_get_line(s, " ");
    lista_println(l);

    FILE *f = fopen("test.csv", "w");
    lista_writeln_file(f, l, ",");
    fclose(f);
    lista_free(l);
}
void testB()
{
    Lista *l = lista_get_doubles();
    printf("max value: %.2lf\n", lista_max(l));
    printf("sum of elements: %.2lf\n", lista_sum(l));
    printf("positive values: ");
    Lista *positives = lista_filtra_positivos(l);
    lista_println(positives);
    printf("inverted list: ");
    l = lista_inverte(l);
    lista_println(l);
}
void testC()
{
}

// Main

typedef void (*TestFunction)(void);
int main(const int argc, const char *argv[])
{
    TestFunction functions[] = {testA, testB, testC};

    int x = 'A';
    if (argc > 1)
        x = *argv[1];

    // vou buscar a funcao correta ao array a partir da letra (letra A = posicao 0, letra B = posicao 1, etc)
    TestFunction f = functions[x - 'A'];
    // mando executar f
    (*f)();

    return 0;
}