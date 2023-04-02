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

const char *STR_TAMANHOS[6] = {"Tiny", "Small", "Medium", "Large", "Huge", "Gargantuan"};
const char *DELIMITER = ",";

Tamanho string_to_tamanho(char *s)
{
    for (int i = Tiny; i <= Gargantuan; i++)
        if (strcmp(s, STR_TAMANHOS[i]) == 0)
            return i;
    assert(0);
}

const char *tamanho_to_string(Tamanho t)
{
    return STR_TAMANHOS[t];
}

Monstro *monstro(char *nome, char *tipo, Tamanho tam, int ac, int hp, double cr, char *trait)
{
    Monstro *m = malloc(sizeof(Monstro));
    m->nome = malloc(sizeof(char) * (strlen(nome) + 1));
    strcpy(m->nome, nome);
    m->tipo = malloc(sizeof(char) * (strlen(tipo) + 1));
    strcpy(m->tipo, tipo);
    m->tam = tam;
    m->ac = ac;
    m->hp = hp;
    m->cr = cr;
    // printf("here! %s\n");
    m->trait = malloc(sizeof(char) * (strlen(trait) + 1));
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

void free_monstros(Monstro **m, int n)
{
    for (int i = 0; i < n; i++)
        free_monstro(m[i]);
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

char **my_tokenizer(const char *s, const char *delim, int *out_token_count)
{
    int s_len = strlen(s);
    int token_length;
    char **tokens = malloc(sizeof(char *));
    int str_ar_len = 0;

    while ((token_length = strcspn(s, delim)) <= s_len)
    {
        char *token = malloc((token_length + 1) * sizeof(char));
        memcpy(token, s, token_length * sizeof(char));
        token[token_length] = '\0';
        tokens = realloc(tokens, (str_ar_len + 1) * sizeof(char *));
        tokens[str_ar_len++] = token;
        s += token_length + 1;
        s_len -= token_length + 1;
    }

    *out_token_count = str_ar_len;
    return tokens;
}

void free_tokens(char **tokens, int n)
{
    for (int i = 0; i < n; i++)
        free(tokens[i]);
    free(tokens);
}

int get_monstros_from_file(FILE *f, Monstro *monstros[], int n)
{
    char line[347]; // 10 + 10 + 10 + 16 + 100 + 100 + 100 + 1  (100 for each string) (10 for each int) (15+1(dot) for each double) (1 for \n)
    for (int i = 0; i < n; i++)
    {
        fscanf(f, "%346[^\n]%*c", line);
        int token_count;
        char **tokens = my_tokenizer(line, DELIMITER, &token_count);
        monstros[i] = monstro(tokens[0], tokens[1], string_to_tamanho(tokens[2]), atoi(tokens[3]), atoi(tokens[4]), atof(tokens[5]), tokens[6]);
        free_tokens(tokens, token_count);
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

int pesquisa_monstros(Monstro *in[], Monstro *out[], int n, int (*p)(Monstro *))
{
    int size = 0;
    for (int i = 0; i < n; i++)
        if (p(in[i]))
            out[size++] = in[i];
    return size;
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
        int size_result = pesquisa_monstros_tipo(m, m_result, n, tipo);
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

    free_monstros(m, n);
}

void test_Monstro_File_Loading()
{
    char filename[100];
    scanf("%s", filename);
    FILE *f = fopen(filename, "r");

    int n;
    fscanf(f, "%d%*c", &n);

    Monstro *m[n];
    get_monstros_from_file(f, m, n);

    char tipo[100], cr_min_str[64];
    while (scanf("%s %s", tipo, cr_min_str) != EOF)
    {
        double cr_min, cr_max;
        Monstro *m_result[n];
        int size_result = pesquisa_monstros_tipo(m, m_result, n, tipo);
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

    free_monstros(m, n);
    fclose(f);
}

typedef int (*Comparer)(const void *, const void *);

int monster_cmp(const Monstro **a, const Monstro **b)
{
    int result;
    double result_double = (*a)->cr - (*b)->cr;
    if (result_double == 0)
        result = -strcmp((*a)->nome, (*b)->nome);
    else if (result_double > 0)
        result = 1;
    else if (result_double < 0)
        result = -1;
    return -result;
}

void test_Monstro_Sorting()
{
    char filename[100];
    scanf("%s", filename);
    FILE *f = fopen(filename, "r");

    int n;
    fscanf(f, "%d%*c", &n);

    Monstro *m[n];

    get_monstros_from_file(f, m, n);

    qsort(m, n, sizeof(Monstro *), (Comparer)monster_cmp);
    println_monstros(m, n);
}

int monstro_med_diff(Monstro *m)
{
    int result = 0;
    if (m->tam == Medium && m->hp > 10)
        result = 1;
    return result;
}

void test_Monstro_Pesquisa()
{
    char filename[100];
    scanf("%s", filename);
    FILE *f = fopen(filename, "r");

    int n;
    fscanf(f, "%d%*c", &n);

    Monstro *m[n];
    get_monstros_from_file(f, m, n);
    Monstro *out[n];
    int out_size = pesquisa_monstros(m, out, n, monstro_med_diff);
    println_monstros(out, out_size);
}