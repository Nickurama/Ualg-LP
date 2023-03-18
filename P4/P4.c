#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "our_ints.h"
#include "our_doubles.h"
const char *author = "Diogo Fonseca";

// Programa A
int ints_get_line(char *line, int *a, const char *delimiters)
{
    int size = 0;
    char *token = strtok(line, delimiters);
    while (token != NULL)
    {
        a[size++] = atoi(token);
        token = strtok(NULL, delimiters);
    }
    return size;
}

void ints_writeln_file(FILE *f, int *a, int n, const char *delimiter)
{
    if (n > 0)
        fprintf(f, "%d", a[0]);
    for (int i = 1; i < n; i++) // i = 1
        fprintf(f, "%s%d", delimiter, a[i]);
    fprintf(f, "\n");
}

void testA(void)
{
    int input[1000];
    int input_size = 0;
    char line[1000];
    FILE *finput = fopen("exemplo.csv", "r");
    FILE *foutput = fopen("output.tsv", "w");
    while (fscanf(finput, "%s", line) != EOF)
    {
        input_size = ints_get_line(line, input, ",");
        ints_writeln_file(foutput, input, input_size, "\t");
    }
    fclose(finput);
    fclose(foutput);
}

// problema B
int ints_get_line_sscanf(const char *line, int *a, const char *delimiter)
{
    int size = 0;
    sscanf(line, "%d%*s", &a[size++]); // assumes there's at least 2 values + doesn't work if delimiter is numeric
    char *buffer = strpbrk(line, delimiter);
    while (buffer != NULL)
    {
        sscanf(buffer + 1, "%d%*s", &a[size++]);
        buffer = strpbrk(buffer + 1, delimiter);
    }
    return size;
}

void testB(void)
{
    int input[1000];
    int input_size = 0;
    char line[1000];
    FILE *finput = fopen("exemplo.csv", "r");
    FILE *foutput = fopen("output.tsv", "w");
    while (fscanf(finput, "%s", line) != EOF)
    {
        input_size = ints_get_line_sscanf(line, input, ",");
        ints_writeln_file(foutput, input, input_size, "\t");
    }
    fclose(finput);
    fclose(foutput);
}

// Problema C
char **my_tokenizer(const char *s, const char *delim, int *out_token_count)
{
    int s_len = strlen(s);
    int token_length;
    char **tokens = malloc(sizeof(char *));
    int str_ar_len = 0;

    while ((token_length = strcspn(s, delim)) <= s_len)
    {
        char *token = malloc((token_length + 1) * sizeof(char));
        memcpy(token, s, token_length * sizeof(char));
        token[token_length] = '\0';
        tokens = realloc(tokens, (str_ar_len + 1) * sizeof(char *));
        tokens[str_ar_len++] = token;
        s += token_length + 1;
        s_len -= token_length + 1;
    }

    *out_token_count = str_ar_len;
    return tokens;
}

void strings_writeln_file(FILE *f, char **strings, int n, const char *delimiter)
{
    if (n > 0)
        fprintf(f, "%s", strings[0]);
    for (int i = 1; i < n; i++) // i = 1
        fprintf(f, "%s%s", delimiter, strings[i]);
    fprintf(f, "\n");
}

void free_tokens(char **tokens, int n)
{
    for (int i = 0; i < n; i++)
        free(tokens[i]);
    free(tokens);
}

FILE *ask_for_file(const char *access)
{
    char file_name[100];
    FILE *f;
    do
    {
        printf("Please type the name of the file:");
        scanf("%99s", file_name);
        f = fopen(file_name, access);
        if (f == NULL)
            printf("Error opening %s!\n", access);
    } while (f == NULL);
    return f;
}

void testC(void)
{
    char line[1000];
    char **tokens;
    int tokens_len;
    printf("Input file:\n");
    FILE *in = ask_for_file("r");
    printf("Output file:\n");
    FILE *out = ask_for_file("w");
    while (fscanf(in, "%1000s", line) != EOF)
    {
        tokens = my_tokenizer(line, ";", &tokens_len);
        strings_writeln_file(out, tokens, tokens_len, "\t");
    }
    fclose(in);
    fclose(out);
    free_tokens(tokens, tokens_len);
    printf("Program terminated.\n");
}

