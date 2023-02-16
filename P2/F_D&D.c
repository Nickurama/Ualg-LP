#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "our_ints.h"
#include "our_doubles.h"
const char *author = "Diogo Fonseca";

enum m_size
{
    tiny,
    small,
    medium,
    large,
    huge,
    gargantuan
};

typedef struct monster
{
    char name[1000];
    char type[1000];
    enum m_size size; // 0 = tiny, 1 = small, 2 = medium, 3 = large, 4 = huge, 5 = gargantuan
    int ac;           // (armor class)
    int hp;           // (hit points)
    double cr;        // (challenge rating)
} monster;

monster monster_constructor(char *name, char *type, enum m_size size, int ac, int hp, double cr)
{
    monster m;
    strcpy(m.name, name);
    strcpy(m.type, type);
    m.size = size;
    m.ac = ac;
    m.hp = hp;
    m.cr = cr;
    return m;
}

void print_monster(monster *m)
{
    printf("%s - ", m->name);
    if (m->size == tiny)
        printf("Tiny");
    else if (m->size == small)
        printf("Small");
    else if (m->size == medium)
        printf("Medium");
    else if (m->size == large)
        printf("Large");
    else if (m->size == huge)
        printf("Huge");
    else if (m->size == gargantuan)
        printf("Gargantuan");
    printf(" %s, AC:%d, HP:%d, CR:%.2lf\n", m->type, m->ac, m->hp, m->cr);
}

void print_monsters(monster **m, int n)
{
    for (int i = 0; i < n; i++)
        print_monster(m[i]);
}

void monsters_to_monsters_ptr(monster *in, int n, monster **out)
{
    for (int i = 0; i < n; i++)
        out[i] = &in[i];
}

int search_monsters_cr(monster **in, int n, monster **out, double cr_min, double cr_max)
{
    int size = 0;
    for (int i = 0; i < n; i++)
        if (in[i]->cr <= cr_max && in[i]->cr >= cr_min)
            out[size++] = in[i];
    return size;
}

int search_monsters_type(monster **in, int n, monster **out, char *type)
{
    int size = 0;
    for (int i = 0; i < n; i++)
        if (!strcmp(in[i]->type, type))
            out[size++] = in[i];
    return size;
}

int get_monsters(monster *monsters, int n)
{
    for (int i = 0; i < n; i++)
    {
        char name[1000], type[1000], mon_size_str[11];
        enum m_size size;
        int ac, hp;
        double cr;

        scanf("%s %s %s %d %d %lf", name, type, mon_size_str, &ac, &hp, &cr);
        if (!strcmp(mon_size_str, "Tiny"))
            size = tiny;
        else if (!strcmp(mon_size_str, "Small"))
            size = small;
        else if (!strcmp(mon_size_str, "Medium"))
            size = medium;
        else if (!strcmp(mon_size_str, "Large"))
            size = large;
        else if (!strcmp(mon_size_str, "Huge"))
            size = huge;
        else if (!strcmp(mon_size_str, "Gargantuan"))
            size = gargantuan;
        monster m = monster_constructor(name, type, size, ac, hp, cr);
        monsters[i] = m;
    }
    return n;
}

int main()
{
    int n;
    scanf("%d", &n);
    monster m[n];
    get_monsters(m, n);

    char type[1000], cr_min_str[64];
    while (scanf("%s %s", type, cr_min_str) != EOF)
    {
        double cr_min, cr_max;
        monster *m_result[n];
        monsters_to_monsters_ptr(m, n, m_result);
        int size_result = search_monsters_type(m_result, n, m_result, type);
        if (strcmp(cr_min_str, "*"))
        {
            cr_min = atof(cr_min_str);
            scanf("%lf", &cr_max);
            size_result = search_monsters_cr(m_result, size_result, m_result, cr_min, cr_max);
        }

        if (size_result == 0)
            printf("None\n");
        else
            print_monsters(m_result, size_result);
    }
    return 0;
}