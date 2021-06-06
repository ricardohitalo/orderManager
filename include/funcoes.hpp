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
int numPizzaCad = 0;
int totalMesas = 0;

typedef struct Conta{
  int codigoMesa;
  int status;
  float valor;
  char data[100];
  struct Pizza *pizza;
} contaMesa;

contaMesa mesa[TAMCONTA];

typedef struct Pizza{
  char nome[100];
  float preco;
} cardapio;

cardapio pizza[TAMCONTA];

void cadastrarConta(){
  if (numPizzaCad != 0){
    int pizzaOpcao; 
    time_t tempo = time(0); // data / hora atual com base no sistema atual
    char *data = ctime(&tempo); // converter a variavel now para a forma de string
    strcpy(mesa[indiceMesa].data, data); // setar data na conta

    printf("\nCÓDIGO DA MESA: ");
    scanf("%d", &indiceMesa);
    if (mesa[indiceMesa].status == 1){
      printf("\nA mesa (%d) está em uso! Favor selecionar uma mesa vazia.\n", indiceMesa);
    } else {
      mesa[indiceMesa].codigoMesa = indiceMesa;

      printf("\n-----PIZZAS DO CARDAPIO-----\n");
      for (int i = 1; i <= numPizzaCad; i++){
        printf("\n(%d) - %s | R$: %.2f\n", i, pizza[i].nome, pizza[i].preco);
      }

      printf("\nSelecione a Pizza pelo código correspondente:\n~> ");
      getchar();
      scanf("%d", &pizzaOpcao);
      if (pizzaOpcao > numPizzaCad){
        printf("\nNão foi possível identificar o código da pizza.\n");
      } else {
        mesa[indiceMesa].status = 1;
        mesa[indiceMesa].pizza = &pizza[pizzaOpcao];
        mesa[indiceMesa].valor += pizza[pizzaOpcao].preco;
        strcpy(mesa[indiceMesa].data, data);
        totalMesas++;

        printf("\nPedido Registrado!\n\n");
      }
    }
  } else {
    printf("\nALERTA! Nenhuma pizza cadastrada no sistema.\n");
  }
}

void finalizarPedido(){
  int pos = 0;

  printf("\nMesas ocupadas:\n");
  for (int i = 0; i <= TOTALMESA; i++){
    if (mesa[i].status == 1) {
      printf(" ->(%d)", mesa[i].codigoMesa);
    }
  }

  printf("\n\nFinalizar pedido da mesa: ");
  scanf("%d", &pos);
  mesa[pos].status = -1;

  printf(
    "\n========================================================\n\n"
    "\t\t+---+---------------------+\n"
    "\t\t|      Finalização      |\n"
    "\t\t+---+---------------------+\n"
    "\t\t| PIZZA |-> %s"
    "\t\t+---+---------------------+\n"
    "\t\t| Total |-> %.2f\n"
    "\t\t+---+---------------------+\n\n"
    "========================================================\n\n",
    mesa[pos].pizza->nome, mesa[pos].valor
  );

  pArquivo = fopen("pedidos.txt", "a+");
  if (pArquivo == NULL) {
    printf("Erro ao salvar arquivo.");
    exit(1);
  } else {
    fprintf(pArquivo, "-------\nPedido ~ %s\nMesa-> %d\nPizza-> %sPreco-> %.2f\nStatus-> %d\n-------",
      mesa[pos].data, mesa[pos].codigoMesa, mesa[pos].pizza->nome,
      mesa[pos].pizza->preco, mesa[pos].status);
    fclose(pArquivo);
  }
}

void cadastrarPizza(){
  int opcao = 0;

  printf("\nCADASTRO DE PIZZA\nPara Prosseguir digite 1, para Sair digite 0: ");
  scanf("%d", &opcao);
  while (opcao == 1){
    printf("\nDigite o sabor da pizza: ");
    getchar();
    fgets(pizza[numPizzaCad + 1].nome, 100, stdin);
    printf("\nDigite o valor da pizza: ");
    scanf("%f", &pizza[numPizzaCad + 1].preco);
    numPizzaCad++;

    pArquivo = fopen("pizzas.txt", "a+");
    if (pArquivo == NULL){
      printf("Erro ao salvar arquivo.");
      exit(1);
    } else {
      fprintf(pArquivo, "%s", pizza[numPizzaCad].nome);
      fprintf(pArquivo, "%.2f\n", pizza[numPizzaCad].preco);
      fclose(pArquivo);
    }

    printf("\nPara continuar adicionando digite 1, para Sair digite 0: ");
    scanf("%d", &opcao);
  }
  printf("\nCADASTRO DE PIZZA FINALIZADO\n");
}

void pesquisarCodigoDaMesa(){
  int codigoMesa = 0;

  printf("\n****Pesquisa sobre a Mesa****\nCodigo da mesa: ");
  scanf("%d", &codigoMesa);
  if ((codigoMesa >= 1) and (codigoMesa < TOTALMESA)) {
    for (int contador = 0; contador <= indiceMesa; contador++){
      if (codigoMesa == mesa[contador].codigoMesa){
        printf("-------\nPedido ~ %s\nMesa-> %d\nPizza-> %sPreco-> %.2f\nStatus-> %d\n-------",
          mesa[contador].data, mesa[contador].codigoMesa, mesa[contador].pizza->nome,
          mesa[contador].pizza->preco, mesa[contador].status
        );
      }
    }
  } else {
    printf("\nO codigo inserido eh invalido.\n\n");
  }
}

void exibirHistoricoDePedidos() {
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

void getPizzaSystem(){
  char contLinha[100];
  char *leitura;
  int contL;

  pArquivo = fopen("pizzas.txt", "r");
  if (pArquivo == NULL) {
    printf("Erro na leitura do arquivo.");
    exit(1);
  } else {
    contL = 1;
    int contPizza = 1;
    // Lê uma Linha (inclusive com o '\n')
    while (!feof(pArquivo)) {
      // o 'fgets' lê até 99 caracteres ou até o '\n'
      leitura = fgets(contLinha, 100, pArquivo);
      // Se foi possível ler
      if (leitura) {
        if ((contL % 2) != 0) {
          strcpy(pizza[contPizza].nome, contLinha);
        } else {
          pizza[contPizza].preco = strtod(contLinha, NULL);
          contPizza++;
          numPizzaCad++;
        }
      }
      contL++;
    }
    fclose(pArquivo);
  }
}

#endif
