#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5   

typedef struct {
    char nome;
    int id;     
} Peca;

typedef struct {
    Peca itens[TAM_FILA];
    int frente;
    int tras;
    int quantidade;
} Fila;

void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->quantidade = 0;
}

int filaCheia(Fila *f) {
    return f->quantidade == TAM_FILA;
}

int filaVazia(Fila *f) {
    return f->quantidade == 0;
}

Peca gerarPeca(int idPeca) {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = idPeca;
    return p;
}

void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("\n❌ A fila está cheia! Não é possível inserir.\n");
        return;
    }

    f->tras = (f->tras + 1) % TAM_FILA;
    f->itens[f->tras] = p;
    f->quantidade++;

    printf("\n✔ Nova peça inserida: [%c %d]\n", p.nome, p.id);
}

void dequeue(Fila *f) {
    if (filaVazia(f)) {
        printf("\n❌ A fila está vazia! Nenhuma peça para jogar.\n");
        return;
    }

    Peca p = f->itens[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    f->quantidade--;

    printf("\n🕹 Peça jogada: [%c %d]\n", p.nome, p.id);
}

void exibirFila(Fila *f) {
    printf("\n📌 **Fila de peças**\n");

    if (filaVazia(f)) {
        printf("(vazia)\n");
        return;
    }

    int i = f->frente;
    for (int c = 0; c < f->quantidade; c++) {
        Peca p = f->itens[i];
        printf("[%c %d] ", p.nome, p.id);
        i = (i + 1) % TAM_FILA;
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    Fila fila;
    inicializarFila(&fila);

    int opcao;
    int idGlobal = 0;

    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca(idGlobal++));
    }

    printf("=== Sistema de Fila de Peças - Tetris Stack ===\n");

    do {
        exibirFila(&fila);

        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                dequeue(&fila);
                break;

            case 2:
                enqueue(&fila, gerarPeca(idGlobal++));
                break;

            case 0:
                printf("\nEncerrando...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while(opcao != 0);

    return 0;
}