// Problema D

struct Point2D
{
    int x;
    int y;
};

void print_point2d(struct Point2D p)
{
    printf("(%d,%d)", p.x, p.y);
}

void add_identations(FILE *f, int identation_level)
{
    for (int i = 0; i < identation_level; i++)
        fprintf(f, "\t");
}

void point2d_write_json(FILE *f, struct Point2D p, int identation_level)
{
    // line 1
    add_identations(f, identation_level);
    fprintf(f, "\"position\": {\n");

    // line 2
    add_identations(f, identation_level + 1);
    fprintf(f, "\"x\": %d,\n", p.x);

    // line 3
    add_identations(f, identation_level + 1);
    fprintf(f, "\"y\": %d\n", p.y);

    // line 4
    add_identations(f, identation_level);
    fprintf(f, "},\n");
}

struct Color
{
    int r;
    int g;
    int b;
    float alpha;
};

void color_write_json(FILE *f, struct Color *c, int identation_level)
{
    // line 1
    add_identations(f, identation_level);
    fprintf(f, "\"color\": {\n");

    // line 2
    add_identations(f, identation_level + 1);
    fprintf(f, "\"r\": %d,\n", c->r);

    // line 3
    add_identations(f, identation_level + 1);
    fprintf(f, "\"g\": %d,\n", c->g);

    // line 4
    add_identations(f, identation_level + 1);
    fprintf(f, "\"b\": %d,\n", c->b);

    // line 5
    add_identations(f, identation_level + 1);
    fprintf(f, "\"alpha\": %.2lf\n", c->alpha);

    // line 6
    add_identations(f, identation_level);
    fprintf(f, "},\n");
}

void print_color(struct Color *c)
{
    printf("C(%d,%d,%d,%.2f)", c->r, c->g, c->b, c->alpha);
}

struct Rectangle
{
    struct Point2D position;
    int width;
    int height;
    struct Color *color;
    char name[20];
    char *description;
    const char *type;
};

void rectangle_write_json(FILE *f, struct Rectangle *r, int identation_level)
{
    point2d_write_json(f, r->position, identation_level);

    add_identations(f, identation_level);
    fprintf(f, "\"width\": %d,\n", r->width);

    add_identations(f, identation_level);
    fprintf(f, "\"height\": %d,\n", r->height);

    color_write_json(f, r->color, identation_level);

    add_identations(f, identation_level);
    fprintf(f, "\"name\": \"%s\",\n", r->name);

    add_identations(f, identation_level);
    fprintf(f, "\"description\": \"%s\",\n", r->description);

    add_identations(f, identation_level);
    fprintf(f, "\"type\": \"%s\"\n", r->type);
}

void rectangles_write_json(FILE *f, struct Rectangle *rectangles[], int n, int identation_level)
{
    add_identations(f, identation_level);
    fprintf(f, "[\n");

    for (int i = 0; i < n; i++)
    {
        add_identations(f, identation_level + 1);
        fprintf(f, "{\n");

        rectangle_write_json(f, rectangles[i], identation_level + 2);

        add_identations(f, identation_level + 1);
        if (i + 1 == n)
            fprintf(f, "}\n");
        else
            fprintf(f, "},\n");
    }

    add_identations(f, identation_level);
    fprintf(f, "]\n");
}

struct Rectangle *rectangle(int x, int y, int width, int height, struct Color c, char *name, char *description, const char *type)
{
    struct Rectangle *r = (struct Rectangle *)malloc(sizeof(struct Rectangle));
    assert(r != NULL);
    r->position.x = x;
    r->position.y = y;
    r->width = width;
    r->height = height;
    // isto é errado, porque o objeto c é um parâmetro, e vai desaparecer assim que o método terminar
    r->color = &c;
    // neste caso a forma correta é criar uma cópia da cor
    r->color = (struct Color *)malloc(sizeof(struct Color));
    *(r->color) = c;
    strcpy(r->name, name);
    r->description = strdup(description);

