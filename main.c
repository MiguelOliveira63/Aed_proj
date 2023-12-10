#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void registarAluno(Aluno alunos[], int *numAlunos){
  if(*numAlunos < 3000){
      printf("\nRegistrar novo aluno:\n");
      printf("Matrícula: ");
        scanf("%d", &alunos[*numAlunos].matricula);
      printf("Nome: ");
        scanf("%s", alunos[*numAlunos].nome);
      printf("Curso: ");
        scanf("%s", aluno[*numAlunos].curso);

      alunos[*numAlunos].livros_na_posse = 0;
      (*numAlunos)++;
      ptintf("Novo Aluno Registado!! \n")
  }else {
        printf("Limite de alunos atingido!!!\n");
    }
}

void registarLivro(Livro livros[], int *numLivros){
  if(*numLivros < 1000){
      printf("\nRegistrar novo Livro:\n");
      printf("ISBN: ");
        scanf("%s", livros[*numLivros].isbn);
      printf("Titulo: ");
        scanf("%s", livros[*numLivros].titulo);
      printf("Autores: ");
        scanf("%s", livros[*numLivros].autores);
      printf("Numero de exemplares: ");
        scanf("%d", &livros[*numLivros].total_exemplares);
      printf("Número de exemplares disponíveis para empréstimo: ");
        scanf("%d", &livros[*numLivros].exemplares_disponiveis);
        (*numLivros)++;
      printf("Livro registrado com sucesso!!\n");
  }else {
        printf("Limite de Livros atingido!!!\n");
    }
}

void registarEmprestimo(Emprestimo emprestimos[], int *numEmprestimos, Livro livros[], int numLivros[], Aluno alunos[], int numAlunos){
  char isbn[13];
  int matricula;
  int encontrado = 0;

  printf("\nRegistrar novo empréstimo:\n");

  printf("Matricula do Aluno: ");
  scanf("%d", &matricula);

    //loop para verificar se o aluno existe no sistema
    for (int i = 0; i < numAlunos; i++) {
        if (alunos[i].matricula == matricula) {
            encontrado = 1;
        }
    }

    if (!encontrado){
      printf("O Aluno não existe!\n");
      return 0;
    }

    printf("ISBN do Livro para emprestimo: ");
    scanf("%s", isbn);

    //loop para verificar de o Livro existe no sistema
    for(int i = 0; i < numLivros; i++){
      if (strcmp(livros[i].isbn, isbn) == 0) {
            // Verifica se há exemplares disponíveis
            if (livros[i].exemplares_disponiveis > 0) {

                // Atribui o valor da matricula do aluno ao emprestimo, atribui o valor armazenado em isbn para o isbn de emprestimo, e da inicio a devolvivo como NAO DEVOLVIDO (0). 
                emprestimos[*numEmprestimos].matricula = matricula;
                strcpy(emprestimos[*numEmprestimos].isbn, isbn);
                emprestimos[*numEmprestimos].devolvido = 0; // Inicializa como não devolvido
                
                // Atualiza o numero de livros na posse do aluno e o nnumero de exemplares emprestados
                for (int j = 0; j < numAlunos; j++) {
                    if (alunos[j].matricula == matricula) {
                        alunos[j].livros_na_posse++;
                    }
                }
                livros[i].exemplares_disponiveis--;

                // numTotal de emprestimos
                (*numEmprestimos)++; 
                printf("Empréstimo registrado com sucesso.\n");
            } else {
                printf("Não há exemplares disponíveis para empréstimo deste livro.\n");
            }
            return;
        }
    }

    // Se o livro não for encontrado, exibe uma mensagem
    printf("O Livro Não existe no sistema.\n");
}


    




