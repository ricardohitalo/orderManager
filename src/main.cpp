#include "../include/funcoes.hpp"

int main(){
  int opcao;
  
  //Cadastrar todas as pizzas predefinidas no documento pizzas.txt
  getPizzaSystem();

  printf("\t\t BEM VINDO AO 1TZF00D3\n\n");

  do {
    printf(
      "\t\t+---+-----------------+\n"
      "\t\t| 1 | Novo Pedido     |\n"
      "\t\t+---+-----------------+\n"
      "\t\t| 2 | Mesas           |\n"
      "\t\t+---+-----------------+\n"
      "\t\t| 3 | Fechar Pedido   |\n"
      "\t\t+---+-----------------+\n"
      "\t\t| 4 | Historico       |\n"
      "\t\t+---+-----------------+\n"
      "\t\t| 5 | Cadastrar Pizza |\n"
      "\t\t+---+-----------------+\n"
      "\t\t| 6 | Sair            |\n"
      "\t\t+---+-----------------+\n\n"
    );
    printf("OPÇÃO DESEJADA ==> "); scanf("%d", &opcao);

    switch (opcao) {
      case 1:
        cadastrarConta();
        break;
      case 2:
        pesquisarCodigoDaMesa();
        break;
      case 3:
        finalizarPedido();
        break;
      case 4:
        exibirHistoricoDePedidos();
        break;
      case 5:
        cadastrarPizza();
        break;
      case 6:
        printf("\n... | Bye bye |...\n");
        break;
      default:
        printf("Opcao invalida, digite novamente.");
        break;
    }
  } while (opcao != 6);
  return(0);
}