    // neste caso, posso fazer isto, pq a string recebida é constante e nunca vai ser mudada, por isso o risco
    // de ter um ponteiro para o mesmo objeto não é grave
    // o único problema que poderá ocorrer é se alguém externamente apagar a string que foi recebida
    r->type = type;

    return r;
}

void print_rectangle(struct Rectangle *r)
{
    print_point2d(r->position);
    printf(",%d,%d,", r->width, r->height);
    print_color(r->color);
    printf("\nType:%s\nName:%s\nDescription:%s\n", r->type, r->name, r->description);
}

int get_rectangles(struct Rectangle **rectangles, int n)
{
    int i = 0;
    int x, y, w, h;
    char nome[100];
    char description[1000];
    struct Color c;

    while (i < n && scanf("%d%d%d%d%d%d%d%f", &x, &y, &w, &h, &c.r, &c.g, &c.b, &c.alpha) != EOF)
    {
        gets(nome);
        gets(nome);
        gets(description);
        rectangles[i++] = rectangle(x, y, w, h, c, nome, description, "User defined");
    }

    return i;
}

#define WIDTH_RES 1920
#define HEIGHT_RES 1080
#define RGB_MAX 256

char *random_mock_string(int n)
{
    char *s = (char *)malloc((n + 1) * sizeof(char));
    for (int i = 0; i < n; i++)
    {
        s[i] = '0' + rand() % 74;
    }
    s[n] = '\0';

    return s;
}

struct Rectangle *random_mock_rectangle()
{
    int x, y, w, h;
    struct Color c;
    struct Rectangle *r;

    x = rand() % WIDTH_RES;
    y = rand() % HEIGHT_RES;
    w = rand() % WIDTH_RES;
    h = rand() % HEIGHT_RES;
    c.r = rand() % RGB_MAX;
    c.g = rand() % RGB_MAX;
    c.b = rand() % RGB_MAX;
    c.alpha = ((float)(rand() % 100)) / 100;

    char *name = random_mock_string(8);
    char *description = random_mock_string(30);
    r = rectangle(x, y, w, h, c, name, description, "Random Mock");
    free(name);
    free(description);
    return r;
}

void free_rectangle(struct Rectangle *r)
{
    free(r->color);
    free(r->description);
    free(r);
}

void testD(void)
{
    int seed;

    scanf("%d", &seed);
    srand(seed);

    struct Rectangle *rectangles[5];

    for (int i = 0; i < 5; i++)
    {
        rectangles[i] = random_mock_rectangle();
    }

    FILE *f = fopen("rectangles.json", "w");
    rectangles_write_json(f, rectangles, 5, 0);
    fclose(f);

    for (int i = 0; i < 5; i++)
    {
        free_rectangle(rectangles[i]);
    }
}

// Problema E
// reduceOrDefault
// map
// all
// any
// filter
// findFirst
// max
typedef int (*IntOperator)(int);
typedef int (*IntBinaryOperator)(int, int);
typedef int (*IntPredicate)(int);
typedef char (*CharOperator)(char);

void map(int in[], int n, IntOperator op)
{
    for (int i = 0; i < n; i++)
        in[i] = op(in[i]);
}

void map_string(char a[], int n, CharOperator op)
{
    for (int i = 0; i < n; i++)
        a[i] = op(a[i]);
}

int all(int a[], int n, IntPredicate p)
{
    for (int i = 0; i < n; i++)
        if (!p(a[i]))
            return 0;
    return 1;
}

int any(int a[], int n, IntPredicate p)
{
    for (int i = 0; i < n; i++)
        if (p(a[i]))
            return 1;
    return 0;
}

int filter(int in[], int out[], int n, IntPredicate p)
{
    int size = 0;
    for (int i = 0; i < n; i++)
        if (p(in[i]))
            out[size++] = in[i];
    return size;
}

int *find_first(int a[], int n, IntPredicate p)
{
    for (int i = 0; i < n; i++)
        if (p(a[i]))
            return &a[i];
    return NULL;
}

