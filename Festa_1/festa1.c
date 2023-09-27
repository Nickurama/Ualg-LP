//podem adicionar outros includes, caso necessitem
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "lista.h"
#include "festa1.h"

//comece por identificar o ficheiro com o seu numero e nome de aluno
//substitua nestas constantes o seu numero de aluno, e o seu primeiro e ultimo nome
const int NUMERO_ALUNO = 49858;
const char NOME_ALUNO[] = "Diogo Fonseca";


// Auxiliar Functions

char **my_tokenizer(const char *s, const char *delim, int *out_token_count)
{
    int s_len = strlen(s);
    int token_length;
    char **tokens = malloc(100 * sizeof(char *));
    int str_ar_len = 0;

    while ((token_length = strcspn(s, delim)) <= s_len)
    {
        if ((str_ar_len % 100) == 0)
            tokens = realloc(tokens, (((str_ar_len / 100) + 1) * 100) * sizeof(char *));
        char *token = malloc((token_length + 1) * sizeof(char));
        memcpy(token, s, token_length * sizeof(char));
        token[token_length] = '\0';

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

/***************************        Problema A - 5 pontos       ****************************************/
Time time(int timezone, int horas, int minutos)
{
    Time t;
    t.timezone = timezone;
    t.horas = horas;
    t.minutos = minutos;
    return t;
}

Time time_read(char *s)
{
    int token_count = 0;
    char **tokens = my_tokenizer(s, ",", &token_count);
    if (token_count < 3)
        assert(0);
    int hour = atoi(tokens[0]);
    int minute = atoi(tokens[1]);
    int timezone = atoi(tokens[2]);
    free_tokens(tokens, token_count);
    return time(timezone, hour, minute);
}

void print_two_digits(int a)
{
    if (a < 10 && a > -10)
        printf("0%d", a);
    else
        printf("%d", a);
}

void time_println(Time t)
{
    print_two_digits(t.horas);
    printf(":");
    print_two_digits(t.minutos);
    printf(" UTC");
    if (t.timezone < 0)
        printf("-");
    else
        printf("+");
    print_two_digits(abs(t.timezone));
    printf("\n");
}

/***************************        Problema B - 5 pontos       ****************************************/
int *array_ptr_to_last_divider(int a[], int n, int *x)
{
    int *pointer = NULL;
    for (int i = 0; i < n; i++)
    {
        if (a[i] % *x == 0)
            pointer = &a[i];
    }
    return pointer;
}

/***************************        Problema C - 5 pontos       ****************************************/
int* array_junta(int a[], int n, int b[], int m)
{
    int *c = malloc((n + m) * sizeof(int));
    for (int i = 0; i < n; i++)
        c[i] = a[i];
    for (int i = 0; i < m; i++)
        c[i + n] = b[i];
    return c;
}

/***************************        Problema D - 5 pontos       ****************************************/
Box box(const char *v)
{
    Box b = {v};
    return b;
}

Teste *teste(int id, char *name, char* type, const char* toBox)
{
    Teste *t = malloc(sizeof(Teste));
    t->id = id;
    t->name = strdup(name);
    strcpy(t->type, type);
    t->box = box(toBox);
    return t;
}

void teste_free(Teste *t)
{
    free(t->name);
    free(t);
}

/***************************        Problema E - 5 pontos       ****************************************/
void filter_string_characters(const char *s, char *s_out, CharPredicate p)
{
    int s_out_len = 0;
    for (int i = 0; i < strlen(s); i++)
        if (p(s[i]))
            s_out[s_out_len++] = s[i];
    s_out[s_out_len] = '\0';
}

int isVowel(char c)
{
    int result = 0;
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
        c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
        result = 1;
    return result;
}

void apenas_vogais(const char *s, char *s_out)
{
    filter_string_characters(s, s_out, isVowel);
}


/***************************        Problema F - 5 pontos       ****************************************/
Aluno *aluno(int numero, char *nome, char *turno)
{
    Aluno *a = calloc(1,sizeof(Aluno));
    a->numero = numero;
    a->nome = strdup(nome);
    a->turno = strdup(turno);
    a->estado_avaliacao = Reprovado;

    return a;
}

int remove_sem_frequencia(Aluno *alunos_in[], int n, Aluno *alunos_out[])
{
    int out_count = 0;
    for (int i = 0; i < n; i++)
    {
        if (alunos_in[i]->estado_avaliacao != Sem_Frequencia)
            alunos_out[out_count++] = alunos_in[i];
    }
    return out_count;
}

int aluno_cmp(const Aluno **a0, const Aluno **a1)
{
    int result = strcmp((*a0)->turno, (*a1)->turno);
    if (result == 0)
        result = (*a0)->numero - (*a1)->numero;
    return result;
}

typedef int (*Comparer)(const void *, const void *);

void ordena_turno_numero(Aluno *alunos[], int n)
{
    qsort(alunos, n, sizeof(Aluno *), (Comparer)aluno_cmp);
}

int remove_e_ordena(Aluno *alunos_in[], int n, Aluno *alunos_out[])
{
    int out_size = remove_sem_frequencia(alunos_in, n, alunos_out);
    ordena_turno_numero(alunos_out, out_size);
    return out_size;
}


/***************************        Problema G - 5 pontos       ****************************************/
Lista *array_to_lista(double a[], int n)
{
    Lista *l = lista();
    for (int i = 0; i < n; i++)
        l = lista_insere_fim(l, a[i]);
    return l;
}

/***************************        Problema H - 5 pontos       ****************************************/
int strings_iguais_recursivo(char *s1, char *s2)
{
    if (s1[0] == 0 || s2[0] == 0) //test for end of string
        return (s1[0] == 0 && s2[0] == 0); //test if same size
    
    return (s1[0] == s2[0]) && strings_iguais_recursivo(s1 + 1, s2 + 1);
}

/***************************        Problema I - 10 pontos       ****************************************/
void reverse_str_arr(char **strs, int n)
{
    //buffer string (reversed)
    char **str_arr_reversed = malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++)
        str_arr_reversed[i] = strdup(strs[n-1-i]);
    
    //reverse string
    for (int i = 0; i < n; i++)
    {
        free(strs[i]);
        strs[i] = strdup(str_arr_reversed[i]);
    }

    //memory management
    for (int i = 0; i < n; i++)
        free(str_arr_reversed[i]);
    free(str_arr_reversed);
}

void reverse_file(const char *input_filename, const char *output_filename)
{
    //read lines
    FILE *f_in = fopen(input_filename, "r");

    char **lines = malloc(100 * sizeof(char *));
    char line_buffer[1024];
    int lines_read = 0;
    while (fscanf(f_in, "%[^\n]%*c", line_buffer) != EOF)
    {
        if ((lines_read % 100) == 0)
            lines = realloc(lines, (((lines_read / 100) + 1) * 100) * sizeof(char *));
        
        lines[lines_read++] = strdup(line_buffer);
    }

    fclose(f_in);

    //write to file
    FILE *f_out = fopen(output_filename, "w");

    reverse_str_arr(lines, lines_read);

    if(lines_read > 0)
        fprintf(f_out, "%s", lines[0]);
    for (int i = 1; i < lines_read; i++) //i = 1
    {
        fprintf(f_out, "\n%s", lines[i]);
    }

    fflush(f_out);
    fclose(f_out);

    //memory management
    for (int i = 0; i < lines_read; i++)
        free(lines[i]);
    free(lines);
}


/***************************        Main - para testes locais      ****************************************/
#ifndef MOOSHAK_MAIN
//podem ter aqui uma função de main se o desejarem para fazerem testes locais no vosso computador
//tudo o que estiver aqui definido não será compilado quando submetido ao Mooshak
int main(void)
{

}
#endif