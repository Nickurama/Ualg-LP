#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#include "submission.h"

const char *author = "Diogo Fonseca";
const char *STR_RESULTS[13] = {
    "Accepted", "Presentation Error", "Wrong Answer", "Output Limit Exceeded",
    "Memory Limit Exceeded", "Time Limit Exceeded", "Invalid Function", "Runtime Error",
    "Compile Time Error", "Invalid Submission", "Program Size Exceeded", "Requires Reevaluation",
    "Evaluating"};
const char *STR_STATES[2] = {"pending", "final"};
const int DATE_STR_SIZE = 17; // 16 + 1
const char FILE_DELIM[1] = "\t";
const char PRINT_DELIM[1] = ",";
const int MAX_LINE_SIZE = 564; // number is hardcoded in get_subs_from_file()

// Types

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
State str_to_state(const char *s)
{
    for (int i = Pending; i <= Final; i++)
        if (strcmp(s, STR_STATES[i]) == 0)
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

Date *str_to_date(const char *str) // Format: YYYY/MM/DD HH:MM
{
    int y, mo, d, h, m;
    sscanf(str, "%d/%d/%d %d:%d", &y, &mo, &d, &h, &m);
    Date *date = date_cnstrct(y, mo, d, h, m);
    return date;
}

char *date_to_str(char *str_out, Date *d) // Format: YYYY/MM/DD HH:MM
{
    sprintf(str_out, "%d/%d/%d %d:%d", d->year, d->month, d->day, d->hour, d->minute);
    return str_out;
}

char *date_to_str_no_hours(char *str_out, Date *d) // Format: YYYY/MM/DD
{
    sprintf(str_out, "%d/%d/%d", d->year, d->month, d->day);
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

char *sub_to_str(char *str_out, const Submission *sub, const char *delim)
{
    char date_str_buffer[DATE_STR_SIZE];
    date_to_str_no_hours(date_str_buffer, sub->time);
    int i;
    i = sprintf(str_out, "%d%s", sub->number, delim);
    i += sprintf(str_out + i, "%s%s", date_str_buffer, delim);
    i += sprintf(str_out + i, "%d%s", sub->points, delim);
    i += sprintf(str_out + i, "%s%s", sub->group, delim);
    i += sprintf(str_out + i, "%s%s", sub->id, delim);
    i += sprintf(str_out + i, "%s%s", sub->team, delim);
    i += sprintf(str_out + i, "%s%s", sub->problem, delim);
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
    Submission **sub = malloc(sizeof(Submission *));
    char line[MAX_LINE_SIZE]; // 10(int) + 16(time) + 100(group) + 100(id) + 100(name) + 100(problem) + 100(language) + 21(result max) + 7(state max) + 9*1(delimiter '\t') + 1(\n)
    int i = 0;
    while (fscanf(f, "%[^\n]%*c", line) != EOF) // MAX_LINE_SIZE - 1, remove white_space and new_line
    {
        int len = strlen(line);
        if (line[len - 1] == ' ')
            line[len - 1] = '\0'; // removes white space at the end of the string

        sub = realloc(sub, (i + 1) * sizeof(Submission *));
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

void sub_println(const Submission *sub, const char *delim)
{
    char buffer[MAX_LINE_SIZE];
    sub_to_str(buffer, sub, delim);
    printf("%s\n", buffer);
}

void subs_println(const Submission **subs, const char *delim, int size)
{
    for (int i = 0; i < size; i++)
        sub_println(subs[i], delim);
}

Submission **get_accepted_subs(Submission **subs, int size, int *out_size)
{
    int n = 0;
    Submission **accepted = malloc(sizeof(Submission *));
    for (int i = 0; i < size; i++)
    {
        accepted = realloc(accepted, (n + 1) * sizeof(Submission *));
        if (subs[i]->result == Accepted)
            accepted[n++] = subs[i];
    }
    *out_size = n;
    return accepted;
}

// Test functions

void teste_leitura_simples()
{
    char filename[101];
    scanf("%100s", filename);
    FILE *f = fopen(filename, "r");
    fscanf(f, "%*[^\n]%*c");
    int subs_size = 0;
    Submission **submissions = get_subs_from_file(f, &subs_size);
    int accepted_size = 0;
    Submission **accepted = get_accepted_subs(submissions, subs_size, &accepted_size);
    subs_println((const Submission **)accepted, PRINT_DELIM, accepted_size);
    submissions_free(submissions, subs_size);
    free(accepted); // accepted is a subspace of submissions, so it's pointers have already been freed
    fclose(f);
}

void teste_estatisticas()
{
}

void teste_atualizacao()
{
}

void teste_ordenacao()
{
}

void teste_ranking()
{
}

/*
Dúvidas:
    -delimite? ou dar print/fazer só para aquele caso específico do \t?
    -realloc on loop?
    -no white space on last line
    -free on subspace (free(accepted))
    -deep copy no constructor?
*/