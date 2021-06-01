#include "../include/funcoes.h"

int main(){
  int opcao;

  printf("\t\tBem vindos ao IfoodItz\n\n");

  do {
    printf(
      "| 1 | Cadastrar conta \n"
      "| 2 | Pesquisa por Mesa \n"
      "| 3 | Historico de Pedidos \n"
      "| 4 | Sair \n\n"
    );
    printf("OP:_ "); scanf("%d", &opcao);

    switch (opcao) {
      case 1:
        cadastrarConta(); 
        break;
      case 2:
        pesquisarCodigoDaMesa();
        break;
      case 3:
        exibirHistoricoDePedidos();
        break;
      case 4:
        printf("\n... | Bye bye |...\n");
        break;
      default:
        printf("Opcao invalida, digite novamente.");
        break;
    }
  } while (opcao != 4);
  return(0);
}