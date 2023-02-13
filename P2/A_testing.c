#include <stdio.h>

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