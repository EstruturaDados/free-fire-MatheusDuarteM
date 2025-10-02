#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- ESTRUTURA E VARIÁVEIS GLOBAIS ---

// Definindo a struct do Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Definindo a mochila como um array (vetor) de Itens
#define TAMANHO_MOCHILA 10
Item mochila[TAMANHO_MOCHILA];
int numeroDeItens = 0; // Controla a quantidade atual de itens na mochila
int vetorOrdenado = 0; // Flag para controlar se o vetor está ordenado

// Protótipos das funções
void inserirItem();
void removerItem();
void listarItens();
void buscarItemSequencial();
void ordenarItensBubbleSort();
void buscarItemBinario();

// --- FUNÇÃO PRINCIPAL ---
int main() {
    int opcao;
    do {
        printf("\n--- MOCHILA DE LOOT (LISTA SEQUENCIAL) ---\n");
        printf("1. Inserir novo item\n");
        printf("2. Remover um item\n");
        printf("3. Listar todos os itens\n");
        printf("4. Buscar item (Busca Sequencial)\n");
        printf("5. Ordenar itens por nome\n");
        printf("6. Buscar item (Busca Binaria)\n");
        printf("0. Sair do Programa\n");
        printf("------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer de entrada

        switch (opcao) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: buscarItemSequencial(); break;
            case 5: ordenarItensBubbleSort(); break;
            case 6: buscarItemBinario(); break;
            case 0: printf("Saindo do sistema...\n"); break;
            default: printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

void inserirItem() {
    if (numeroDeItens >= TAMANHO_MOCHILA) {
        printf("\nERRO: A mochila esta cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    printf("\n-- Cadastro de Novo Item --\n");
    Item novoItem;
    printf("Digite o nome do item: ");
    fgets(novoItem.nome, 30, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = 0; // Remove o '\n' do final

    printf("Digite o tipo do item: ");
    fgets(novoItem.tipo, 20, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = 0;

    printf("Digite a quantidade: ");
    scanf("%d", &novoItem.quantidade);
    getchar();

    mochila[numeroDeItens] = novoItem;
    numeroDeItens++;
    vetorOrdenado = 0; // Ao inserir, a lista pode ficar desordenada
    printf("\nItem '%s' cadastrado com sucesso!\n", novoItem.nome);
}

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
        // Usando strcmp para comparar os nomes
        if (strcmp(mochila[i].nome, nomeParaRemover) == 0) {
            indiceEncontrado = i;
            break;
        }
    }

    if (indiceEncontrado == -1) {
        printf("\nERRO: Item '%s' nao encontrado na mochila.\n", nomeParaRemover);
    } else {
        // Move os itens para preencher o espaço do item removido
        for (int i = indiceEncontrado; i < numeroDeItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        numeroDeItens--;
        vetorOrdenado = 0; // Ao remover, a ordem pode ser alterada
        printf("\nItem '%s' removido com sucesso!\n", nomeParaRemover);
    }
}

void listarItens() {
    printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", numeroDeItens, TAMANHO_MOCHILA);
    if (numeroDeItens == 0) {
        printf("A mochila esta vazia.\n");
    } else {
        for (int i = 0; i < numeroDeItens; i++) {
            printf("Item %d: { Nome: %s, Tipo: %s, Qtd: %d }\n", i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
        }
    }
    printf("---------------------------------\n");
}

void buscarItemSequencial() {
    if (numeroDeItens == 0) {
        printf("\nA mochila esta vazia.\n");
        return;
    }
    char nomeParaBuscar[30];
    printf("\nDigite o nome do item para buscar (Sequencial): ");
    fgets(nomeParaBuscar, 30, stdin);
    nomeParaBuscar[strcspn(nomeParaBuscar, "\n")] = 0;

    int comparacoes = 0;
    int encontrado = 0;
    for (int i = 0; i < numeroDeItens; i++) {
        comparacoes++;
        // Usando strcmp para comparar os nomes dos itens, conforme solicitado.
        if (strcmp(mochila[i].nome, nomeParaBuscar) == 0) {
            printf("\n--- Item Encontrado! ---\n");
            printf("  { Nome: %s, Tipo: %s, Qtd: %d }\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem '%s' nao foi encontrado.\n", nomeParaBuscar);
    }
    printf(">> Total de comparacoes realizadas: %d\n", comparacoes);
}

void ordenarItensBubbleSort() {
    if (numeroDeItens < 2) {
        printf("\nNao ha itens suficientes para ordenar.\n");
        return;
    }

    for (int i = 0; i < numeroDeItens - 1; i++) {
        for (int j = 0; j < numeroDeItens - i - 1; j++) {
            // Usando strcmp para decidir a ordem alfabética
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                Item temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
    vetorOrdenado = 1; // Marca o vetor como ordenado
    printf("\nMochila ordenada por nome com sucesso!\n");
    listarItens();
}

void buscarItemBinario() {
    if (!vetorOrdenado) {
        printf("\nERRO: A mochila precisa ser ordenada antes de usar a busca binaria.\n");
        printf("Use a opcao 5 para ordenar.\n");
        return;
    }
    if (numeroDeItens == 0) {
        printf("\nA mochila esta vazia.\n");
        return;
    }

    char nomeParaBuscar[30];
    printf("\nDigite o nome do item para buscar (Binaria): ");
    fgets(nomeParaBuscar, 30, stdin);
    nomeParaBuscar[strcspn(nomeParaBuscar, "\n")] = 0;

    int comparacoes = 0;
    int esquerda = 0, direita = numeroDeItens - 1;
    int encontrado = 0;

    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        comparacoes++;
        // Usando strcmp para comparar com o elemento do meio
        int res = strcmp(mochila[meio].nome, nomeParaBuscar);

        if (res == 0) { // Encontrou o item
            printf("\n--- Item Encontrado! ---\n");
            printf("  { Nome: %s, Tipo: %s, Qtd: %d }\n", mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade);
            encontrado = 1;
            break;
        }
        if (res < 0) { // O item procurado está à direita
            esquerda = meio + 1;
        } else { // O item procurado está à esquerda
            direita = meio - 1;
        }
    }
    
    if (!encontrado) {
        printf("\nItem '%s' nao foi encontrado.\n", nomeParaBuscar);
    }
    printf(">> Total de comparacoes realizadas: %d\n", comparacoes);
}
