// este operador serve para dizer ao compilador de C, que este ficheiro header so deve ser processado
// se ainda nao sido processado anteriormente
// le-se "se ainda nao tiver sido definido MONSTRO_H, define MONSTRO_H".
// Se o teste falhar (i.e. o MONSTRO_H ja foi definido), o compilador salta para o #endif e tudo o que esta
// dentro do #if e ignorado
#ifndef MONSTRO_H
#define MONSTRO_H

// Definicao do enumerado Tamanho
typedef enum e_Tam
{
    Tiny,
    Small,
    Medium,
    Large,
    Huge,
    Gargantuan
} Tamanho;

// Dada uma string, retorna o tamanho (valor enumerado) correspondente a string recebida
Tamanho string_to_tamanho(char *s);

// Dada um tamanho, retorna uma String que descreve o tamanho
const char *tamanho_to_string(Tamanho t);

// Define o Tipo Estruturado Monstro, e os seus membros
// para os mais distraidos, existe um membro novo
typedef struct S_Monstro
{
    char *nome;
    char *tipo;
    Tamanho tam;
    int ac;
    int hp;
    double cr;
    // string que representa uma habilidade especial da criatura
    char *trait;
} Monstro;

// Construtor do tipo Monstro, recebe os membros, e cria um novo monstro, e inicializa-o. Devolve
// um ponteiro para o monstro criado
Monstro *monstro(char *nome, char *tipo, Tamanho tam, int ac, int hp, double cr, char *trait);

// Recebe um ponteiro para um monstro, e liberta a memória usada pelo tipo
void free_monstro(Monstro *m);

// Recebe um ponteiro para um monstro, e cria uma copia (ou clone) profunda do monstro. Devolve um
// ponteiro para o monstro criado
Monstro *monstro_dup(Monstro *m);

// Recebe um ponteiro para um monstro, e atualiza algum dos seus membros com os valores recebidos
void atualiza_stats(Monstro *m, int ac, int hp, double cr);

// Imprime um monstro para o Standard Output, usando o seguinte formato:
//<Nome do Monstro> - <Tamanho> <Tipo Criatura>, AC:<Armor Class>, HP:<Hit Points>, CR: <Challenge Rating>, Trait: <trait>\n
// por exemplo:
// Imp – Tiny Fiend, AC:13, HP:10, CR:1.00, Trait:Shapechanger\n
void println_monstro(Monstro *m);

// Recebe um array de ponteiros para monstros, e o numero de elementos no array n, e imprime
// todos os monstros, pela ordem em que aparecem no array. Caso nao existam elementos no array
// imprime "None\n"
void println_monstros(Monstro *monstros[], int n);

// Dado um array de ponteiros para monstros, e um numero n de monstros a ler, le do standard input os n monstros.
// cada monstro deve ser lido numa unica linha, com todos os membros separados por espaco, pela seguinte ordem
//<Nome do Monstro> <Tipo Criatura> <Tamanho> <Armor Class> <Hit Points> <Challenge Rating> <Trait>.
// Os membros que correspondem a cadeias de caracteres (strings) nao excederao os 100 caracteres cada.
// O metodo retorna o numero de monstros efetivamente lidos.
int get_monstros(Monstro *monstros[], int n);

// Dado um array de ponteiros para monstros, um numero n de monstros, uma string com o nome,
// esta funcao procura no array monstros pelo primeiro monstro com nome igual ao nome recebido,
//  e retorna o ponteiro para esse monstro.
// Caso nao exista tal monstro, retorna-se o ponteiro NULL
Monstro *pesquisa_monstro(Monstro *monstros[], int n, char *nome);

// Dado um array de ponteiros para monstros, um numero n de monstros nesse array, retorna o monstro
// com maior numero de hit points. Caso nao exista nenhum monstro, retorna-se NULL
Monstro *pesquisa_monstro_mais_duro(Monstro *monstros[], int n);

// dado um array de entrada de ponteiros de monstros in, e um array de saida de ponteiros de monstros out,
// um inteiro n que corresponde ao numero de elementos de in, e uma string com um nome de um tipo de monstro
// esta funcao procura no array in todos os monstros com o tipo recebido, colocando-os no
// array de saida out. A funcao retorna o numero de elementos encontrados e guardados em out.
int pesquisa_monstros_tipo(Monstro *in[], Monstro *out[], int n, char *tipo);

// dado um array de entrada de ponteiros de monstros in, um array de saida de ponteiros de monstros out,
// um inteiro n que corresponde ao numero de elementos de in, e dois inteiros que correspondem
// a um numero minimo e maximo do challenge rating, esta funcao procura no array in todos
// os monstros com challenge rating compreendido entre os valores minimo e maximo (inclusive),
// colocando-os no array de saida out. A funcao retorna o numero de elementos encontrados e guardados em out.
int pesquisa_monstros_cr(Monstro *in[], Monstro *out[], int n, double cr_min, double cr_max);

// Coloquem aqui a funcao de teste que usaram para testar o problema F da Semana 2.
// Ou seja, "A funcao começa por ler um inteiro n representando o numero de monstros que vao ser lidos..."
// etc etc.
void test_F_S2(void);

#endif