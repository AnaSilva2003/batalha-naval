#include <stdio.h>
#include <stdlib.h> // Incluir para usar a função abs

// Definir o tamanho do tabuleiro
#define TAMANHO_TABULEIRO 10

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0; // 0 representa água
        }
    }
}

// Função para posicionar um navio horizontalmente
int posicionarNavioHorizontal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (coluna + 2 < TAMANHO_TABULEIRO) {
        for (int i = 0; i < 3; i++) {
            // Verifica se há sobreposição
            if (tabuleiro[linha][coluna + i] == 3) {
                printf("Erro: O navio já está posicionado nesta área.\n");
                return 0;
            }
            tabuleiro[linha][coluna + i] = 3; // 3 representa a parte do navio
        }
        return 1; // Retorna 1 se a posição for válida
    }
    return 0; // Retorna 0 se a posição não for válida
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro de Batalha Naval:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0)
                printf(" ~ ");  // Água
            else if (tabuleiro[i][j] == 3)
                printf(" # ");  // Navio
            else if (tabuleiro[i][j] == 5)
                printf(" * ");  // Área afetada pela habilidade
        }
        printf("\n");
    }
}

// Função para aplicar a habilidade do Cone
void aplicarHabilidadeCone(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linhaOrigem, int colunaOrigem) {
    int tamanho = 3; // Definindo o tamanho da área de efeito do cone
    for (int i = 0; i < tamanho; i++) {
        for (int j = -i; j <= i; j++) {
            int linha = linhaOrigem + i;
            int coluna = colunaOrigem + j;
            if (linha >= 0 && linha < TAMANHO_TABULEIRO && coluna >= 0 && coluna < TAMANHO_TABULEIRO) {
                tabuleiro[linha][coluna] = 5; // 5 representa área afetada
            }
        }
    }
}

// Função para aplicar a habilidade da Cruz
void aplicarHabilidadeCruz(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linhaOrigem, int colunaOrigem) {
    int tamanho = 1; // A Cruz afeta a linha e a coluna no ponto de origem
    // Linha afetada
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        tabuleiro[linhaOrigem][i] = 5; // 5 representa área afetada
    }
    // Coluna afetada
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        tabuleiro[i][colunaOrigem] = 5; // 5 representa área afetada
    }
}

// Função para aplicar a habilidade do Octaedro
void aplicarHabilidadeOctaedro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linhaOrigem, int colunaOrigem) {
    int tamanho = 3; // Definindo o tamanho da área de efeito do octaedro
    for (int i = -tamanho; i <= tamanho; i++) {
        for (int j = -tamanho; j <= tamanho; j++) {
            int linha = linhaOrigem + i;
            int coluna = colunaOrigem + j;
            // Verifica se o ponto está dentro do formato de losango (octaedro)
            if (abs(i) + abs(j) <= tamanho) {
                if (linha >= 0 && linha < TAMANHO_TABULEIRO && coluna >= 0 && coluna < TAMANHO_TABULEIRO) {
                    tabuleiro[linha][coluna] = 5; // 5 representa área afetada
                }
            }
        }
    }
}

int main() {
    // Declaração do tabuleiro 10x10
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa o tabuleiro com água
    inicializarTabuleiro(tabuleiro);

    // Posição e orientação dos navios
    int linhaNavioHorizontal = 2, colunaNavioHorizontal = 3; // Navio 1 horizontal
    int linhaNavioVertical = 5, colunaNavioVertical = 6;     // Navio 2 vertical

    // Posiciona os navios no tabuleiro
    if (!posicionarNavioHorizontal(tabuleiro, linhaNavioHorizontal, colunaNavioHorizontal)) {
        printf("Falha ao posicionar o navio horizontal.\n");
    }

    // Aplica as habilidades
    aplicarHabilidadeCone(tabuleiro, 1, 5);      // Aplica habilidade cone na posição (1,5)
    aplicarHabilidadeCruz(tabuleiro, 5, 5);      // Aplica habilidade cruz na posição (5,5)
    aplicarHabilidadeOctaedro(tabuleiro, 7, 7);  // Aplica habilidade octaedro na posição (7,7)

    // Exibe o tabuleiro com as habilidades aplicadas
    exibirTabuleiro(tabuleiro);

    return 0;
}
