# tetriscg

Alunos:
    Rodrigo Eduardo de Oliveira Bauer Chichorro - 92535
    Wallace Ferancini Rosa - 92545


Sobre o menu (apagar depois):

O menu é definido por um struct:

struct Menu {
    int linha=0;
    int coluna[6] = {0,0,0,0,0,0};
    int select[6] = {0,0,0,0,0,0};
    const int maxMenu[6] = {1,3,3,3,2,1};
};

As variáveis linha, coluna e maxMenu são irrelevantes para a integração com o Jogo.
A variável select contém as opções escolhidas pelo jogador ao início do jogo:
    Posição 0: irrelevante
    Posição 1 - Velocidade: 0 - normal, 1 - rápido, 2 - turbo;
    Posição 2 - Tamanho: 0 - 20x10, 1 - 30x15, 2 - 50x25;
    Posição 3 - Cores: 0 - Cores1, 1 - Cores2, 2 - Cores3;
    Posição 4 - Modo: 0 - normal, 1 - bêbado;
    Posição 5: irrelevante

Menu omenu;

omenu é a variável da struct Menu que conterá as informações.
Assim, basta acessar omenu.select[index] para resgatar a configuração do jogador.
