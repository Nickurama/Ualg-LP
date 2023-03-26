#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <math.h>

int main(void)
{
    int ns[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int i = 3;
    ns[i++] = ns[i] - 1; // ns[3] = ns[3] - 1
    printf("%d\n", ns[i]);
    return 0;
}