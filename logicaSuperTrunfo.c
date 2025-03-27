#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_CARTAS 7

typedef struct {
    char nome[20];
    int populacao;
    int area;
    int pib;
} Carta;

void embaralhar(Carta *cartas, int tamanho) {
    for (int i = tamanho - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Carta temp = cartas[i];
        cartas[i] = cartas[j];
        cartas[j] = temp;
    }
}

void exibirCarta(Carta carta) {
    printf("-------------------------\n");
    printf("País: %s\n", carta.nome);
    printf("1 - População: %d milhões\n", carta.populacao);
    printf("2 - Área: %d mil km²\n", carta.area);
    printf("3 - PIB: %d bilhões USD\n", carta.pib);
    printf("-------------------------\n");
}

void jogarRodada(Carta *jogador1, Carta *jogador2, int *tam1, int *tam2) {
    if (*tam1 == 0 || *tam2 == 0) return;

    Carta cartaJogador = jogador1[0];
    Carta cartaAdversario = jogador2[0];

    printf("Sua carta:\n");
    exibirCarta(cartaJogador);
    
    int escolha;
    do {
        printf("Escolha um atributo (1 - População, 2 - Área, 3 - PIB): ");
        scanf("%d", &escolha);
    } while (escolha < 1 || escolha > 3);
    
    int valorJogador = (escolha == 1) ? cartaJogador.populacao : (escolha == 2) ? cartaJogador.area : cartaJogador.pib;
    int valorAdversario = (escolha == 1) ? cartaAdversario.populacao : (escolha == 2) ? cartaAdversario.area : cartaAdversario.pib;
    
    printf("Carta do adversário:\n");
    exibirCarta(cartaAdversario);
    
    if (valorJogador > valorAdversario) {
        printf("Você venceu esta rodada!\n");
        for (int i = 0; i < *tam1 - 1; i++) jogador1[i] = jogador1[i + 1];
        jogador1[*tam1 - 1] = cartaJogador;
        jogador1[*tam1] = cartaAdversario;
        (*tam1)++;
        (*tam2)--;
    } else {
        printf("Você perdeu esta rodada!\n");
        for (int i = 0; i < *tam2 - 1; i++) jogador2[i] = jogador2[i + 1];
        jogador2[*tam2 - 1] = cartaAdversario;
        jogador2[*tam2] = cartaJogador;
        (*tam2)++;
        (*tam1)--;
    }
    printf("Cartas restantes - Você: %d | Adversário: %d\n", *tam1, *tam2);
}

int main() {
    srand(time(NULL));

    Carta cartas[NUM_CARTAS] = {
        {"Brasil", 213, 8516, 1445},
        {"EUA", 331, 9834, 21433},
        {"China", 1441, 9597, 14342},
        {"Alemanha", 83, 357, 3845},
        {"Japão", 126, 378, 5065},
        {"França", 67, 551, 2715},
        {"Índia", 1380, 3287, 2875}
    };

    embaralhar(cartas, NUM_CARTAS);

    int metade = NUM_CARTAS / 2;
    Carta jogador1[NUM_CARTAS], jogador2[NUM_CARTAS];
    int tam1 = metade, tam2 = NUM_CARTAS - metade;

    memcpy(jogador1, cartas, tam1 * sizeof(Carta));
    memcpy(jogador2, cartas + tam1, tam2 * sizeof(Carta));

    int turno = 0;
    while (tam1 > 0 && tam2 > 0) {
        printf("=== Rodada %d ===\n", turno + 1);
        jogarRodada(jogador1, jogador2, &tam1, &tam2);
        turno++;
    }

    if (tam1 > 0)
        printf("Parabéns! Você venceu o jogo!\n");
    else
        printf("O adversário venceu o jogo!\n");

    return 0;
