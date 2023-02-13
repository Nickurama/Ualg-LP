#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "our_ints.h"
#include "our_doubles.h"
const char *author = "Diogo Fonseca";

double *maximum(double *a, int size)
{
    double *result = a;
    for (int i = 0; i < size; i++)
        if (*result < *(a + i))
            result = a + i;
    return result;
}

void swap_char(char *a, char *b)
{
    char buffer = *a;
    *a = *b;
    *b = buffer;
}

int get_size_str(const char *a)
{
    int result = 0;
    for (int i = 0; *(a + i); i++)
        result++;
    return result;
}

void reverseStr(char *s)
{
    int size = get_size_str(s);
    int half_size = size / 2;
    for (int i = 0; i < half_size; i++)
        swap_char(s + i, s + size - 1 - i);
}

int chars_to_ints(const char *str, int *a)
{
    int size = get_size_str(str);
    for (int i = 0; i < size; i++)
        *(a + i) = *(str + i) - 48;
    return size;
}

void print_max(double *a, int n)
{
    if (n > 0)
        printf("%.1lf\n", *maximum(a, n));
    else
        printf("*\n");
}

int main()
{
    char select;
    while (scanf("%c", &select) != EOF)
    {
        if (select == 'r')
        {
            char input[1000];
            scanf("%s", input);
            reverseStr(input);
            printf("%s\n", input);
        }
        else if (select == 'm')
        {
            double input[1000];
            int size = doubles_get_until(-1, input);
            print_max(input, size);
        }
        else
        { // unspecified
        }
    }
    return 0;
}