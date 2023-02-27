#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "our_ints.h"
#include "our_doubles.h"
const char *author = "Diogo Fonseca";

int *ints_get_to_heap(int n)
{
    int *a = malloc(n*sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%s", a[i]);
    return a;
}

char **strings_get_to_heap(int n)
{
    char **s = malloc(n*sizeof(int));
    for (int i = 0; i < n; i++)
    {
        scanf("%s", s[i]);
    }
    return s;
}


int main()
{
    return 0;
}