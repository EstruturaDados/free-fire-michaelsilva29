#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Componente para representar cada componente da torre
struct Componente {
    char nome[30];
    char tipo[20];
    int prioridade;
};

// Variáveis globais
struct Componente componentes[20];
int totalComponentes = 0;
int comparacoes = 0;
int trocas = 0;
int vetorOrdenadoPorNome = 0; // Flag para controlar se o vetor está ordenado por nome

// Protótipos das funções
void exibirMenu();
void cadastrarComponentes();
void mostrarComponentes();
void bubbleSortNome();
void insertionSortTipo();
void selectionSortPrioridade();
void buscaBinariaPorNome();
void medirTempo(void (*algoritmo)(), char* nomeAlgoritmo);
void limparBuffer();
void resetarMetricas();

int main() {
    printf("=== SISTEMA DE MONTAGEM DA TORRE DE RESGATE ===\n");
    printf("Última safe zone - Fase Final do Jogo!\n\n");
    
    int opcao;
    
    do {
        exibirMenu();
        printf("Digite sua opção: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                cadastrarComponentes();
                break;
            case 2:
                mostrarComponentes();
                break;
            case 3:
                medirTempo(bubbleSortNome, "Bubble Sort (Nome)");
                break;
            case 4:
                medirTempo(insertionSortTipo, "Insertion Sort (Tipo)");
                break;
            case 5:
                medirTempo(selectionSortPrioridade, "Selection Sort (Prioridade)");
                break;
            case 6:
                buscaBinariaPorNome();
                break;
            case 7:
                printf("=== INICIANDO MONTAGEM DA TORRE ===\n");
                printf("Verificando componentes...\n");
                if(totalComponentes > 0) {
                    printf("Torre pronta para montagem!\n");
                    mostrarComponentes();
                } else {
                    printf("ERRO: Nenhum componente cadastrado!\n");
                }
                break;
            case 8:
                printf("Saindo do sistema...\n");
                printf("Boa sorte na fuga da ilha!\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
        
        printf("\n");
    } while(opcao != 8);
    
    return 0;
}

void exibirMenu() {
    printf("=== MENU DA TORRE DE RESGATE ===\n");
    printf("Componentes cadastrados: %d/20\n", totalComponentes);
    printf("Status ordenação por nome: %s\n", vetorOrdenadoPorNome ? "SIM" : "NÃO");
    printf("1. Cadastrar componentes\n");
    printf("2. Mostrar todos os componentes\n");
    printf("3. Ordenar por NOME (Bubble Sort)\n");
    printf("4. Ordenar por TIPO (Insertion Sort)\n");
    printf("5. Ordenar por PRIORIDADE (Selection Sort)\n");
    printf("6. Busca binária por nome (requer ordenação por nome)\n");
    printf("7. Iniciar montagem final da torre\n");
    printf("8. Sair\n");
}

void cadastrarComponentes() {
    if(totalComponentes >= 20) {
        printf("ERRO: Capacidade máxima de 20 componentes atingida!\n");
        return;
    }
    
    printf("\n=== CADASTRO DE COMPONENTES ===\n");
    printf("Quantos componentes deseja cadastrar? (máx %d): ", 20 - totalComponentes);
    int quantidade;
    scanf("%d", &quantidade);
    limparBuffer();
    
    if(quantidade <= 0 || quantidade > (20 - totalComponentes)) {
        printf("ERRO: Quantidade inválida!\n");
        return;
    }
    
    for(int i = 0; i < quantidade; i++) {
        printf("\n--- Componente %d ---\n", totalComponentes + 1);
        
        printf("Nome do componente (ex: 'chip central', 'propulsor'): ");
        fgets(componentes[totalComponentes].nome, 30, stdin);
        componentes[totalComponentes].nome[strcspn(componentes[totalComponentes].nome, "\n")] = '\0';
        
        printf("Tipo (controle, suporte, propulsao, energia, seguranca): ");
        fgets(componentes[totalComponentes].tipo, 20, stdin);
        componentes[totalComponentes].tipo[strcspn(componentes[totalComponentes].tipo, "\n")] = '\0';
        
        printf("Prioridade (1-10, onde 10 é mais importante): ");
        scanf("%d", &componentes[totalComponentes].prioridade);
        limparBuffer();
        
        // Validação da prioridade
        if(componentes[totalComponentes].prioridade < 1 || componentes[totalComponentes].prioridade > 10) {
            printf("AVISO: Prioridade ajustada para valor padrão 5\n");
            componentes[totalComponentes].prioridade = 5;
        }
        
        totalComponentes++;
    }
    
    vetorOrdenadoPorNome = 0; // Reset da flag de ordenação
    printf("\nSUCESSO: %d componentes cadastrados!\n", quantidade);
}

void mostrarComponentes() {
    if(totalComponentes == 0) {
        printf("AVISO: Nenhum componente cadastrado!\n");
        return;
    }
    
    printf("\n=== COMPONENTES DA TORRE ===\n");
    printf("Total: %d componentes\n\n", totalComponentes);
    printf("%-3s %-25s %-15s %-10s\n", "#", "NOME", "TIPO", "PRIORIDADE");
    printf("-------------------------------------------------\n");
    
    for(int i = 0; i < totalComponentes; i++) {
        printf("%-3d %-25s %-15s %-10d\n", 
               i + 1, 
               componentes[i].nome, 
               componentes[i].tipo, 
               componentes[i].prioridade);
    }
    
    // Calcular prioridade média
    int somaPrioridades = 0;
    for(int i = 0; i < totalComponentes; i++) {
        somaPrioridades += componentes[i].prioridade;
    }
    double prioridadeMedia = (double)somaPrioridades / totalComponentes;
    
    printf("-------------------------------------------------\n");
    printf("Prioridade média: %.2f/10.0\n", prioridadeMedia);
    
    if(prioridadeMedia >= 7.0) {
        printf("STATUS: Torre bem priorizada! ✅\n");
    } else if(prioridadeMedia >= 5.0) {
        printf("STATUS: Prioridade aceitável ⚠️\n");
    } else {
        printf("STATUS: Atenção! Prioridade muito baixa! ❌\n");
    }
}

void bubbleSortNome() {
    if(totalComponentes == 0) {
        printf("ERRO: Nenhum componente para ordenar!\n");
        return;
    }
    
    resetarMetricas();
    printf("Iniciando Bubble Sort por nome...\n");
    
    // Implementação do Bubble Sort
    for(int i = 0; i < totalComponentes - 1; i++) {
        for(int j = 0; j < totalComponentes - i - 1; j++) {
            comparacoes++;
            // Compara os nomes dos componentes
            if(strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                // Troca os componentes
                struct Componente temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
                trocas++;
            }
        }
    }
    
    vetorOrdenadoPorNome = 1;
    printf("Ordenação concluída!\n");
}

void insertionSortTipo() {
    if(totalComponentes == 0) {
        printf("ERRO: Nenhum componente para ordenar!\n");
        return;
    }
    
    resetarMetricas();
    printf("Iniciando Insertion Sort por tipo...\n");
    
    // Implementação do Insertion Sort
    for(int i = 1; i < totalComponentes; i++) {
        struct Componente chave = componentes[i];
        int j = i - 1;
        
        // Move elementos maiores que a chave para frente
        while(j >= 0) {
            comparacoes++;
            if(strcmp(componentes[j].tipo, chave.tipo) > 0) {
                componentes[j + 1] = componentes[j];
                trocas++;
                j--;
            } else {
                break;
            }
        }
        componentes[j + 1] = chave;
        if(j + 1 != i) trocas++; // Conta a inserção final como troca
    }
    
    printf("Ordenação concluída!\n");
}

void selectionSortPrioridade() {
    if(totalComponentes == 0) {
        printf("ERRO: Nenhum componente para ordenar!\n");
        return;
    }
    
    resetarMetricas();
    printf("Iniciando Selection Sort por prioridade...\n");
    
    // Implementação do Selection Sort
    for(int i = 0; i < totalComponentes - 1; i++) {
        int indiceMenor = i;
        
        // Encontra o índice do componente com menor prioridade
        for(int j = i + 1; j < totalComponentes; j++) {
            comparacoes++;
            if(componentes[j].prioridade < componentes[indiceMenor].prioridade) {
                indiceMenor = j;
            }
        }
        
        // Troca se necessário
        if(indiceMenor != i) {
            struct Componente temp = componentes[i];
            componentes[i] = componentes[indiceMenor];
            componentes[indiceMenor] = temp;
            trocas++;
        }
    }
    
    printf("Ordenação concluída!\n");
}

void buscaBinariaPorNome() {
    if(totalComponentes == 0) {
        printf("ERRO: Nenhum componente para buscar!\n");
        return;
    }
    
    if(!vetorOrdenadoPorNome) {
        printf("ERRO: O vetor precisa estar ordenado por nome para busca binária!\n");
        printf("Use a opção 3 (Bubble Sort) primeiro.\n");
        return;
    }
    
    printf("\n=== BUSCA BINÁRIA - COMPONENTE-CHAVE ===\n");
    printf("Digite o nome exato do componente a ser buscado: ");
    
    char nomeBusca[30];
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    resetarMetricas();
    
    // Implementação da busca binária
    int inicio = 0;
    int fim = totalComponentes - 1;
    int encontrado = -1;
    
    while(inicio <= fim) {
        comparacoes++;
        int meio = (inicio + fim) / 2;
        
        int resultado = strcmp(componentes[meio].nome, nomeBusca);
        
        if(resultado == 0) {
            encontrado = meio;
            break;
        } else if(resultado < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    
    printf("\n--- RESULTADO DA BUSCA ---\n");
    printf("Comparações realizadas: %d\n", comparacoes);
    
    if(encontrado != -1) {
        printf("✅ COMPONENTE ENCONTRADO!\n\n");
        printf("Detalhes do componente:\n");
        printf("Nome: %s\n", componentes[encontrado].nome);
        printf("Tipo: %s\n", componentes[encontrado].tipo);
        printf("Prioridade: %d/10\n", componentes[encontrado].prioridade);
        printf("Posição no inventário: %d\n", encontrado + 1);
        
        // Verificação especial para componentes críticos
        if(strstr(componentes[encontrado].nome, "chip") != NULL || 
           strstr(componentes[encontrado].nome, "central") != NULL) {
            printf("\n🚨 COMPONENTE CRÍTICO IDENTIFICADO!\n");
            printf("Este componente é essencial para ativação da torre!\n");
        }
    } else {
        printf("❌ COMPONENTE NÃO ENCONTRADO!\n");
        printf("Verifique se o nome está correto e se o vetor está ordenado.\n");
    }
}

void medirTempo(void (*algoritmo)(), char* nomeAlgoritmo) {
    if(totalComponentes == 0) {
        printf("ERRO: Nenhum componente para ordenar!\n");
        return;
    }
    
    printf("\n=== EXECUTANDO %s ===\n", nomeAlgoritmo);
    
    // Faz uma cópia do vetor original para preservar os dados
    struct Componente copia[20];
    memcpy(copia, componentes, sizeof(componentes));
    
    clock_t inicio = clock();
    algoritmo(); // Executa o algoritmo de ordenação
    clock_t fim = clock();
    
    double tempoDecorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000.0;
    
    printf("\n--- MÉTRICAS DE DESEMPENHO ---\n");
    printf("Algoritmo: %s\n", nomeAlgoritmo);
    printf("Componentes ordenados: %d\n", totalComponentes);
    printf("Comparações realizadas: %d\n", comparacoes);
    printf("Trocas realizadas: %d\n", trocas);
    printf("Tempo de execução: %.3f milissegundos\n", tempoDecorrido);
    
    // Análise de eficiência
    printf("\n--- ANÁLISE DE EFICIÊNCIA ---\n");
    if(tempoDecorrido < 1.0) {
        printf("✅ Excelente desempenho!\n");
    } else if(tempoDecorrido < 5.0) {
        printf("⚠️  Desempenho aceitável\n");
    } else {
        printf("❌ Desempenho lento - considere outro algoritmo\n");
    }
    
    // Mostra os primeiros componentes ordenados
    printf("\nPrimeiros 5 componentes ordenados:\n");
    printf("%-25s %-15s %-10s\n", "NOME", "TIPO", "PRIORIDADE");
    printf("---------------------------------------------\n");
    for(int i = 0; i < 5 && i < totalComponentes; i++) {
        printf("%-25s %-15s %-10d\n", 
               componentes[i].nome, componentes[i].tipo, componentes[i].prioridade);
    }
    
    // Pergunta se deseja manter a ordenação
    printf("\nDeseja manter esta ordenação? (s/n): ");
    char resposta;
    scanf("%c", &resposta);
    limparBuffer();
    
    if(resposta == 'n' || resposta == 'N') {
        // Restaura a cópia original
        memcpy(componentes, copia, sizeof(copia));
        printf("Ordenação descartada. Vetor restaurado.\n");
        if(algoritmo == bubbleSortNome) {
            vetorOrdenadoPorNome = 0;
        }
    } else {
        printf("Ordenação mantida!\n");
    }
}

void resetarMetricas() {
    comparacoes = 0;
    trocas = 0;
}

void limparBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}