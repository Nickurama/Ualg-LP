#include <stdio.h>
const char *author = "Diogo Fonseca";

double *maximum(double *a, int size)
{
    double *result = a;
    for (int i = 0; i < size; i++)
        if (*result < *(a + i))
            result = a + i;
    return result;
}

int main()
{
    double input1, input2;
    while (scanf("%d %d", &input1, &input2) != EOF)
    {
        double a[2] = {input1, input2};
        double *result = maximum(a, 2);
        printf("%d", *result);
    }
    return 0;
}