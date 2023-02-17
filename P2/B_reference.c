#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "our_ints.h"
#include "our_doubles.h"
const char *author = "Diogo Fonseca";

void soma_2(int x, int y, int *out)
{
    *out = x + y;
}

void soma_3(int *x, int *y, int z, int *out)
{
    *out = *x + *y + z;
}

void soma_todos(int **a, int n, int *out)
{
    *out = 0;
    for (int i = 0; i < n; i++)
        *out += *a[i];
}

void print_ints_from_ptr(int **a, int n)
{
    for (int i = 0; i < n - 1; i++)
        printf("%d, ", *a[i]);
    printf("%d\n", *a[n - 1]);
}

int main()
{
    int input1, input2;
    int result1, result2, result3;
    while (scanf("%d %d", &input1, &input2) != EOF)
    {
        soma_2(input1, input2, &result1);
        soma_3(&input1, &input2, result1, &result2);
        int *a[4] = {&input1, &input2, &result1, &result2};
        print_ints_from_ptr(a, 4);
        soma_todos(a, 4, &result3);
        printf("%d\n", result3);
    }
    return 0;
}