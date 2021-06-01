#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctime>

#define TAMCONTA 100
#define TOTALMESA 20

// Variavel Global
int indiceMesa = 0;
FILE *pArquivo;

typedef struct Conta{
  int codigoMesa;
  float valor;
  char nomePizza[100];
  char descricao[100];
  char data[100];
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
  // data / hora atual com base no sistema atual
  time_t tempo = time(0);
  // converter a variavel now para a forma de string
  char* data = ctime(&tempo);
  // setar data na conta
  strcpy(conta[indiceMesa].data, data);

  printf("\n_Codigo da mesa: ");
  scanf("%d", &conta[indiceMesa].codigoMesa);
  printf("_Pizza e Tamanho (ex: calabresa g):\n_ ");
  getchar();
  fgets(conta[indiceMesa].nomePizza, 100, stdin);
  printf("_Descricao: ");
  fgets(conta[indiceMesa].descricao, 100, stdin);

  // Verificar pizza e registrar na conta.
  lerCardapio(conta[indiceMesa].nomePizza);
  conta[indiceMesa].valor = pizza[1].preco;

  pArquivo = fopen("pedidos.txt", "a+");
  if (pArquivo == NULL) {
    printf("Erro ao salvar arquivo.");
    exit(1);
  } else {
    fprintf(pArquivo, "-------\nPedido ~ %sMesa-> %d\nPizza-> %sPreco-> %2.f\nDescricao-> %s-------",
      conta[indiceMesa].data, conta[indiceMesa].codigoMesa, conta[indiceMesa].nomePizza, 
      conta[indiceMesa].valor, conta[indiceMesa].descricao
    );
    fclose(pArquivo);
  }

  //Mudando o indice da mesa
  indiceMesa++;

  printf("\nConta Registrada!\n\n");
}

void pesquisarCodigoDaMesa(){
  int codigoMesa = 1;
  int contador;
  
  printf("\n\tPesquisa sobre a Mesa\nCodigo da mesa:_ ");
  scanf("%d", &codigoMesa);
  if ((codigoMesa >= 1) and (codigoMesa < TOTALMESA)) {
    for (contador = 0; contador <= indiceMesa; contador++){
      if (codigoMesa == conta[contador].codigoMesa){
        printf("-------\nPedido ~ %sMesa-> %d\nPizza-> %sPreco-> %2.f\nDescricao-> %s-------\n",
          conta[contador].data, conta[contador].codigoMesa, conta[contador].nomePizza, 
          conta[contador].valor, conta[contador].descricao
        );
      }
    }
  } else {
    printf("\nO codigo inserido eh invalido.\n\n");
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
    printf("\n\n");
    fclose(pArquivo);
  }
}

#endif
