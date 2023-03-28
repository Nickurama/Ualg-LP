#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "submission.h"
const char *author = "Diogo Fonseca";

const int DATE_STR_SIZE = 17;  // 16 + 1
const int MAX_LINE_SIZE = 564; // number is hardcoded in get_subs_from_file()
const char *STR_RESULTS[13] = {
    "Accepted", "Presentation Error", "Wrong Answer", "Output Limit Exceeded",
    "Memory Limit Exceeded", "Time Limit Exceeded", "Invalid Function", "Runtime Error",
    "Compile Time Error", "Invalid Submission", "Program Size Exceeded", "Requires Reevaluation",
    "Evaluating"};
const char *STR_STATES[2] = {"pending", "final"};
const char *FILE_DELIM = "\t";
const char *PRINT_DELIM = ",";
const char *COMMAND_STAT = "STATS";
const char *COMMAND_UPDATE = "UPDATE";
const char *COMMAND_ORDER = "ORDER";
const char *COMMAND_ORDER_PARAM0 = "number_ascending";
const char *COMMAND_ORDER_PARAM1 = "number_descending";
const char *COMMAND_ORDER_PARAM2 = "id";
const char *COMMAND_ORDER_PARAM3 = "problem";
const char *COMMAND_PRINT = "PRINT";
const char *COMMAND_PRINT_ALL = "*";
const char *HEADER = "#	Time	Points	Group	Id	Team	Problem	Language	Result	State";
#define TIME_FORMAT "%d/%d/%d %d:%d"
#define TIME_FORMAT_PRINT "%d%d%d%d/%d%d/%d%d %d%d:%d%d"

// Types

typedef int (*Comparer)(const void *, const void *);

typedef enum Result
{
    Accepted,
    Presentation_Error,
    Wrong_Answer,
    Output_Limit_Exceeded,
    Memory_Limit_Exceeded,
    Time_Limit_Exceeded,
    Invalid_Function,
    Runtime_Error,
    Compile_Time_Error,
    Invalid_Submission,
    Program_Size_Exceeded,
    Requires_Reevaluation,
    Evaluating
} Result;

typedef enum State
{
    Pending,
    Final
} State;

typedef struct Date
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
} Date;

typedef struct Submission
{
    int number;
    Date *time;
    int points;
    char *group;
    char *id;
    char *team;
    char *problem;
    char *language;
    Result result;
    State state;

} Submission;

// Tools

char **my_tokenizer(const char *s, const char *delim, int *out_token_count)
{
    int s_len = strlen(s);
    int token_length;
    char **tokens = malloc(100 * sizeof(char *));
    int str_ar_len = 0;

    while ((token_length = strcspn(s, delim)) <= s_len)
    {
        if ((str_ar_len % 100) == 0)
            tokens = realloc(tokens, (((str_ar_len / 100) + 1) * 100) * sizeof(char *));
        char *token = malloc((token_length + 1) * sizeof(char));
        memcpy(token, s, token_length * sizeof(char));
        token[token_length] = '\0';

        tokens[str_ar_len++] = token;
        s += token_length + 1;
        s_len -= token_length + 1;
    }
    *out_token_count = str_ar_len;
    return tokens;
}

void free_tokens(char **tokens, int n)
{
    for (int i = 0; i < n; i++)
        free(tokens[i]);
    free(tokens);
}

// Constructors / conversions / frees

// result
Result str_to_result(const char *s)
{
    for (int i = Accepted; i <= Evaluating; i++)
        if (strcmp(s, STR_RESULTS[i]) == 0)
            return i;
    assert(0);
}

const char *result_to_str(Result r)
{
    return STR_RESULTS[r];
}

// state
State str_to_state(const char *str)
{
    for (int i = Pending; i <= Final; i++)
        if (strcmp(str, STR_STATES[i]) == 0)
            return i;
    assert(0);
}

const char *state_to_str(State st)
{
    return STR_STATES[st];
}

// date
Date *date_cnstrct(int year, int month, int day, int hour, int minute)
{
    Date *date = malloc(sizeof(Date));
    date->year = year;
    date->month = month;
    date->day = day;
    date->hour = hour;
    date->minute = minute;
    return date;
}

Date *str_to_date(const char *str)
{
    int y, mo, d, h, m;
    sscanf(str, TIME_FORMAT, &y, &mo, &d, &h, &m);
    Date *date = date_cnstrct(y, mo, d, h, m);
    return date;
}

int get_digit(int n, int digit)
{
    int x = n / (int)(pow(10, digit));
    return x % 10;
}

