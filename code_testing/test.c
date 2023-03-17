#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <math.h>

int main(void)
{
    char *strings[100];
    char buffer[100];
    int n = 0;
    // int read;

    // este código tem um problema se o input começar com \n
    while (scanf("%[^\n]%*c", buffer) != EOF)
    {
        printf("test 1");
        strings[n++] = strdup(buffer);
        printf("test 2");
    }

    for (int i = 0; i < n; i++)
    {
        printf("%s\n", strings[i]);
    }

    return 0;
}