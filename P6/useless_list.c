#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <math.h>

typedef struct s_node
{
    double value;
    struct s_node *next;
} Lista;

Lista *lista()
{
    return NULL;
}

int lista_vazia(Lista *l)
{
    return l == NULL;
}

int lista_tamanho(Lista *l)
{
    int n = 0;
    while (l != NULL)
    {
        l = l->next;
        n++;
    }
    return n;
}

void lista_println(Lista *l)
{
    printf("{");
    if (!lista_vazia(l))
    {
        printf("%.2lf", l->value);
        l = l->next;
    }
    while (!lista_vazia(l))
    {
        printf(",%.2lf", l->value);
        l = l->next;
    }
    printf("}\n");
}

double lista_primeiro(Lista *l)
{
    assert(!lista_vazia(l));
    return l->value;
}

Lista *lista_resto(Lista *l)
{
    assert(!lista_vazia(l));
    return l->next;
}

double lista_obtem(Lista *l, int i)
{
    while (i != 0)
    {
        assert(!lista_vazia(l));
        l = l->next;
        i--;
    }
    assert(!lista_vazia(l));
    return l->value;
}

Lista *lista_insere(Lista *l, double valor)
{
    Lista *new_l = malloc(sizeof(Lista));

    new_l->value = valor;
    new_l->next = l;

    return new_l;
}

Lista *lista_insere_fim(Lista *l, double valor)
{
    Lista *start = l;
    Lista *new_l = malloc(sizeof(Lista));
    new_l->value = valor;
    new_l->next = NULL;

    if (lista_vazia(l))
        start = new_l;
    else
    {
        while (l->next != NULL)
            l = l->next;
        l->next = new_l;
    }

    return start;
}

Lista *lista_insere_posicao(Lista *l, int i, double valor)
{
    Lista *start = l;

    while (i > 1)
    {
        assert(!lista_vazia(l));
        l = l->next;
        i--;
    }
    assert(!lista_vazia(l));

    Lista *new_l = malloc(sizeof(Lista));
    new_l->value = valor;
    new_l->next = l->next;
    l->next = new_l;

    return start;
}

Lista *lista_altera_posicao(Lista *l, int i, double valor)
{
    Lista *start = l;

    while (i != 0)
    {
        assert(!lista_vazia(l));
        l = l->next;
    }
    assert(!lista_vazia(l));

    l->value = valor;

    return start;
}

Lista *lista_remove_primeiro(Lista *l)
{
    Lista *start = l;
    l = l->next;
    free(start);
    return l;
}

Lista *lista_remove_ultimo(Lista *l)
{
    Lista *start = l;

    while (!lista_vazia(l->next->next))
        l = l->next;
    free(l->next);
    l->next = NULL;

    return start;
}

Lista *lista_remove_posicao(Lista *l, int i)
{
    Lista *start = l;
    while (i > 1)
    {
        assert(!lista_vazia(l));
        l = l->next;
        i--;
    }

    Lista *buffer_next = l->next->next;
    free(l->next);
    l->next = buffer_next;

    return start;
}

void lista_free(Lista *l)
{
    Lista *buffer = l;
    while (!lista_vazia(l))
    {
        l = l->next;
        free(buffer);
        buffer = l;
    }
}

Lista *lista_copia(Lista *l)
{
    Lista *copy = malloc(sizeof(Lista));
    Lista *copy_start = copy;
    copy->value = l->value;

    l = l->next;
    while (!lista_vazia(l))
    {
        Lista *next = malloc(sizeof(Lista));
        next->value = l->value;
        copy->next = next;

        l = l->next;
        copy = copy->next;
    }

    return copy_start;
}