char *date_to_str(char *str_out, Date *d)
{
    sprintf(str_out, TIME_FORMAT_PRINT,
            get_digit(d->year, 3), get_digit(d->year, 2), get_digit(d->year, 1), get_digit(d->year, 0),
            get_digit(d->month, 1), get_digit(d->month, 0),
            get_digit(d->day, 1), get_digit(d->day, 0),
            get_digit(d->hour, 1), get_digit(d->hour, 0),
            get_digit(d->minute, 1), get_digit(d->minute, 0));
    return str_out;
}

void date_free(Date *date)
{
    free(date);
}

// submission
Submission *submission_cnstrct(int number, Date *time, int points, char *group, char *id, char *team, char *problem, char *language, Result result, State state)
{
    Submission *sub = malloc(sizeof(Submission));

    // misc
    sub->time = time;

    // ints
    sub->number = number;
    sub->points = points;
    sub->result = result;
    sub->state = state;

    // strings
    sub->group = malloc((strlen(group) + 1) * sizeof(char));
    sub->id = malloc((strlen(id) + 1) * sizeof(char));
    sub->team = malloc((strlen(team) + 1) * sizeof(char));
    sub->problem = malloc((strlen(problem) + 1) * sizeof(char));
    sub->language = malloc((strlen(language) + 1) * sizeof(char));

    strcpy(sub->group, group);
    strcpy(sub->id, id);
    strcpy(sub->team, team);
    strcpy(sub->problem, problem);
    strcpy(sub->language, language);

    return sub;
}

Submission *str_to_sub(const char *str, const char *delim, Submission *out)
{
    int token_count = 0;
    char **tokens = my_tokenizer(str, delim, &token_count);
    int sub_n = atoi(tokens[0]);
    Date *sub_date = str_to_date(tokens[1]);
    int sub_points = atoi(tokens[2]);
    char *sub_group = tokens[3];
    char *sub_id = tokens[4];
    char *sub_team = tokens[5];
    char *sub_problem = tokens[6];
    char *sub_language = tokens[7];
    Result sub_result = str_to_result(tokens[8]);
    State sub_state = str_to_state(tokens[9]);

    Submission *sub = submission_cnstrct(sub_n, sub_date, sub_points, sub_group, sub_id, sub_team, sub_problem, sub_language, sub_result, sub_state);

    free_tokens(tokens, token_count);
    out = sub;
    return sub;
}

char *sub_to_str(char *str_out, const Submission *sub, const char *delim, int is_print_format)
{
    char date_str_buffer[DATE_STR_SIZE];
    date_to_str(date_str_buffer, sub->time);
    int i;
    i = sprintf(str_out, "%d%s", sub->number, delim);
    i += sprintf(str_out + i, "%s%s", date_str_buffer, delim);
    i += sprintf(str_out + i, "%d%s", sub->points, delim);
    if (is_print_format)
        i += sprintf(str_out + i, "%s%s", sub->group, delim);
    i += sprintf(str_out + i, "%s%s", sub->id, delim);
    if (is_print_format)
        i += sprintf(str_out + i, "%s%s", sub->team, delim);
    i += sprintf(str_out + i, "%s%s", sub->problem, delim);
    if (is_print_format)
        i += sprintf(str_out + i, "%s%s", sub->language, delim);
    i += sprintf(str_out + i, "%s%s", result_to_str(sub->result), delim);
    i += sprintf(str_out + i, "%s", state_to_str(sub->state));
    return str_out;
}

void submission_free(Submission *sub)
{
    date_free(sub->time);
    free(sub->group);
    free(sub->id);
    free(sub->team);
    free(sub->problem);
    free(sub->language);
    free(sub);
}

// Functions

Submission **get_subs_from_file(FILE *f, int *size)
{
    Submission **sub = malloc(100 * sizeof(Submission *));
    char line[MAX_LINE_SIZE]; // 10(int) + 16(time) + 100(group) + 100(id) + 100(name) + 100(problem) + 100(language) + 21(result max) + 7(state max) + 9*1(delimiter '\t') + 1(\n)
    int i = 0;
    while (fscanf(f, "%[^\n]%*c", line) != EOF) // MAX_LINE_SIZE - 1, remove white_space and new_line
    {
        if ((i % 100) == 0)
            sub = realloc(sub, (((i / 100) + 1) * 100) * sizeof(Submission *));

        int len = strlen(line);
        if (line[len - 1] == ' ')
            line[len - 1] = '\0'; // removes white space at the end of the string

        sub[i] = str_to_sub(line, FILE_DELIM, sub[i]);
        i++;
    }
    *size = i;
    return sub;
}

void submissions_free(Submission **subs, int size)
{
    for (int i = 0; i < size; i++)
        submission_free(subs[i]);
    free(subs);
}

