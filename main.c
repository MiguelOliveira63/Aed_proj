#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIVROS 1000
#define MAX_ALUNOS 3000
#define MAX_NOME 100
#define MAX_EMPRESTIMOS 5000


//livros (ISBN (codigo de 13 digitos ex: 978-15-333-0227-3), _tulo, autores, número total de exemplares, e número de exemplares disponíveis para empréstimo)
typedef struct livro{
    char isbn[18];
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
  char isbn[18];
  int matricula;
  int devolvido;
} Emprestimo;

void registarAluno(Aluno alunos[], int *numAlunos) {
    if (*numAlunos < MAX_ALUNOS) {
        printf("\nRegistrar novo aluno:\n");
        printf("Matrícula: ");
        scanf("%d", &alunos[*numAlunos].matricula);

        printf("Nome: ");
        scanf(" %[^\n]", alunos[*numAlunos].nome);

        printf("Curso: ");
        scanf(" %[^\n]", alunos[*numAlunos].curso);

        alunos[*numAlunos].num_livros_na_posse = 0;
        (*numAlunos)++;
        printf("Novo Aluno Registrado!! \n");
    } else {
        printf("Limite de alunos atingido!!!\n");
    }
}

void registarLivro(Livro livros[], int *numLivros){
    if (*numLivros < MAX_LIVROS) {
        printf("\nRegistrar novo Livro:\n");
        printf("ISBN: ");
        scanf("%18s", livros[*numLivros].isbn);

        printf("Titulo: ");
        scanf(" %[^\n]", livros[*numLivros].titulo);

        printf("Autores: ");
        scanf(" %[^\n]", livros[*numLivros].autores);
        
        printf("Numero de exemplares: ");
        scanf("%d", &livros[*numLivros].total_exemplares);

        printf("Número de exemplares disponíveis para empréstimo: ");
        scanf("%d", &livros[*numLivros].disponiveis);
        (*numLivros)++;
        printf("Livro registrado com sucesso!!\n");
    } else {
        printf("Limite de Livros atingido!!!\n");
    }
}

int compararISBN(char isbn1[], char isbn2[]) {
    return strcmp(isbn1, isbn2);
}
void registarEmprestimo(Emprestimo emprestimos[], int *numEmprestimos, Livro livros[], int numLivros, Aluno alunos[], int numAlunos){
  char isbn[18];
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
      return;
    }

    printf("ISBN do livro para emprestimo: ");
    scanf(" %17s", isbn); 
    

    //loop para verificar de o Livro existe no sistema
    for(int i = 0; i < numLivros; i++){
      if (compararISBN(livros[i].isbn, isbn) == 0) {
            if (livros[i].disponiveis > 0) {  //Há exemplares disponiveis?? 

                emprestimos[*numEmprestimos].matricula = matricula;
                for (int j = 0; j < 13; j++) {
                    emprestimos[*numEmprestimos].isbn[j] = isbn[j] - '0';
                }
                emprestimos[*numEmprestimos].devolvido = 0;
                // Atualiza o numero de livros na posse do aluno e o numero de exemplares emprestados
                for (int j = 0; j < numAlunos; j++) {
                    if (alunos[j].matricula == matricula) {
                        alunos[j].num_livros_na_posse++;
                    }
                }
                livros[i].disponiveis--;

                // numTotal de emprestimos
                (*numEmprestimos)++;
                printf("Empréstimo registrado com sucesso.\n");
            } else {
                printf("Não há exemplares disponíveis para empréstimo deste livro.\n");
            }
            return;
        }
    }

    // O livro não foi econtrado
    printf("O Livro Não existe no sistema.\n");
}

void registarDevolucao(Emprestimo emprestimos[], int *numEmprestimos, Livro livros[], int numLivros, Aluno alunos[], int numAlunos){
  char isbn[18];
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
      return;
    }

    printf("ISBN do livro para emprestimo: ");
    scanf(" %17s", isbn); 

    //o livro existe ??
    for(int i = 0; i < numLivros; i++){
      if(compararISBN(livros[i].isbn, isbn) == 0){

         //o livro foi emprestado ao aluno??
        for (int j = 0; j < *numEmprestimos; j++) {
            if (compararISBN(emprestimos[j].isbn, isbn) && emprestimos[j].matricula == matricula && emprestimos[j].devolvido == 0) {
                emprestimos[j].devolvido = 1; //livro Devolvido
        
                //atualizar num_livros_na_posse
                for (int a = 0; a < numAlunos; a++) {
                    if (alunos[a].matricula == matricula) {
                        alunos[a].num_livros_na_posse--;
                        break; // sem necessidade de procurar mais
                    }
                }
                livros[i].disponiveis++;
        
                printf("Devolução Concluida!!\n");
                return;
            }
}
printf("Este livro não está na posse do aluno!!\n");
return;
        }
    }
    printf("O Livro não existe no sistema!!!\n");
    return;
}

