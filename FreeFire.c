#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Item para representar cada item do inventário
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Definição do nó para lista encadeada
struct No {
    struct Item dados;
    struct No* proximo;
};

// Variáveis globais para VETOR
struct Item mochilaVetor[10];
int totalItensVetor = 0;
int comparacoesVetor = 0;

// Variáveis globais para LISTA ENCADEADA
struct No* headLista = NULL;
int totalItensLista = 0;
int comparacoesLista = 0;

// Protótipos das funções
// Funções gerais
void exibirMenuPrincipal();
void limparBuffer();

// Funções para VETOR
void menuVetor();
void inserirItemVetor();
void removerItemVetor();
void listarItensVetor();
void buscarSequencialVetor();
void ordenarVetor();
void buscarBinariaVetor();
int buscaBinariaRecursiva(struct Item vetor[], int inicio, int fim, char nome[]);

// Funções para LISTA ENCADEADA
void menuListaEncadeada();
void inserirItemLista();
void removerItemLista();
void listarItensLista();
void buscarItemLista();
struct No* criarNo(struct Item novoItem);
void liberarLista();

int main() {
    printf("=== SISTEMA DE INVENTÁRIO AVANÇADO ===\n");
    printf("Comparação entre Vetor e Lista Encadeada\n\n");
    
    int opcao;
    
    do {
        exibirMenuPrincipal();
        printf("Digite sua opção: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                menuVetor();
                break;
            case 2:
                menuListaEncadeada();
                break;
            case 3:
                printf("Saindo do sistema...\n");
                printf("Obrigado por usar o sistema de inventário avançado!\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
        
        printf("\n");
    } while(opcao != 3);
    
    // Libera memória da lista encadeada ao sair
    liberarLista();
    
    return 0;
}

// ===============================
// FUNÇÕES GERAIS
// ===============================

void exibirMenuPrincipal() {
    printf("=== MENU PRINCIPAL ===\n");
    printf("1. Trabalhar com VETOR (Lista Sequencial)\n");
    printf("2. Trabalhar com LISTA ENCADEADA\n");
    printf("3. Sair\n");
}

void limparBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

// ===============================
// IMPLEMENTAÇÃO COM VETOR
// ===============================

void menuVetor() {
    int opcao;
    
    do {
        printf("\n=== MODO VETOR (Lista Sequencial) ===\n");
        printf("Itens na mochila: %d/10\n", totalItensVetor);
        printf("1. Inserir novo item\n");
        printf("2. Remover item por nome\n");
        printf("3. Listar todos os itens\n");
        printf("4. Busca sequencial por nome\n");
        printf("5. Ordenar itens por nome (Bubble Sort)\n");
        printf("6. Busca binária por nome (requer ordenação)\n");
        printf("7. Voltar ao menu principal\n");
        printf("Digite sua opção: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                inserirItemVetor();
                break;
            case 2:
                removerItemVetor();
                break;
            case 3:
                listarItensVetor();
                break;
            case 4:
                buscarSequencialVetor();
                break;
            case 5:
                ordenarVetor();
                break;
            case 6:
                buscarBinariaVetor();
                break;
            case 7:
                printf("Retornando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while(opcao != 7);
}

void inserirItemVetor() {
    if(totalItensVetor >= 10) {
        printf("ERRO: A mochila está cheia! Capacidade máxima: 10 itens.\n");
        return;
    }
    
    printf("\n=== CADASTRAR NOVO ITEM NO VETOR ===\n");
    
    printf("Nome do item (máx 30 caracteres): ");
    fgets(mochilaVetor[totalItensVetor].nome, 30, stdin);
    mochilaVetor[totalItensVetor].nome[strcspn(mochilaVetor[totalItensVetor].nome, "\n")] = '\0';
    
    printf("Tipo do item (ex: arma, municao, cura, ferramenta): ");
    fgets(mochilaVetor[totalItensVetor].tipo, 20, stdin);
    mochilaVetor[totalItensVetor].tipo[strcspn(mochilaVetor[totalItensVetor].tipo, "\n")] = '\0';
    
    printf("Quantidade: ");
    scanf("%d", &mochilaVetor[totalItensVetor].quantidade);
    limparBuffer();
    
    if(mochilaVetor[totalItensVetor].quantidade <= 0) {
        printf("ERRO: A quantidade deve ser maior que zero!\n");
        return;
    }
    
    totalItensVetor++;
    printf("SUCESSO: Item '%s' cadastrado no vetor!\n", mochilaVetor[totalItensVetor-1].nome);
    
    listarItensVetor();
}

void removerItemVetor() {
    if(totalItensVetor == 0) {
        printf("AVISO: A mochila está vazia! Não há itens para remover.\n");
        return;
    }
    
    printf("\n=== REMOVER ITEM DO VETOR ===\n");
    
    char nomeBusca[30];
    printf("Digite o nome do item a ser removido: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    // Busca sequencial para encontrar o item
    int indice = -1;
    comparacoesVetor = 0;
    
    for(int i = 0; i < totalItensVetor; i++) {
        comparacoesVetor++;
        if(strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            indice = i;
            break;
        }
    }
    
    if(indice == -1) {
        printf("ERRO: Item '%s' não encontrado na mochila! (%d comparações)\n", nomeBusca, comparacoesVetor);
        return;
    }
    
    printf("Item encontrado - Nome: %s, Tipo: %s, Quantidade: %d (%d comparações)\n", 
           mochilaVetor[indice].nome, mochilaVetor[indice].tipo, mochilaVetor[indice].quantidade, comparacoesVetor);
    
    // Remove o item deslocando os elementos
    for(int i = indice; i < totalItensVetor - 1; i++) {
        mochilaVetor[i] = mochilaVetor[i + 1];
    }
    
    totalItensVetor--;
    printf("SUCESSO: Item '%s' removido do vetor!\n", nomeBusca);
    
    listarItensVetor();
}

void listarItensVetor() {
    printf("\n=== LISTA DE ITENS NO VETOR ===\n");
    
    if(totalItensVetor == 0) {
        printf("A mochila está vazia.\n");
        return;
    }
    
    printf("Itens cadastrados: %d/10\n", totalItensVetor);
    printf("----------------------------------------\n");
    
    for(int i = 0; i < totalItensVetor; i++) {
        printf("Item %d:\n", i + 1);
        printf("  Nome: %s\n", mochilaVetor[i].nome);
        printf("  Tipo: %s\n", mochilaVetor[i].tipo);
        printf("  Quantidade: %d\n", mochilaVetor[i].quantidade);
        printf("----------------------------------------\n");
    }
}

void buscarSequencialVetor() {
    if(totalItensVetor == 0) {
        printf("AVISO: A mochila está vazia! Não há itens para buscar.\n");
        return;
    }
    
    printf("\n=== BUSCA SEQUENCIAL NO VETOR ===\n");
    
    char nomeBusca[30];
    printf("Digite o nome do item a ser buscado: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    comparacoesVetor = 0;
    int encontrado = 0;
    
    for(int i = 0; i < totalItensVetor; i++) {
        comparacoesVetor++;
        if(strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            printf("\nITEM ENCONTRADO (Busca Sequencial):\n");
            printf("  Nome: %s\n", mochilaVetor[i].nome);
            printf("  Tipo: %s\n", mochilaVetor[i].tipo);
            printf("  Quantidade: %d\n", mochilaVetor[i].quantidade);
            printf("  Posição no inventário: %d\n", i + 1);
            printf("  Comparações realizadas: %d\n", comparacoesVetor);
            encontrado = 1;
            break;
        }
    }
    
    if(!encontrado) {
        printf("Item '%s' não encontrado na mochila. (%d comparações)\n", nomeBusca, comparacoesVetor);
    }
}

void ordenarVetor() {
    if(totalItensVetor == 0) {
        printf("AVISO: A mochila está vazia! Não há itens para ordenar.\n");
        return;
    }
    
    printf("\n=== ORDENANDO VETOR POR NOME (Bubble Sort) ===\n");
    
    int trocas = 0;
    int comparacoes = 0;
    
    // Bubble Sort
    for(int i = 0; i < totalItensVetor - 1; i++) {
        for(int j = 0; j < totalItensVetor - i - 1; j++) {
            comparacoes++;
            if(strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                // Troca os elementos
                struct Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
                trocas++;
            }
        }
    }
    
    printf("Ordenação concluída!\n");
    printf("Comparações realizadas: %d\n", comparacoes);
    printf("Trocas realizadas: %d\n", trocas);
    
    listarItensVetor();
}

// Função auxiliar para busca binária recursiva
int buscaBinariaRecursiva(struct Item vetor[], int inicio, int fim, char nome[]) {
    comparacoesVetor++;
    
    if (fim >= inicio) {
        int meio = inicio + (fim - inicio) / 2;
        
        int comparacao = strcmp(vetor[meio].nome, nome);
        
        if (comparacao == 0) {
            return meio; // Item encontrado
        }
        
        if (comparacao > 0) {
            return buscaBinariaRecursiva(vetor, inicio, meio - 1, nome);
        }
        
        return buscaBinariaRecursiva(vetor, meio + 1, fim, nome);
    }
    
    return -1; // Item não encontrado
}

void buscarBinariaVetor() {
    if(totalItensVetor == 0) {
        printf("AVISO: A mochila está vazia! Não há itens para buscar.\n");
        return;
    }
    
    printf("\n=== BUSCA BINÁRIA NO VETOR ===\n");
    printf("AVISO: A busca binária requer que o vetor esteja ordenado por nome!\n");
    
    char nomeBusca[30];
    printf("Digite o nome do item a ser buscado: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    comparacoesVetor = 0;
    int indice = buscaBinariaRecursiva(mochilaVetor, 0, totalItensVetor - 1, nomeBusca);
    
    if(indice != -1) {
        printf("\nITEM ENCONTRADO (Busca Binária):\n");
        printf("  Nome: %s\n", mochilaVetor[indice].nome);
        printf("  Tipo: %s\n", mochilaVetor[indice].tipo);
        printf("  Quantidade: %d\n", mochilaVetor[indice].quantidade);
        printf("  Posição no inventário: %d\n", indice + 1);
        printf("  Comparações realizadas: %d\n", comparacoesVetor);
    } else {
        printf("Item '%s' não encontrado na mochila. (%d comparações)\n", nomeBusca, comparacoesVetor);
    }
}

// ===============================
// IMPLEMENTAÇÃO COM LISTA ENCADEADA
// ===============================

void menuListaEncadeada() {
    int opcao;
    
    do {
        printf("\n=== MODO LISTA ENCADEADA ===\n");
        printf("Itens na mochila: %d\n", totalItensLista);
        printf("1. Inserir novo item\n");
        printf("2. Remover item por nome\n");
        printf("3. Listar todos os itens\n");
        printf("4. Buscar item por nome\n");
        printf("5. Voltar ao menu principal\n");
        printf("Digite sua opção: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                inserirItemLista();
                break;
            case 2:
                removerItemLista();
                break;
            case 3:
                listarItensLista();
                break;
            case 4:
                buscarItemLista();
                break;
            case 5:
                printf("Retornando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while(opcao != 5);
}

struct No* criarNo(struct Item novoItem) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    if(novoNo == NULL) {
        printf("ERRO: Falha na alocação de memória!\n");
        return NULL;
    }
    novoNo->dados = novoItem;
    novoNo->proximo = NULL;
    return novoNo;
}

void inserirItemLista() {
    printf("\n=== CADASTRAR NOVO ITEM NA LISTA ENCADEADA ===\n");
    
    struct Item novoItem;
    
    printf("Nome do item (máx 30 caracteres): ");
    fgets(novoItem.nome, 30, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0';
    
    printf("Tipo do item (ex: arma, municao, cura, ferramenta): ");
    fgets(novoItem.tipo, 20, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0';
    
    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    limparBuffer();
    
    if(novoItem.quantidade <= 0) {
        printf("ERRO: A quantidade deve ser maior que zero!\n");
        return;
    }
    
    struct No* novoNo = criarNo(novoItem);
    if(novoNo == NULL) return;
    
    // Inserção no início da lista
    novoNo->proximo = headLista;
    headLista = novoNo;
    totalItensLista++;
    
    printf("SUCESSO: Item '%s' cadastrado na lista encadeada!\n", novoItem.nome);
    
    listarItensLista();
}

void removerItemLista() {
    if(headLista == NULL) {
        printf("AVISO: A mochila está vazia! Não há itens para remover.\n");
        return;
    }
    
    printf("\n=== REMOVER ITEM DA LISTA ENCADEADA ===\n");
    
    char nomeBusca[30];
    printf("Digite o nome do item a ser removido: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    struct No* atual = headLista;
    struct No* anterior = NULL;
    comparacoesLista = 0;
    int encontrado = 0;
    
    while(atual != NULL) {
        comparacoesLista++;
        if(strcmp(atual->dados.nome, nomeBusca) == 0) {
            encontrado = 1;
            
            printf("Item encontrado - Nome: %s, Tipo: %s, Quantidade: %d (%d comparações)\n", 
                   atual->dados.nome, atual->dados.tipo, atual->dados.quantidade, comparacoesLista);
            
            if(anterior == NULL) {
                // Remove o primeiro nó
                headLista = atual->proximo;
            } else {
                // Remove nó do meio ou final
                anterior->proximo = atual->proximo;
            }
            
            free(atual);
            totalItensLista--;
            printf("SUCESSO: Item '%s' removido da lista encadeada!\n", nomeBusca);
            break;
        }
        
        anterior = atual;
        atual = atual->proximo;
    }
    
    if(!encontrado) {
        printf("ERRO: Item '%s' não encontrado na mochila! (%d comparações)\n", nomeBusca, comparacoesLista);
    } else {
        listarItensLista();
    }
}

void listarItensLista() {
    printf("\n=== LISTA DE ITENS NA LISTA ENCADEADA ===\n");
    
    if(headLista == NULL) {
        printf("A mochila está vazia.\n");
        return;
    }
    
    printf("Itens cadastrados: %d\n", totalItensLista);
    printf("----------------------------------------\n");
    
    struct No* atual = headLista;
    int posicao = 1;
    
    while(atual != NULL) {
        printf("Item %d:\n", posicao);
        printf("  Nome: %s\n", atual->dados.nome);
        printf("  Tipo: %s\n", atual->dados.tipo);
        printf("  Quantidade: %d\n", atual->dados.quantidade);
        printf("  Endereço: %p -> Próximo: %p\n", (void*)atual, (void*)atual->proximo);
        printf("----------------------------------------\n");
        
        atual = atual->proximo;
        posicao++;
    }
}

void buscarItemLista() {
    if(headLista == NULL) {
        printf("AVISO: A mochila está vazia! Não há itens para buscar.\n");
        return;
    }
    
    printf("\n=== BUSCAR ITEM NA LISTA ENCADEADA ===\n");
    
    char nomeBusca[30];
    printf("Digite o nome do item a ser buscado: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    struct No* atual = headLista;
    comparacoesLista = 0;
    int posicao = 1;
    int encontrado = 0;
    
    while(atual != NULL) {
        comparacoesLista++;
        if(strcmp(atual->dados.nome, nomeBusca) == 0) {
            printf("\nITEM ENCONTRADO (Lista Encadeada):\n");
            printf("  Nome: %s\n", atual->dados.nome);
            printf("  Tipo: %s\n", atual->dados.tipo);
            printf("  Quantidade: %d\n", atual->dados.quantidade);
            printf("  Posição na lista: %d\n", posicao);
            printf("  Endereço: %p\n", (void*)atual);
            printf("  Comparações realizadas: %d\n", comparacoesLista);
            encontrado = 1;
            break;
        }
        
        atual = atual->proximo;
        posicao++;
    }
    
    if(!encontrado) {
        printf("Item '%s' não encontrado na mochila. (%d comparações)\n", nomeBusca, comparacoesLista);
    }
}

void liberarLista() {
    struct No* atual = headLista;
    while(atual != NULL) {
        struct No* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    headLista = NULL;
    totalItensLista = 0;
}