void print_sub(const Submission *sub, const char *delim)
{
    char buffer[MAX_LINE_SIZE];
    sub_to_str(buffer, sub, delim, 0);
    printf("%s\n", buffer);
}

void print_subs(const Submission **subs, const char *delim, int size)
{
    for (int i = 0; i < size; i++)
        print_sub(subs[i], delim);
}

Submission **get_accepted_subs(Submission **subs, int size, int *out_size)
{
    int n = 0;
    Submission **accepted = malloc(100 * sizeof(Submission *));
    for (int i = 0; i < size; i++)
    {
        if ((i % 100) == 0)
            accepted = realloc(accepted, (((i / 100) + 1) * 100) * sizeof(Submission *));

        if (subs[i]->result == Accepted)
            accepted[n++] = subs[i];
    }
    *out_size = n;
    return accepted;
}

FILE *get_file_from_stdout(char *mode)
{
    char filename[101];
    FILE *f;
    do
    {
        scanf("%100s%*c", filename);
        f = fopen(filename, mode);
        if (f == NULL)
            printf("file '%s' not found!\n", filename);
    } while (f == NULL);
    return f;
}

// name_out should be 101 characters long
FILE *get_file_name_from_stdout(const char *mode, char *name_out)
{
    char filename[101];
    FILE *f;
    do
    {
        scanf("%100s%*c", filename);
        f = fopen(filename, mode);
        if (f == NULL)
            printf("file '%s' not found!\n", filename);
    } while (f == NULL);
    strcpy(name_out, filename);
    return f;
}

FILE *file_change_mode(FILE *f, char *filename, char *new_mode)
{
    fclose(f);
    f = fopen(filename, new_mode);
    return f;
}

// STATS command
Submission **get_subs_by_problem(Submission **subs, int size, const char *problem, int *out_size)
{
    int n = 0;
    Submission **selected = malloc(100 * sizeof(Submission *));
    for (int i = 0; i < size; i++)
    {
        if ((i % 100) == 0)
            selected = realloc(selected, (((i / 100) + 1) * 100) * sizeof(Submission *));

        if (strcmp(subs[i]->problem, problem) == 0)
            selected[n++] = subs[i];
    }
    *out_size = n;
    return selected;
}

void get_problem_stats(Submission **subs, int size, int *problem_stats)
{
    for (int i = 0; i < size; i++)
        problem_stats[subs[i]->result]++;
}

void print_stats(const int *stats, const char *problem, int total)
{
    int other = stats[Output_Limit_Exceeded] + stats[Invalid_Function] + stats[Invalid_Submission] + stats[Program_Size_Exceeded] + stats[Requires_Reevaluation] + stats[Evaluating];
    printf("Problem: %s\n", problem);
    printf("Total Submissions: %d\n", total);
    printf("Accepted: %d\n", stats[Accepted]);
    printf("Presentation Error: %d\n", stats[Presentation_Error]);
    printf("Wrong Answer: %d\n", stats[Wrong_Answer]);
    printf("Memory Limit Exceeded: %d\n", stats[Memory_Limit_Exceeded]);
    printf("Time Limit Exceeded: %d\n", stats[Time_Limit_Exceeded]);
    printf("Run Time Error: %d\n", stats[Runtime_Error]);
    printf("Compile Time Error: %d\n", stats[Compile_Time_Error]);
    printf("Other Errors: %d\n", other);
}

// UPDATE command

Submission *get_sub_by_number(Submission **subs, int size, int number)
{
    for (int i = 0; i < size; i++)
        if (subs[i]->number == number)
            return subs[i];
    return NULL;
}

void update_sub(Submission *s, int points)
{
    s->points = points;
    s->result = Accepted;
    s->state = Final;
}

void file_update(FILE *f, Submission **subs, int size)
{
    rewind(f);
    fprintf(f, "%s\n", HEADER);
    char line[MAX_LINE_SIZE];
    for (int i = 0; i < (size); i++)
    {
        sub_to_str(line, subs[i], FILE_DELIM, 1);
        fprintf(f, "%s\n", line);
    }
}

// SORT command

int subs_number_cmp_asc(const Submission **s0, const Submission **s1)
{
    return (*s0)->number - (*s1)->number;
}

int subs_number_cmp_desc(const Submission **s0, const Submission **s1)
{
    return (*s1)->number - (*s0)->number;
}

int subs_id_cmp(const Submission **s0, const Submission **s1)
{
    int n = strcmp((*s0)->id, (*s1)->id);
    if (n == 0)
        n = subs_number_cmp_desc(s0, s1);
    return n;
}
int subs_problem_cmp(const Submission **s0, const Submission **s1)
{
    int n = strcmp((*s0)->problem, (*s1)->problem);
    if (n == 0)
        n = subs_number_cmp_desc(s0, s1);
    return n;
}

