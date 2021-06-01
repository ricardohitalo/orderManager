#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAMCONTA 100

// Variavel Global
int indiceMesa = 0;
FILE *pArquivo;

typedef struct Conta{
  char nomePizza[100];
  char descricao[100];
  float valor;
  int codigoMesa;
  int dia, mes, ano;
} contaMesa;

contaMesa conta[TAMCONTA];

typedef struct Pizza{
  char nome[100];
  float preco;
} cardapio;

cardapio pizza[TAMCONTA];

void lerCardapio(char *pNomePizza){
  char contLinha[100];
  char *leitura;
  int contL;
  int verdade = 1;

  pArquivo = fopen("cardapio.txt", "r");
  if (pArquivo == NULL){
    printf("Erro na leitura do arquivo.");
    exit(1);
  } else {
    contL = 1;
    int contPizza = 0;
    // Lê uma Linha (inclusive com o '\n')
    while (!feof(pArquivo)) {
      // o 'fgets' lê até 99 caracteres ou até o '\n'
      leitura = fgets(contLinha, 100, pArquivo);
      // Se foi possível ler
      if (leitura){
        if (((contL % 2) != 0) and (strcmp(pNomePizza, contLinha) == 0)){
          strcpy(pizza[contPizza].nome, contLinha);
          verdade = 0;
        } else if (verdade == 0) {
          pizza[contPizza].preco = strtod(contLinha, NULL);
          printf("\n\nPizza: %s, Preco: %2.f", pizza[contPizza].nome, pizza[contPizza].preco);
          break;
        }
        contPizza++;
      }
      contL++;
    }
    fclose(pArquivo);
  }
}

void cadastrarConta(){
  printf("\n Codigo da mesa:_ ");
  scanf("%d", &conta[indiceMesa].codigoMesa);
  printf("\n Nome da pizza:_ ");
  getchar();
  fgets(conta[indiceMesa].nomePizza, 100, stdin);
  printf("\nDescricao do pedido: ");
  getchar();
  fgets(conta[indiceMesa].descricao, 100, stdin);

  lerCardapio(conta[indiceMesa].nomePizza);

  if (indiceMesa == 0){
    pArquivo = fopen("pedidos.txt", "w");
  } else {
    pArquivo = fopen("pedidos.txt", "a");
  }

  if (pArquivo == NULL) {
    printf("Erro ao salvar arquivo.");
    exit(1);
  } else {
    fprintf(pArquivo, "Pedido: \nPizza-> %s\nDescricao-> %s",
      conta[indiceMesa].nomePizza, conta[indiceMesa].descricao
    );
    fclose(pArquivo);
  }

  //Mudando o indice da mesa
  indiceMesa++;

  printf("\nConta Registrada!\n\n");
}

void pesquisarCodigoDaMesa(){
  int codigoMesa = 0;
  int contador;

  printf("\n\tPesquisa sobre a Mesa\nCodigo da mesa:_ ");
  scanf("%d", &codigoMesa);
  for (contador = 0; contador <= indiceMesa; contador++){
    if (codigoMesa == conta[contador].codigoMesa){
      printf("----\n\tPedido: \nPizza-> %s\nDescricao-> %s----\n\n\n", 
        conta[contador].nomePizza, conta[contador].descricao
      );
      break;
    } else if (contador == indiceMesa) {
      printf("\nO codigo inserido eh invalido.\n\n");
    }
  }
}

void exibirHistoricoDePedidos(){
  char conteudo[100];
  char *leitura;
  int linha = 1;

  pArquivo = fopen("pedidos.txt", "r");
  if (pArquivo == NULL) {
    printf("Erro na leitura do arquivo.");
    exit(1);
  } else {
    // Lê uma Linha (inclusive com o '\n')
    while (!feof(pArquivo)) {
      // o 'fgets' lê até 99 caracteres ou até o '\n'
      leitura = fgets(conteudo, 100, pArquivo);

      // Se foi possível ler
      if (leitura) {
        printf("%d. %s", linha, conteudo);
        linha++;
      }
    }
    fclose(pArquivo);
  }
}

#endif
