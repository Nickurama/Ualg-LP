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

// PROBLEMA A ---------------------------------------------------------------------------------

enum grade_state
{
    Aprovado,
    Reprovado,
    Faltou,
    Nao_Admitido,
    Sem_Frequencia
};

typedef struct student
{
    int number;
    char name[1000];
    int grades[10];
    int total_points;
    enum grade_state gr_state;
} student;

student student_construct(int number, char *name)
{
    student stdnt;
    stdnt.gr_state = Reprovado;
    stdnt.number = number;
    strcpy(stdnt.name, name);
    for (int i = 0; i < 10; i++)
        stdnt.grades[i] = 0;
    stdnt.total_points = 0;
    return stdnt;
}

enum grade_state str_to_grade_state(char *s)
{
    enum grade_state gs;
    if (!strcmp(s, "Aprovado"))
        gs = Aprovado;
    else if (!strcmp(s, "Reprovado"))
        gs = Reprovado;
    else if (!strcmp(s, "Faltou"))
        gs = Faltou;
    else if (!strcmp(s, "Nao_Admitido"))
        gs = Nao_Admitido;
    else if (!strcmp(s, "Sem_Frequencia"))
        gs = Sem_Frequencia;
    return gs;
}

char *grade_state_to_str(enum grade_state gs)
{
    char *str = (char *)malloc(15 * sizeof(char));
    if (gs == Aprovado)
        strcpy(str, "Aprovado");
    else if (gs == Reprovado)
        strcpy(str, "Reprovado");
    else if (gs == Faltou)
        strcpy(str, "Faltou");
    else if (gs == Nao_Admitido)
        strcpy(str, "Nao_Admitido");
    else if (gs == Sem_Frequencia)
        strcpy(str, "Sem_Frequencia");
    return str;
}

void update_grade_state(student *stdnt)
{
    printf("total points: %d\n", stdnt->total_points);
    if (stdnt->total_points == 0)
        stdnt->gr_state = Sem_Frequencia;
    else if ((stdnt->grades[8] == 0) && (stdnt->grades[9] == 0))
        stdnt->gr_state = Faltou;
    else if ((stdnt->grades[8] < 15) && (stdnt->grades[9] < 15))
        stdnt->gr_state = Nao_Admitido;
    else if (stdnt->total_points < 95)
        stdnt->gr_state = Reprovado;
    else if (stdnt->total_points > 95)
        stdnt->gr_state = Aprovado;
}

int digits(int n)
{
    int result = 0;
    while (n > 0)
    {
        result++;
        n /= 10;
    }
    return result;
}

void print_stdnt_number(int number)
{
    int d = 5 - digits(number);
    for (int i = 0; i < d; i++)
        printf("0");
    printf("%d ", number);
}

void println_student(student *stdnt)
{
    print_stdnt_number(stdnt->number);
    printf("%s ", stdnt->name);
    for (int i = 0; i < 10; i++)
    {
        printf("%d", stdnt->grades[i]);
        if (i + 1 < 10)
            printf(",");
    }

    char *gs_str_ptr = grade_state_to_str(stdnt->gr_state);
    char gs_str[15];
    strcpy(gs_str, gs_str_ptr);
    free(gs_str_ptr);
    gs_str_ptr = NULL;

    printf(" Total: %d, Estado: %s\n", stdnt->total_points, gs_str);
}

void println_students(student *students, int n)
{
    for (int i = 0; i < n; i++)
        println_student(&students[i]);
}

void update_points(student *stdnt, int n, int score)
{
    stdnt->grades[n - 1] = score;
    stdnt->total_points = 0;
    for (int i = 0; i < 10; i++)
        stdnt->total_points += stdnt->grades[i];
}

int get_students(student *stdnts, int n)
{
    for (int i = 0; i < n; i++)
    {
        int number;
        char name[1000];
        scanf("%d", &number);
        scanf("%s", name);
        stdnts[i] = student_construct(number, name);
    }
    return n;
}

void testA()
{
    int n;
    scanf("%d", &n);
    student students[n];
    get_students(students, n);
    int number, grade, points;
    while (scanf("%d %d %d", &number, &grade, &points) != EOF)
    {
        for (int i = 0; i < n; i++)
        {
            if (students[i].number == number)
                update_points(&students[i], grade, points);
        }
    }
    for (int i = 0; i < n; i++)
    {
        update_grade_state(&students[i]);
        printf("correct total: %d\n", students[i].total_points);
    }
    println_students(students, n);
}

// PROBLEMA B ---------------------------------------------------------------------------------

int *ints_get_to_heap(int n)
{
    int *a = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    return a;
}

char **strings_get_to_heap(int n)
{
    char **str = malloc(n * sizeof(char));
    char buffer[1000];
    for (int i = 0; i < n; i++)
    {
        scanf("%s", buffer);
        str[i] = malloc(strlen(buffer) * sizeof(char));
        strcpy(str[i], buffer);
    }
    return str;
}

int *ints_get_unknown_number(int *out_size)
{
    out_size = malloc(2 * sizeof(int));
    int size = 1;
    while (scanf("%d", &out_size[size++]) != EOF)
        out_size = realloc(out_size, (2 + size) * sizeof(int));
    out_size[0] = size - 1;
    return out_size;
}

void strs_println(char **str_array, int length)
{
    printf("%s", str_array[0]);
    for (int i = 1; i < length; i++) // i = 1
        printf(", %s", str_array[i]);
    printf("\n");
}

void testB()
{
    char input;
    int param;

    while (scanf("%c", &input) != EOF)
    {
        if (input == 'i')
        {
            scanf("%d", &param);
            int *array = ints_get_to_heap(param); // MEMORY NEEDS TO BE FREED!!!
            ints_println(array, param, ",");
        }
        else if (input == 's')
        {
            scanf("%d", &param);
            char **str_array = strings_get_to_heap(param); // MEMORY NEEDS TO BE FREED!!!
            strs_println(str_array, param);
        }
        else if (input == '?')
        {
            int *array = ints_get_unknown_number(array); // MEMORY NEEDS TO BE FREED!!!
            ints_println(array + 1, array[0] - 1, ",");
        }
    }
}
// PROBLEMA C ---------------------------------------------------------------------------------

void testC()
{
}

// PROBLEMA F ---------------------------------------------------------------------------------

void testF()
{
}

// MAIN ---------------------------------------------------------------------------------------

int main(const int argc, const char *argv[])
{
    int x = 'F';
    if (argc > 1)
        x = *argv[1];
    if (x == 'A')
        testA();
    else if (x == 'B')
        testB();
    else if (x == 'C')
        testC();
    else if (x == 'F')
        testF();
    else if (x == 'U')
        printf("All unit tests PASSED.\n");

    return 0;
}