int reduce_or_default(int a[], int n, int default_value, IntBinaryOperator op)
{
    if (n <= 0)
        return default_value;

    int buffer = a[0];
    for (int i = 1; i < n; i++)
        buffer = op(buffer, a[i]);
    return buffer;
}

void testE(void)
{
    // TODO
}

// Problema F
// ordenacao de alunos
typedef enum e_EstadoAvaliacao
{
    Aprovado,
    Reprovado,
    Faltou,
    Nao_Admitido,
    Sem_Frequencia
} EstadoAvaliacao;

// eu consigo implementar isto sem este array de strings constante, mas torna a implementação um pouco mais simples e elegante
const char *STR_ESTADOS_AVALIACAO[5] = {"Aprovado", "Reprovado", "Faltou", "Nao_Admitido", "Sem_Frequencia"};

EstadoAvaliacao str_to_estado_aval(char *s)
{
    for (int i = Aprovado; i <= Sem_Frequencia; i++)
    {
        if (strcmp(s, STR_ESTADOS_AVALIACAO[i]) == 0)
        {
            return i;
        }
    }

    // opcao 1, retornar um valor considerado invalido
    // return -1;
    // opcao 2, retornar um valor por omissão
    // return Reprovado;
    // opcao 3 - forçar um erro
    assert(0);
}

const char *estado_aval_to_str(EstadoAvaliacao estado)
{
    return STR_ESTADOS_AVALIACAO[estado];
}

#define N_AVAL 10

typedef struct S_Aluno
{
    int numero;
    char nome[100];
    EstadoAvaliacao estado_avaliacao;
    int avaliacoes[N_AVAL];
    int total;
} Aluno;

Aluno aluno(int numero, char *nome)
{
    Aluno a;
    a.numero = numero;
    strcpy(a.nome, nome);
    a.estado_avaliacao = Reprovado;
    for (int i = 0; i < N_AVAL; i++)
    {
        a.avaliacoes[i] = 0;
    }
    a.total = 0;
    return a;
}

void atualizaEstadoAvaliacao(Aluno *a)
{
    if (a->total == 0)
    {
        a->estado_avaliacao = Sem_Frequencia;
    }
    else if (a->avaliacoes[8] == 0 && a->avaliacoes[9] == 0)
    {
        a->estado_avaliacao = Faltou;
    }
    else if (a->avaliacoes[8] < 15 && a->avaliacoes[9] < 15)
    {
        a->estado_avaliacao = Reprovado;
    }
    else if (a->total < 95)
    {
        a->estado_avaliacao = Reprovado;
    }
    else
    {
        a->estado_avaliacao = Aprovado;
    }
}

void println_aluno(Aluno *a)
{
    printf("%05d %s ", a->numero, a->nome);
    ints_print(a->avaliacoes, N_AVAL, ",");
    printf(" Total: %d, Estado: %s\n", a->total, estado_aval_to_str(a->estado_avaliacao));
}

int get_alunos_notas(Aluno *alunos, int n)
{
    // TODO
    return 0;
}

typedef int (*AlunoComparer)(const Aluno *, const Aluno *);
typedef int (*Comparer)(const void *, const void *);

int compare_by_numero(const Aluno *a1, const Aluno *a2)
{
    // TODO
    return 0;
}

int compare_by_nome(const Aluno *a1, const Aluno *a2)
{
    // TODO
    return 0;
}

int compare_by_total(const Aluno *a1, const Aluno *a2)
{
    // TODO
    return 0;
}

void testF()
{

    // TODO
}

typedef void (*TestFunction)(void);

// Este main utiliza funcoes como cidadaos de 1a classe.
// Desta forma consigo determinar qual a funcao de teste a executar sem usar um grande comboio de if, else if.
int main(const int argc, const char *argv[])
{
    TestFunction functions[] = {testA, testB, testC, testD, testE, testF};

    int x = 'A';
    if (argc > 1)
        x = *argv[1];

    // vou buscar a funcao correta ao array a partir da letra (letra A = posicao 0, letra B = posicao 1, etc)
    TestFunction f = functions[x - 'A'];
    // mando executar f
    (*f)();

    return 0;
}