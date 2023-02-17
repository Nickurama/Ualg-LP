#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "our_ints.h"
#include "our_doubles.h"
const char *author = "Diogo Fonseca";

typedef struct student
{
    int number;
    char name[1000];
    int grades[10];
    int total_points;
} student;

student student_construct(int number, char *name)
{
    student stdnt;
    stdnt.number = number;
    strcpy(stdnt.name, name);
    for (int i = 0; i < 10; i++)
        stdnt.grades[i] = 0;
    stdnt.total_points = 0;
    return stdnt;
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
        stdnt->total_points += stdnt->grades[i];
        printf("%d", stdnt->grades[i]);
        if (i + 1 < 10)
            printf(",");
    }
    printf(" Total: %d\n", stdnt->total_points);
}

void println_students(student *students, int n)
{
    for (int i = 0; i < n; i++)
        println_student(&students[i]);
}

void update_points(student *stdnt, int n, int score)
{
    stdnt->grades[n - 1] = score;
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

int main()
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
    println_students(students, n);
    return 0;
}