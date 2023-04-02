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