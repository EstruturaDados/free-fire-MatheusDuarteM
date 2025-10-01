#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. Criação da struct: definindo a struct Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Definindo a mochila como um array de Itens e um contador
#define TAMANHO_MOCHILA 10
Item mochila[TAMANHO_MOCHILA];
int numeroDeItens = 0; // Controla a quantidade de itens na mochila

// Protótipos das funções
void cadastrarItem();
void removerItem();
void listarItens();
void buscarItem();

int main() {
    int opcao;

    do {
        printf("\n--- SISTEMA DE MOCHILA DE LOOT ---\n");
        printf("1. Cadastrar novo item\n");
        printf("2. Remover um item\n");
        printf("3. Listar todos os itens\n");
        printf("4. Buscar um item\n");
        printf("0. Sair do programa\n");
        printf("-----------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer de entrada para evitar problemas com fgets

        switch (opcao) {
            case 1:
                cadastrarItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("Saindo do sistema de inventario...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

// 2. Cadastro de itens: permite que o jogador cadastre até 10 itens
void cadastrarItem() {
    if (numeroDeItens >= TAMANHO_MOCHILA) {
        printf("\nERRO: A mochila esta cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    printf("\n-- Cadastro de Novo Item --\n");
    Item novoItem;

    printf("Digite o nome do item: ");
    fgets(novoItem.nome, 30, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = 0; // Remove a quebra de linha

    printf("Digite o tipo do item (ex: arma, municao, cura): ");
    fgets(novoItem.tipo, 20, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = 0; // Remove a quebra de linha

    printf("Digite a quantidade: ");
    scanf("%d", &novoItem.quantidade);
    getchar(); // Limpa o buffer

    mochila[numeroDeItens] = novoItem;
    numeroDeItens++;

    printf("\nItem '%s' cadastrado com sucesso!\n", novoItem.nome);
    
    // 4. Listagem dos itens registrados com seus dados (após cada operação)
    listarItens();
}

// 3. Remoção de itens: permitir que o jogador exclua um item da mochila
void removerItem() {
    if (numeroDeItens == 0) {
        printf("\nA mochila esta vazia. Nao ha itens para remover.\n");
        return;
    }

    char nomeParaRemover[30];
    printf("\nDigite o nome do item que deseja remover: ");
    fgets(nomeParaRemover, 30, stdin);
    nomeParaRemover[strcspn(nomeParaRemover, "\n")] = 0;

    int indiceEncontrado = -1;
    for (int i = 0; i < numeroDeItens; i++) {
        if (strcmp(mochila[i].nome, nomeParaRemover) == 0) {
            indiceEncontrado = i;
            break;
        }
    }

    if (indiceEncontrado == -1) {
        printf("\nERRO: Item '%s' nao encontrado na mochila.\n", nomeParaRemover);
    } else {
        // Move todos os itens a partir do índice encontrado uma posição para trás
        for (int i = indiceEncontrado; i < numeroDeItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        numeroDeItens--;
        printf("\nItem '%s' removido com sucesso!\n", nomeParaRemover);
        
        // 4. Listagem dos itens registrados com seus dados (após cada operação)
        listarItens();
    }
}

// 4. Listagem dos itens registrados com seus dados
void listarItens() {
    printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", numeroDeItens, TAMANHO_MOCHILA);
    if (numeroDeItens == 0) {
        printf("A mochila esta vazia.\n");
    } else {
        for (int i = 0; i < numeroDeItens; i++) {
            printf("Item %d:\n", i + 1);
            printf("  Nome: %s\n", mochila[i].nome);
            printf("  Tipo: %s\n", mochila[i].tipo);
            printf("  Quantidade: %d\n", mochila[i].quantidade);
            printf("-----------------------------------\n");
        }
    }
}

// 5. Busca sequencial: localizar um item na mochila com base no nome
void buscarItem() {
    if (numeroDeItens == 0) {
        printf("\nA mochila esta vazia. Nao ha itens para buscar.\n");
        return;
    }
    
    char nomeParaBuscar[30];
    printf("\nDigite o nome do item que deseja buscar: ");
    fgets(nomeParaBuscar, 30, stdin);
    nomeParaBuscar[strcspn(nomeParaBuscar, "\n")] = 0;

    int encontrado = 0;
    for (int i = 0; i < numeroDeItens; i++) {
        if (strcmp(mochila[i].nome, nomeParaBuscar) == 0) {
            printf("\n--- Item Encontrado! ---\n");
            printf("  Nome: %s\n", mochila[i].nome);
            printf("  Tipo: %s\n", mochila[i].tipo);
            printf("  Quantidade: %d\n", mochila[i].quantidade);
            printf("--------------------------\n");
            encontrado = 1;
            break; // Para a busca assim que o primeiro item com o nome for encontrado
        }
    }

    if (!encontrado) {
        printf("\nItem '%s' nao foi encontrado na mochila.\n", nomeParaBuscar);
    }
}
