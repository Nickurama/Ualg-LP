#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#include "our_ints.h"
#include "our_doubles.h"
#include "monstro.h"

const char *author = "Diogo Fonseca";

Tamanho string_to_tamanho(char *s)
{
    Tamanho t;
    if (!strcmp(s, "Tiny"))
        t = Tiny;
    else if (!strcmp(s, "Small"))
        t = Small;
    else if (!strcmp(s, "Medium"))
        t = Medium;
    else if (!strcmp(s, "Large"))
        t = Large;
    else if (!strcmp(s, "Huge"))
        t = Huge;
    else if (!strcmp(s, "Gargantuan"))
        t = Gargantuan;
    return t;
}

const char *tamanho_to_string(Tamanho t)
{
    char *s;
    if (t == Tiny)
    {
        s = malloc(5 * sizeof(char));
        strcpy(s, "Tiny");
    }
    else if (t == Small)
    {
        s = malloc(6 * sizeof(char));
        strcpy(s, "Small");
    }
    else if (t == Medium)
    {
        s = malloc(7 * sizeof(char));
        strcpy(s, "Medium");
    }
    else if (t == Large)
    {
        s = malloc(6 * sizeof(char));
        strcpy(s, "Large");
    }
    else if (t == Huge)
    {
        s = malloc(5 * sizeof(char));
        strcpy(s, "Huge");
    }
    else if (t == Gargantuan)
    {
        s = malloc(11 * sizeof(char));
        strcpy(s, "Gargantuan");
    }
    return s;
}

Monstro *monstro(char *nome, char *tipo, Tamanho tam, int ac, int hp, double cr, char *trait)
{
    Monstro *m = malloc(sizeof(Monstro));
    m->nome = malloc(sizeof(char) * strlen(nome));
    strcpy(m->nome, nome);
    m->tipo = malloc(sizeof(char) * strlen(tipo));
    strcpy(m->tipo, tipo);
    m->tam = tam;
    m->ac = ac;
    m->hp = hp;
    m->cr = cr;
    m->trait = malloc(sizeof(char) * strlen(trait));
    strcpy(m->trait, trait);
    return m;
}

void free_monstro(Monstro *m)
{
    free(m->nome);
    free(m->tipo);
    free(m->trait);
    free(m);
}

Monstro *monstro_dup(Monstro *m)
{
    return monstro(m->nome, m->tipo, m->tam, m->ac, m->hp, m->cr, m->trait);
}

void atualiza_stats(Monstro *m, int ac, int hp, double cr)
{
    m->ac = ac;
    m->hp = hp;
    m->cr = cr;
}

void println_monstro(Monstro *m)
{
    printf("%s - %s %s, AC:%d, HP:%d, CR:%.2lf, Trait:%s\n", m->nome, tamanho_to_string(m->tam), m->tipo, m->ac, m->hp, m->cr, m->trait);
}

void println_monstros(Monstro *monstros[], int n)
{
    if (n == 0)
        printf("None\n");
    for (int i = 0; i < n; i++)
        println_monstro(monstros[i]);
}

int get_monstros(Monstro *monstros[], int n)
{
    for (int i = 0; i < n; i++)
    {
        char nome[100], tipo[100], tam_str[11], trait[100];
        int ac, hp;
        double cr;

        scanf("%s %s %s %d %d %lf %s", nome, tipo, tam_str, &ac, &hp, &cr, trait);

        Monstro *m = monstro(nome, tipo, string_to_tamanho(tam_str), ac, hp, cr, trait);
        monstros[i] = m;
    }
    return n;
}

Monstro *pesquisa_monstro(Monstro *monstros[], int n, char *nome)
{
    for (int i = 0; i < n; i++)
        if (!strcmp(monstros[i]->nome, nome))
            return monstros[i];
    return NULL;
}

Monstro *pesquisa_monstro_mais_duro(Monstro *monstros[], int n)
{
    Monstro *m;
    if (n > 0)
    {
        m = monstros[0];
        for (int i = 0; i < n; i++)
            if (monstros[i]->hp > m->hp)
                m = monstros[i];
    }
    else
        m = NULL;
    return m;
}

int pesquisa_monstros_tipo(Monstro *in[], Monstro *out[], int n, char *tipo)
{
    int size = 0;
    for (int i = 0; i < n; i++)
        if (!strcmp(in[i]->tipo, tipo))
            out[size++] = in[i];
    return size;
}

int pesquisa_monstros_cr(Monstro *in[], Monstro *out[], int n, double cr_min, double cr_max)
{
    int size = 0;
    for (int i = 0; i < n; i++)
        if (in[i]->cr <= cr_max && in[i]->cr >= cr_min)
            out[size++] = in[i];
    return size;
}

void monsters_to_monsters_ptr(Monstro *in, int n, Monstro **out)
{
    for (int i = 0; i < n; i++)
        out[i] = &in[i];
}

void test_F_S2()
{
    int n;
    scanf("%d", &n);
    Monstro *m[n];
    get_monstros(m, n);

    char tipo[100], cr_min_str[64];
    while (scanf("%s %s", tipo, cr_min_str) != EOF)
    {
        double cr_min, cr_max;
        Monstro *m_result[n];
        monsters_to_monsters_ptr(*m, n, m_result);
        int size_result = pesquisa_monstros_tipo(m_result, m_result, n, tipo);
        if (strcmp(cr_min_str, "*"))
        {
            cr_min = atof(cr_min_str);
            scanf("%lf", &cr_max);
            size_result = pesquisa_monstros_cr(m_result, m_result, size_result, cr_min, cr_max);
        }

        if (size_result == 0)
            printf("None\n");
        else
            println_monstros(m_result, size_result);
    }
}