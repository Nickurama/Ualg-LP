#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "our_ints.h"
#include "our_doubles.h"
const char *author = "Diogo Fonseca";

void f1(int val)
{
    int x;
    x = val;
    printf("%p\n", &x);
}
void f2(int lixo)
{
    int y;
    printf("%p\n", &y);
}
int main()
{
    f1(5);
    f2(7);
    return 0;
}