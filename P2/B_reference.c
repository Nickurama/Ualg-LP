#include <stdio.h>

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
    for (int i = 0; i < n; i++)
    {
        printf("%d", *a[i]);
        if (i + 1 < n)
            printf(",");
    }
    printf("\n");
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