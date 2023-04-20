#ifndef FESTA_1_A
#define FESTA_1_A

#include "lista.h"

/***************************        Problema A - 5 pontos       ****************************************/
typedef struct s_time {
    int timezone;
    int horas;
    int minutos;
} Time;

Time time(int timezone, int horas, int minutos);
Time time_read(char *s);
void time_println(Time t);

/***************************        Problema B - 5 pontos       ****************************************/
int *array_ptr_to_last_divider(int a[], int n, int *x);

/***************************        Problema C - 5 pontos       ****************************************/
int* array_junta(int a[], int n, int b[], int m);

/***************************        Problema D - 5 pontos       ****************************************/
typedef struct s_box {
    const char* value;  
} Box;

Box box(const char *v);

typedef struct s_teste {
    int id;
    char *name;
    char type[5];
    Box box;
} Teste;

Teste *teste(int id, char *name, char* type, const char* toBox);
void teste_free(Teste *t);

/***************************        Problema E - 5 pontos       ****************************************/
typedef int (*CharPredicate) (char);
void filter_string_characters(const char *s, char *s_out, CharPredicate p);
void apenas_vogais(const char *s, char *s_out);


/***************************        Problema F - 5 pontos       ****************************************/
typedef enum e_EstadoAvaliacao {Aprovado, Reprovado, Faltou, Nao_Admitido, Sem_Frequencia} EstadoAvaliacao;

typedef struct S_Aluno
{
        int numero;
        char *nome;
        char *turno;
        EstadoAvaliacao estado_avaliacao;
} Aluno;

Aluno *aluno(int numero, char *nome, char *turno);
int remove_sem_frequencia(Aluno *alunos_in[], int n, Aluno *alunos_out[]);
void ordena_turno_numero(Aluno *alunos[], int n);
int remove_e_ordena(Aluno *alunos_in[], int n, Aluno *alunos_out[]);


/***************************        Problema G - 5 pontos       ****************************************/
Lista *array_to_lista(double a[], int n);

/***************************        Problema H - 5 pontos       ****************************************/
int strings_iguais_recursivo(char *s1, char *s2);

/***************************        Problema I - 10 pontos       ****************************************/
void reverse_file(const char *input_filename, const char *output_filename);

#endif