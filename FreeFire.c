#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição da struct Item para representar cada item do inventário
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Variáveis globais
struct Item mochila[10]; // Vetor para armazenar até 10 itens
int totalItens = 0;      // Contador de itens na mochila

// Protótipos das funções
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();
void exibirMenu();
void limparBuffer();

int main() {
    printf("=== SISTEMA DE INVENTÁRIO - MOCHILA DE LOOT ===\n");
    printf("Bem-vindo ao sistema de gerenciamento de inventário!\n\n");
    
    int opcao;
    
    do {
        exibirMenu();
        printf("Digite sua opção: ");
        scanf("%d", &opcao);
        limparBuffer(); // Limpa o buffer do teclado
        
        switch(opcao) {
            case 1:
                inserirItem();
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
            case 5:
                printf("Saindo do sistema...\n");
                printf("Obrigado por usar o sistema de inventário!\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
        
        printf("\n");
    } while(opcao != 5);
    
    return 0;
}

// Função para exibir o menu de opções
void exibirMenu() {
    printf("=== MENU PRINCIPAL ===\n");
    printf("1. Cadastrar novo item\n");
    printf("2. Remover item\n");
    printf("3. Listar todos os itens\n");
    printf("4. Buscar item por nome\n");
    printf("5. Sair\n");
}

// Função para cadastrar um novo item na mochila
void inserirItem() {
    if(totalItens >= 10) {
        printf("ERRO: A mochila está cheia! Capacidade máxima: 10 itens.\n");
        return;
    }
    
    printf("\n=== CADASTRAR NOVO ITEM ===\n");
    
    // Solicita os dados do item
    printf("Nome do item (máx 30 caracteres): ");
    fgets(mochila[totalItens].nome, 30, stdin);
    mochila[totalItens].nome[strcspn(mochila[totalItens].nome, "\n")] = '\0'; // Remove o \n
    
    printf("Tipo do item (ex: arma, municao, cura, ferramenta): ");
    fgets(mochila[totalItens].tipo, 20, stdin);
    mochila[totalItens].tipo[strcspn(mochila[totalItens].tipo, "\n")] = '\0'; // Remove o \n
    
    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    limparBuffer(); // Limpa o buffer após scanf
    
    // Validações básicas
    if(mochila[totalItens].quantidade <= 0) {
        printf("ERRO: A quantidade deve ser maior que zero!\n");
        return;
    }
    
    if(strlen(mochila[totalItens].nome) == 0 || strlen(mochila[totalItens].tipo) == 0) {
        printf("ERRO: Nome e tipo são obrigatórios!\n");
        return;
    }
    
    totalItens++;
    printf("SUCESSO: Item '%s' cadastrado na mochila!\n", mochila[totalItens-1].nome);
    
    // Lista os itens após cadastro
    listarItens();
}

// Função para remover um item da mochila pelo nome
void removerItem() {
    if(totalItens == 0) {
        printf("AVISO: A mochila está vazia! Não há itens para remover.\n");
        return;
    }
    
    printf("\n=== REMOVER ITEM ===\n");
    
    char nomeBusca[30];
    printf("Digite o nome do item a ser removido: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0'; // Remove o \n
    
    // Busca sequencial pelo item
    int indice = -1;
    for(int i = 0; i < totalItens; i++) {
        if(strcmp(mochila[i].nome, nomeBusca) == 0) {
            indice = i;
            break;
        }
    }
    
    if(indice == -1) {
        printf("ERRO: Item '%s' não encontrado na mochila!\n", nomeBusca);
        return;
    }
    
    // Exibe informações do item que será removido
    printf("Item encontrado - Nome: %s, Tipo: %s, Quantidade: %d\n", 
           mochila[indice].nome, mochila[indice].tipo, mochila[indice].quantidade);
    
    // Remove o item deslocando os elementos
    for(int i = indice; i < totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    
    totalItens--;
    printf("SUCESSO: Item '%s' removido da mochila!\n", nomeBusca);
    
    // Lista os itens após remoção
    listarItens();
}

// Função para listar todos os itens da mochila
void listarItens() {
    printf("\n=== LISTA DE ITENS NA MOCHILA ===\n");
    
    if(totalItens == 0) {
        printf("A mochila está vazia.\n");
        return;
    }
    
    printf("Itens cadastrados: %d/10\n", totalItens);
    printf("----------------------------------------\n");
    
    for(int i = 0; i < totalItens; i++) {
        printf("Item %d:\n", i + 1);
        printf("  Nome: %s\n", mochila[i].nome);
        printf("  Tipo: %s\n", mochila[i].tipo);
        printf("  Quantidade: %d\n", mochila[i].quantidade);
        printf("----------------------------------------\n");
    }
}

// Função para buscar um item pelo nome usando busca sequencial
void buscarItem() {
    if(totalItens == 0) {
        printf("AVISO: A mochila está vazia! Não há itens para buscar.\n");
        return;
    }
    
    printf("\n=== BUSCAR ITEM ===\n");
    
    char nomeBusca[30];
    printf("Digite o nome do item a ser buscado: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0'; // Remove o \n
    
    // Implementação da busca sequencial
    int encontrado = 0;
    for(int i = 0; i < totalItens; i++) {
        if(strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nITEM ENCONTRADO:\n");
            printf("  Nome: %s\n", mochila[i].nome);
            printf("  Tipo: %s\n", mochila[i].tipo);
            printf("  Quantidade: %d\n", mochila[i].quantidade);
            printf("  Posição no inventário: %d\n", i + 1);
            encontrado = 1;
            break;
        }
    }
    
    if(!encontrado) {
        printf("Item '%s' não encontrado na mochila.\n", nomeBusca);
    }
}

// Função auxiliar para limpar o buffer de entrada
void limparBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}