void listarLivro(Livro livros[], int numLivros){
  char isbn[18];
  int encontrado = 0;

  printf("\nListar informação de um livro \n");

  printf("ISBN do livro que pretende procurar: ");
    scanf(" %17s", isbn);  

  //procurar livro
  for(int i = 0; i < numLivros; i++){
    if(strcmp(livros[i].isbn, isbn) == 0){
      printf("ISBN:  %s\n", livros[i].isbn);
      printf("Titulo:  %s\n", livros[i].titulo);
      printf("Autores: %s\n", livros[i].autores);
      printf("Total de exemplares: %d\n", livros[i].total_exemplares);
      printf("Disponiveis: %d\n", livros[i].disponiveis);
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

  printf("\nListar informação de Aluno\n");

  printf("Apresenta a matricula do Aluno: ");
  scanf("%d", &matricula);

  //procurar aluno
  for(int i = 0; i < numAlunos; i++){
    if(alunos[i].matricula == matricula) {
      printf("Matricula:  %d\n", alunos[i].matricula);
      printf("Nome:  %s\n", alunos[i].nome);
      printf("Numero de livros na sua posse: %d\n", alunos[i].num_livros_na_posse);
      encontrado = 1;
    }
  }
  if(!encontrado){
    printf("\n O Aluno não existe no sistema!! \n");
  }
}


void listarTodosLivros(Livro livros[], int numLivros) {
    printf("\nLista de todos os livros:\n");

    if (numLivros == 0) {
        printf("Nenhum livro registado ainda.\n");
        return;
    }

    printf("%-18s %-20s %-20s %-6s %-6s\n", "ISBN", "Título", "Autores", "Total", "Disp.");

    for (int i = 0; i < numLivros; i++) {
        printf("%-18s %-20s %-20s %-6d %-6d\n",
               livros[i].isbn, livros[i].titulo, livros[i].autores,
               livros[i].total_exemplares, livros[i].disponiveis);
    }
}


void listarTodosAlunos(Aluno alunos[], int numAlunos) {
    printf("\nLista de todos os alunos:\n");

    if (numAlunos == 0) {
        printf("Nenhum aluno registado ainda.\n");
        return;
    }

    printf("%-10s %-20s %-20s %-5s\n", "Matrícula", "Nome", "Curso", "Livros");

    for (int i = 0; i < numAlunos; i++) {
        printf("%-10d %-20s %-20s %-5d\n",
               alunos[i].matricula, alunos[i].nome, alunos[i].curso, alunos[i].num_livros_na_posse);
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
    printf("1. Registar novo Aluno .1\n");
    printf("2. Pesquisar Aluno .2\n");
    printf("3. Listar Todos os Aluno .3\n");
    printf("4. Registar novo Livro .4\n");
    printf("5. Pesquisar Livro .5\n");
    printf("6. Listar Todos os Livro .6\n");
    printf("7. Registar novo Emprestimo .7\n");
    printf("8. Registar Devolucao .8\n");
    printf("0. Sair .0\n");
    printf("=====================================\n");
    
    printf("Por favor escolha uma opcao\n");
    scanf("%d", &escolha);

    switch(escolha){
      case 1:
        registarAluno(alunos, &numAlunos);
      break;
      case 2:
        listarAluno(alunos, numAlunos);
      break;
      case 3: 
        listarTodosAlunos(alunos, numAlunos);
      break;
      case 4:
        registarLivro(livros, &numLivros);
      break;
      case 5:
        listarLivro(livros, numLivros);
      break;
      case 6: 
        listarTodosLivros(livros, numLivros);
      break;
      case 7:
        registarEmprestimo(emprestimos, &numEmprestimos, livros, numLivros, alunos, numAlunos);
      break;
      case 8:
        registarDevolucao(emprestimos, &numEmprestimos, livros, numLivros, alunos, numAlunos);
      break;
      case 0:
        printf("A sair do programa!\n");
      break;
      
      default:
        printf("Invalido, por favor escolha uma opcao valida!!\n");
    }
  }while(escolha != 0);
    return 0;
}