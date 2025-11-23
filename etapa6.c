#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

#define MAX_PRODUTOS 100

struct Produto {
    char nome[50];
    float preco;
    int quantidade;
};

struct Produto produtos[MAX_PRODUTOS];
int totalProdutos = 0;

// ===== Declarações =====
void gotoxy(int x, int y);
int menuInterativo();
void adicionarProduto();
float calcularTotal();
float aplicarDesconto(float total);
void emitirNotaFiscal();
void limparBuffer();

// ===== MAIN =====
int main() {
    int opcao;
    do {
        opcao = menuInterativo();
        system("cls");

        switch (opcao) {
            case 1:
                adicionarProduto();
                break;
            case 2: {
                float total = calcularTotal();
                printf("\nTotal atual da compra: R$ %.2f\n", total);
                printf("\nPressione qualquer tecla para voltar ao menu...");
                getch();
                break;
            }
            case 3:
                emitirNotaFiscal();
                printf("\nPressione qualquer tecla para voltar ao menu...");
                getch();
                break;
            case 4:
                printf("\nEncerrando o sistema...\n");
                break;
            case 0:
                printf("\nSaindo do sistema pelo ESC...\n");
                break;
        }
    } while (opcao != 4 && opcao != 0);

    return 0;
}

// ===== Funções Auxiliares =====
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ===== Menu =====
int menuInterativo() {
    int pos = 1;
    char tecla;

    while (1) {
        system("cls");
        printf("====== MENU DO CAIXA ======\n\n");
        printf("%s Adicionar Produto\n",   (pos == 1) ? "->" : "  ");
        printf("%s Calcular Total\n",     (pos == 2) ? "->" : "  ");
        printf("%s Emitir Nota Fiscal\n", (pos == 3) ? "->" : "  ");
        printf("%s Sair\n",               (pos == 4) ? "->" : "  ");
        printf("\n(Use ↑ ↓ para navegar, ENTER para selecionar ou ESC para sair)\n");

        tecla = getch();

        if (tecla == 72 && pos > 1) pos--;
        if (tecla == 80 && pos < 4) pos++;
        if (tecla == 13) return pos;
        if (tecla == 27) return 0;
    }
}

// ===== Adicionar Produto =====
void adicionarProduto() {
    if (totalProdutos >= MAX_PRODUTOS) {
        printf("\nLimite de produtos atingido!\n");
        getch();
        return;
    }

    system("cls");
    printf("===== ADICIONAR PRODUTO =====\n");

    limparBuffer(); // limpa antes de ler texto
    printf("Nome do produto: ");
    fgets(produtos[totalProdutos].nome, sizeof(produtos[totalProdutos].nome), stdin);
    produtos[totalProdutos].nome[strcspn(produtos[totalProdutos].nome, "\n")] = '\0';

    printf("Preço (R$): ");
    while (scanf("%f", &produtos[totalProdutos].preco) != 1 || produtos[totalProdutos].preco <= 0) {
        printf("Preço inválido. Digite novamente: ");
        limparBuffer();
    }

    printf("Quantidade: ");
    while (scanf("%d", &produtos[totalProdutos].quantidade) != 1 || produtos[totalProdutos].quantidade <= 0) {
        printf("Quantidade inválida. Digite novamente: ");
        limparBuffer();
    }

    printf("\nProduto adicionado com sucesso!");
    printf("\n-> %s | Preço: R$ %.2f | Qtd: %d\n",
           produtos[totalProdutos].nome,
           produtos[totalProdutos].preco,
           produtos[totalProdutos].quantidade);

    totalProdutos++;

    printf("\nPressione qualquer tecla para voltar ao menu...");
    getch();
}

// ===== Calcular Total =====
float calcularTotal() {
    float total = 0.0f;
    for (int i = 0; i < totalProdutos; i++) {
        total += produtos[i].preco * produtos[i].quantidade;
    }
    return total;
}

// ===== Aplicar Desconto =====
float aplicarDesconto(float total) {
    float desconto;
    printf("\nDigite o percentual de desconto (0-100): ");
    while (scanf("%f", &desconto) != 1 || desconto < 0 || desconto > 100) {
        printf("Valor inválido! Digite novamente (0-100): ");
        limparBuffer();
    }

    float totalComDesconto = total - (total * desconto / 100);
    printf("Desconto de %.1f%% aplicado! Novo total: R$ %.2f\n", desconto, totalComDesconto);
    return totalComDesconto;
}

// ===== Nota Fiscal =====
void emitirNotaFiscal() {
    if (totalProdutos == 0) {
        printf("\nNenhum produto registrado!\n");
        return;
    }

    system("cls");
    printf("====== NOTA FISCAL ======\n\n");
    printf("%-3s %-25s %-10s %-10s %-10s\n", "Nº", "Produto", "Qtd", "Preço", "Subtotal");
    printf("--------------------------------------------------------------\n");

    float total = 0;
    for (int i = 0; i < totalProdutos; i++) {
        float subtotal = produtos[i].preco * produtos[i].quantidade;
        total += subtotal;
        printf("%-3d %-25s %-10d %-10.2f %-10.2f\n",
               i + 1,
               produtos[i].nome,
               produtos[i].quantidade,
               produtos[i].preco,
               subtotal);
    }

    printf("--------------------------------------------------------------\n");
    printf("TOTAL: R$ %.2f\n", total);

    int opc;
    printf("\nDeseja aplicar desconto? (1 - Sim / 0 - Não): ");
    while (scanf("%d", &opc) != 1 || (opc != 0 && opc != 1)) {
        printf("Opção inválida! Digite 1 ou 0: ");
        limparBuffer();
    }

    if (opc == 1) {
        total = aplicarDesconto(total);
    }

    printf("\nTOTAL FINAL: R$ %.2f\n", total);
    printf("==============================================================\n");
}