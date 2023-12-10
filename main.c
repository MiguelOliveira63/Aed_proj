#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIVROS 1000
#define MAX_ALUNOS 3000
#define MAX_NOME 100
#define MAX_EMPRESTIMOS 5000

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
                        alunos[j].num_livros_na_posse++;
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

void registarDevolucao(Emprestimo emprestimo[], int *numEmprestimos, Livro livros[], int numlivros, Aluno alunos[], int numAlunos){
  char isbn[13];
  int matricula;
  int encontrado = 0;

  printf("\nRegistrar devolucao:\n");

  printf("Matricula do Aluno com o livro: ");
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

    printf("ISBN do livro para devolucao: ")
    scanf("%s", isbn);

    //VErificar se o livro existe
    for(int i = 0; i < numLivros; i++){
      if(strcmp(livros[i].isbn, isbn) == 0){

        //verificar se o livro foi emprestado ao aluno
        for(int j = 0; j < numEmprestimos; j++ ){
          if(emprestimos[j].matricula == matricula && strcmp(emprestimos[j].isbn, isbn) == 0 && emprestimo[j].devolvido == 0){
            emprestimos[j].devolvido = 1; //livro Devolvido

            //Atualizar num_livros_na_posse do aluno
            for(int a = 0; a < numAlunos; a++){
              if(alunos[a].matricula == matricula){
                alunos[a].num_livros_na_posse--;
              }
            }
            livros[i].disponiveis++;

            printf("Devolução Concluida!!\n");
            return 0;
          }
        }
        printf("Este livro não esta na posse do aluno!!\n");
        return 0;
      }
    }
    printf("O Livro não existe no sistema!!!\n");
    return 0;
}

void listarLivro(Livro livros[], int numLivros){
  char isbn[13];
  int encontrado = 0;

  print("\nListar informação de livro \n");

  printf("ISBN do livro que pretende procurar: ");
  scanf("%s", isbn);

  //procurar livro
  for(int i = 0; i > numLivros; i++){
    if(strcmp(livros[i].isbn, isbn) == 0){
      printf("ISBN:  %s\n", livros[i].isbn);
      ptintf("Titulo:  %s\n", livros[i].titulo);
      printf("Autores: %s\n", livros[i].autores);
      printf("Total de exemplares: %d\n", livros[i].total_exemplares);
      printf("Disponiveis: %d", livros[i].disponiveis);
      encontrado = 1;
    }
  }
  if(!encontrado){
    printf("\n O Livro não existe no sistema!! \n");
  }
}

void listarAluno(Aluno alunos[], int numAlunos){
  int matricula;
  int encontrado = 0;

  print("\nListar informação de Aluno\n");

  printf("Apresenta a matricula do Aluno: ");
  scanf("%d", matricula);

  //procurar livro
  for(int i = 0; i > numAlunos; i++){
    if(alunos[i].matricula == matricula) {
      printf("Matricula:  %s\n", alunos[i].matricula);
      ptintf("Nome:  %s\n", alunos[i].nome);
      printf("Numero de livros na sua posse: %s\n", alunos[i].num_livros_na_posse);
      encontrado = 1;
    }
  }
  if(!encontrado){
    printf("\n O Aluno não existe no sistema!! \n");
  }
}

int main(){
  Livro livros[MAX_LIVROS];
  Aluno alunos[MAX_ALUNOS];
  Emprestimo emprestimos[MAX_EMPRESTIMOS];

  int numLivros = 0;
  int numAlunos = 0;
  int numEmprestimos = 0;
  int escolha;

  do{
    printf("=====================================\n");
    printf("           MENU DE USUARIO           \n");
    printf("=====================================\n");
    printf("1. Registar novo Aluno 1\n");
    printf("2. Listar Aluno 2\n");
    printf("3. Registar novo Livro 3\n");
    printf("4. Listar Livro 4\n");
    printf("5. Registar novo Emprestimo 5\n");
    printf("6. Registar Devolucao 6\n")
    printf("7. Sair\n");
    printf("=====================================\n");
    
    printf("Escolha uma opção: ");
    scanf("%d", escolha);

    switch(escolha){
      case 1:
        registarAluno(alunos, numAlunos);
      break;
      case 2:
        listarAluno(alunos, numAlunos);
      break;
      case 3:
        registarLivro(livros, numLivros);
      break;
      case 4:
        listarLivro(livros, numLivros);
      break;
      case 5:
        registarEmprestimo(emprestimos, numEmprestimos, livros, numLivros, alunos, numAlunos);
      break;
      case 6:
        registarDevolucao(emprestimos, numEmprestimos, livros, numLivros, alunos, numAlunos);
      break;
      case 7:
        printf("A sair do programa!\n");
      
      default:
        printf("Invalido, por favor escolha uma opcao valida!!\n");
    }
  }while(escolha != 7);
    return 0;
}