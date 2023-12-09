#include <stdio.h>
#include <stdlib.h>

#define MAX_LIVROS 1000
#define MAX_ALUNOS 3000
#define MAX_NOME 100

//livros (ISBN (codigo de 13 digitos ex: 978-15-333-0227-3), _tulo, autores, número total de exemplares, e número de exemplares disponíveis para empréstimo)
typedef struct livro{
    char isbn[13];
    char titulo[MAX_NOME];
    char autores[MAX_NOME];
    int total_exemplares;
    int disponiveis;
} Livro;


//alunos (número de matrícula, nome, curso, e número de livros na sua posse)
typedef struct aluno{
    char nome[MAX_NOME];
    char curso[MAX_NOME];
    int matricula;
    int num_livros_na_posse;
} Aluno;

//empréstimos, que são caraterizados pelo ISBN do livro, o número de matrícula do aluno e uma variável booleana “devolvido” (verdadeiro se o aluno já devolveu o livro (1), falso caso contrário (0) )

typedef struct emprestimo{
  char isbn[13];
  int matricula;
  int devolvido;
} Emprestimo;