// Commands

void command_stats(char *problem, Submission **subs, int size)
{
    int problem_stats[13] = {0}; // initialize array elements at 0

    int selected_size = 0;
    Submission **selected = get_subs_by_problem(subs, size, problem, &selected_size);
    get_problem_stats(selected, selected_size, problem_stats);
    free(selected);
    print_stats(problem_stats, problem, selected_size);
}

int command_update(char *params, Submission **subs, int size)
{
    int number, points;
    sscanf(params, "%d %d", &number, &points);
    Submission *s = get_sub_by_number(subs, size, number);
    if (s != NULL)
    {
        update_sub(s, points);
        print_sub(s, PRINT_DELIM);
    }
    else
        printf("Invalid Submission!\n");
    return 1;
}

void command_order(char *order, Submission **subs, int size)
{
    if (strcmp(order, COMMAND_ORDER_PARAM0) == 0) // number ascending
        qsort(subs, size, sizeof(Submission *), (Comparer)subs_number_cmp_asc);
    else if (strcmp(order, COMMAND_ORDER_PARAM1) == 0) // number descending
        qsort(subs, size, sizeof(Submission *), (Comparer)subs_number_cmp_desc);
    else if (strcmp(order, COMMAND_ORDER_PARAM2) == 0) // id ascending
        qsort(subs, size, sizeof(Submission *), (Comparer)subs_id_cmp);
    else if (strcmp(order, COMMAND_ORDER_PARAM3) == 0) // problem ascending
        qsort(subs, size, sizeof(Submission *), (Comparer)subs_problem_cmp);
    else
        printf("Invalid sorting order '%s'!\n", order);
}

void command_print(char *params, Submission **subs, int size)
{
    if (strcmp(params, COMMAND_PRINT_ALL) == 0)
        print_subs((const Submission **)subs, PRINT_DELIM, size);
    else
    {
        int n = atoi(params);
        if (n > size)
            n = size;
        print_subs((const Submission **)subs, PRINT_DELIM, n);
    }
}

int command_input(Submission **subs, int size, char *command, char *params)
{
    int has_updated = 0;
    if (strcmp(command, COMMAND_STAT) == 0) // STATS <problem>
        command_stats(params, subs, size);
    else if (strcmp(command, COMMAND_UPDATE) == 0) // UPDATE <number> <points>
        has_updated = command_update(params, subs, size);
    else if (strcmp(command, COMMAND_ORDER) == 0) // ORDER <criteria>
        command_order(params, subs, size);
    else if (strcmp(command, COMMAND_PRINT) == 0) // PRINT <n>
        command_print(params, subs, size);
    else
        printf("unrecognized command '%s'\n", command);
    return has_updated;
}

// Test functions

void interactive_command_line()
{
    // get file
    char filename[101];
    FILE *f = get_file_name_from_stdout("r", filename);

    // get submissions
    fscanf(f, "%*[^\n]%*c"); // Discard first line
    int subs_size = 0;
    Submission **submissions = get_subs_from_file(f, &subs_size);

    // command line
    int has_updated = 0;
    char input[41], command[21], params[21];
    int read;
    while ((read = scanf("%40[^\n]%*c", input)) != EOF)
    {
        if (read > 0)
        {
            sscanf(input, "%20s %20[^\n]%*c", command, params);
            has_updated += command_input(submissions, subs_size, command, params);
            if (has_updated > 1)
                has_updated = 1;
        }
        else
            scanf("%*c");
    }

    // write updates
    if (has_updated)
    {
        qsort(submissions, subs_size, sizeof(Submission *), (Comparer)subs_number_cmp_desc);
        file_change_mode(f, filename, "w");
        file_update(f, submissions, subs_size);
    }

    // cleanup
    submissions_free(submissions, subs_size);
    fclose(f);
}

void teste_leitura_simples()
{
    FILE *f = get_file_from_stdout("r");
    fscanf(f, "%*[^\n]%*c"); // Discard first line
    int subs_size = 0;
    Submission **submissions = get_subs_from_file(f, &subs_size);
    int accepted_size = 0;
    Submission **accepted = get_accepted_subs(submissions, subs_size, &accepted_size);
    print_subs((const Submission **)accepted, PRINT_DELIM, accepted_size);
    submissions_free(submissions, subs_size);
    free(accepted); // accepted is a subspace of submissions, so it's pointers have already been freed in the line prior
    fclose(f);
}

void teste_estatisticas()
{
    interactive_command_line();
}

void teste_atualizacao()
{
    interactive_command_line();
}

void teste_ordenacao()
{
    interactive_command_line();
}

void teste_ranking()
{
}
