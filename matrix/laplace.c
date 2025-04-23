#include <stdio.h>

#define MAX 10  // tamanho máximo da matriz

// função para obter a submatriz excluindo a linha e a coluna dadas
void getSubmatrix(int mat[MAX][MAX], int submat[MAX][MAX], int n, int exclui_linha, int exclui_coluna) {
    int i = 0, j = 0;
    for (int linha = 0; linha < n; linha++) {
        if (linha == exclui_linha) continue;
        j = 0;
        for (int coluna = 0; coluna < n; coluna++) {
            if (coluna == exclui_coluna) continue;
            submat[i][j++] = mat[linha][coluna];
        }
        i++;
    }
}

// função recursiva para calcular o determinante
int determinante(int mat[MAX][MAX], int n) {
    if (n == 1)
        return mat[0][0];
    if (n == 2)
        return mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];

    int submat[MAX][MAX];
    int det = 0;

    for (int x = 0; x < n; x++) {
        getSubmatrix(mat, submat, n, 0, x); // expansão pela 1ª linha (linha 0)
        int sinal = (x % 2 == 0) ? 1 : -1;
        det += sinal * mat[0][x] * determinante(submat, n - 1);
    }

    return det;
}

// função para ler e testar a matriz
int main() {
    int mat[MAX][MAX], ordem;

    printf("Informe a ordem da matriz (até %d): ", MAX);
    scanf("%d", &ordem);

    if (ordem < 1 || ordem > MAX) {
        printf("Ordem inválida.\n");
        return 1;
    }

    printf("Digite os elementos da matriz %dx%d:\n", ordem, ordem);
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            printf("mat[%d][%d]: ", i, j);
            scanf("%d", &mat[i][j]);
        }
    }

    int resultado = determinante(mat, ordem);
    printf("Determinante: %d\n", resultado);

    return 0;
}
