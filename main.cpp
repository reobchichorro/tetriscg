#include <GL/glut.h>
#include <iostream>
#include "Menu.cpp"
#include "Tetris.h"

//variáveis gllobais de janela

GLfloat win=250, r, g, b;
GLint view_w, view_h;

//variaveis do jogo
int estadoJogo = 1; //0 = Menu ; 1 = Jogo; 2 = Perdeu;
const int possiveisRotacoes[] = {0,90,180,270};
const int larguraJogo = 16;
const int alturaMaximaJogo = 20;
Tetris jogo(larguraJogo);
Tetris jogoComPecaCaindo(larguraJogo);
int alturaPecaAtual=alturaMaximaJogo;
char idPecaAtual;
int posicaoPecaAtual,rotacaoPecaAtual;

// Funcao callback chamada para fazer o desenho
void Desenha(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();
    if(estadoJogo == 0) //desenha o menu
    {

    }
    else //desenha o jogo atual
    {
        //desenha o background do jogo
        glColor3f (0.3, 0.3, 0.3);
        
        glBegin(GL_POLYGON);
            glVertex2f(0.0,0.0);
            glVertex2f(1.0,0.0);
            glVertex2f(1.0,1.0);
            glVertex2f(0.0,1.0);
        glEnd();
    }

    glutSwapBuffers();
    glFlush();
}


// Inicializa par�metros de rendering
void init (void)
{   
    // Define a cor de fundo da janela de visualiza��o como branca
    glClearColor(1.0, 1.0, 1.0, 0.0);
    win = 1000;
}

// Fun��o callback chamada quando o tamanho da janela � alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{ 
    // Especifica as dimens�es da Viewport
    glViewport(0, 0, w, h);
    view_w = w;
    view_h = h;                   

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();

  	// Estabelece volume de visualiza��o 
    // (esquerda, direita, inferior, superior)
  	gluOrtho2D (-win, win, -win, win);
}

void teclado(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 27:
            //limpa jogo atual
            estadoJogo = 0; //volta pro menu
        break;
    }

}

void teclas_especiais(int key, int x, int y)
{
    if(estadoJogo == 0)
    {
        //trata o menu
        switch(key)
        {
            case GLUT_KEY_RIGHT :
                //seleciona uma opção do lado (se houver)
            break;
            case GLUT_KEY_LEFT :
                //seleciona uma opção do lado (se houver)
            break;
            case GLUT_KEY_UP :
                //vai pra opção de cima
            break;
            case GLUT_KEY_DOWN :
                //vai pra opção de baixo;
            break;
        }
    }
    else //movimenta as peças do jogo
    {
        switch(key)
        {
            case GLUT_KEY_RIGHT :
                //move peça pra direita
            break;
            case GLUT_KEY_LEFT :
                //move peça pra esquerda
            break;
            case GLUT_KEY_UP :
                //roda a peça
            break;
            case GLUT_KEY_DOWN :
                //faz peça descer mais rapido
            break;
        }
    }
    
}

// Programa Principal 
int main(int argc, char** argv)
{
    //inicialização das variaveis do jogo
    idPecaAtual = "IJLOSTZ"[rand()%7];
	posicaoPecaAtual = larguraJogo/2-2;
	alturaPecaAtual = alturaMaximaJogo;
	rotacaoPecaAtual = 0;
    
    //inicialização openGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);     
    glutInitWindowSize(400,600);
    //glutInitWindowPosition(200,100);
    glutCreateWindow("Tetris");
    //glutReshapeFunc(AlteraTamanhoJanela);
    glutDisplayFunc(Desenha);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(teclas_especiais);

    init();
    glutMainLoop();
}
