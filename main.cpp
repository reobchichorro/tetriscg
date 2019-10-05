// Interaction.c
// Marcus Vin�cius A. Andrade

#include <GL/glut.h>
#include "Menu.cpp"
#include "Tetris.h"
#include "INF390.h"
#include <iostream>
using namespace std;

//variaveis globais da janela
float win=250;
int ortho_w = 0, ortho_h = 0;
int view_w, view_h;
double scale_x = 1, scale_y = 1;

//variaveis de menu
float cor_background[3] = {0.3, 0.3, 0.3};
float cor_quadrado[3] = {0.0, 0.0, 1.0};
float contorno_quadrado[3] = {1.0, 1.0, 1.0};


//variaveis globias de jogo
unsigned int estadoJogo = 1; //0 == Menu, 1 == Jogo, 2 == Perdeu
const int possiveisRotacoes[] = {0,90,180,270};
const int larguraJogo = 8;
const int alturaMaximaJogo = 20;
int velocidade = 33; //velocidade com que as pessas caem em ms
Tetris jogo(larguraJogo);
Tetris jogoComPecaCaindo(larguraJogo);

int alturaPecaAtual=alturaMaximaJogo;
char idPecaAtual;
int posicaoPecaAtual,rotacaoPecaAtual;
int ultimatecla = -1; //0 == espaco, 1 == left, 2 == right, 3 == baixo

void loop_peca_caindo(int value)
{
    if(estadoJogo == 0)
    {
        //inicia o jogo
        jogo = Tetris(larguraJogo);
        jogoComPecaCaindo = Tetris(larguraJogo);
        alturaPecaAtual = alturaMaximaJogo;
        ultimatecla = -1;
        idPecaAtual = "IJLOSTZ"[rand()%7];
        posicaoPecaAtual = larguraJogo/2-2;
        alturaPecaAtual = alturaMaximaJogo;
        rotacaoPecaAtual = 0;

    }
    else if(estadoJogo==1) //moviumento das peças
    {
        jogoComPecaCaindo = jogo;

        Tetris jogoTeste = jogoComPecaCaindo;
        switch(ultimatecla)
        {
            case 0 : 
                            
                if(jogoTeste.adicionaForma(posicaoPecaAtual,alturaPecaAtual,idPecaAtual, possiveisRotacoes[(rotacaoPecaAtual+1)%4]))
                    rotacaoPecaAtual = (rotacaoPecaAtual+1)%4;
            break;
            case 1 : //esquerda 			
                if(jogoTeste.adicionaForma(posicaoPecaAtual-1,alturaPecaAtual,idPecaAtual, possiveisRotacoes[rotacaoPecaAtual]))
                    posicaoPecaAtual--;
            break;
            case 2 : //direita 			
                if(jogoTeste.adicionaForma(posicaoPecaAtual+1,alturaPecaAtual,idPecaAtual, possiveisRotacoes[rotacaoPecaAtual]))
                    posicaoPecaAtual++;
            break;

        }
        ultimatecla = -1;
        if(jogoComPecaCaindo.adicionaForma(posicaoPecaAtual,alturaPecaAtual-1,idPecaAtual, possiveisRotacoes[rotacaoPecaAtual])) {
                alturaPecaAtual--;
        }
        else {
            //adiciona a peca a posicao onde ela ficara fixada
            if(jogo.adicionaForma(posicaoPecaAtual,alturaPecaAtual,idPecaAtual, possiveisRotacoes[rotacaoPecaAtual]))
                jogoComPecaCaindo = jogo;
            else //não é possível adicionar mais peças, GAME OVER
            {
                estadoJogo=2;
                glutPostRedisplay();
                return;
            }
            //sorteia uma nova peca, define a altura como sendo o topo da tela, etc...
            idPecaAtual = "IJLOSTZ"[rand()%7];
            posicaoPecaAtual = larguraJogo/2-2;
            alturaPecaAtual = alturaMaximaJogo;
            rotacaoPecaAtual = rand()%4;
            jogoComPecaCaindo.removeLinhasCompletas();	
            jogo = jogoComPecaCaindo;	
        }
    }
    
    
    glutPostRedisplay();
    glutTimerFunc(velocidade,loop_peca_caindo, 1);
}

void DesenhaTexto(char *string) 
{  
  	
        // Posi��o no universo onde o texto ser� colocado          
        //glRasterPos2f(0,alturaMaximaJogo/2);
        //glScalef(4,4,0);
         
        // Exibe caracter a caracter
        while(*string)
             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,*string++); 
	
}

// Chamada para fazer o desenho
void RenderScene(void)
{
    // Limpa a janela
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    if(estadoJogo == 1)
    {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        // Desenha o back ground do jogo
        glScalef(scale_x, scale_y, 0);
        glColor3f(cor_background[0], cor_background[1], cor_background[2]);
        glBegin(GL_POLYGON);
            glVertex2f(0,0);
            glVertex2f(larguraJogo,0);
            glVertex2f(larguraJogo,alturaMaximaJogo);
            glVertex2f(0,alturaMaximaJogo);
        glEnd();

        
        //Desenha as peças do jogo
        for(int i=0;i<alturaMaximaJogo;i++) {
		    
		    for(int j=0;j<larguraJogo;j++) {
                float x = j, y = alturaMaximaJogo-i-1;
                char pos = jogoComPecaCaindo.get(j,alturaMaximaJogo-i-1);
                if(pos != ' ')
                {
                    //contorno do quadrado
                    glPushMatrix();
                    glScalef(scale_x, scale_y, 0);
                    glColor3f (contorno_quadrado[0], contorno_quadrado[1], contorno_quadrado[2]);
                    glTranslatef(x,y,0);
                    glLineWidth(2);
                    glBegin(GL_LINE_LOOP);
                        glVertex2f(0,0);
                        glVertex2f(1,0);
                        glVertex2f(1,1);
                        glVertex2f(0,1);
                    glEnd();
                    //quadrado
                    glColor3f (cor_quadrado[0], cor_quadrado[1], cor_quadrado[2]);
                    glBegin(GL_POLYGON);
                        glVertex2f(0,0);
                        glVertex2f(1,0);
                        glVertex2f(1,1);
                        glVertex2f(0,1);
                    glEnd();
                    glPopMatrix();
                    
                }
		    }
		    
        }

    }
    else if(estadoJogo == 2)
    {
        //tela de GAME OVER
        glPushMatrix();
        glLoadIdentity();
        glColor3f (1.0, 0.0, 0.0);
        glTranslatef(-0.5,alturaMaximaJogo/2,0);
        glScalef(0.01,0.01,0);
        INF390::texto("GAME OVER",1,1,1,1);
        glPopMatrix();            
    }
    
    //Desenha as peças do jogo
    glutSwapBuffers();
}


// Inicializa��o
void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
}


// Chamada pela GLUT quando a janela � redimensionada
void ChangeSize(GLsizei w, GLsizei h)
{
  	// Especifica o tamanho da viewport
    view_w = w;
  	view_h = h;
    glViewport(0, 0, w, h);
    
    // Inicializa sistema de coordenadas
  	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();

  	// Estabelece volume de visualiza��o 
    // (esquerda, direita, inferior, superior)
    if(estadoJogo == 1 || estadoJogo==2)
    {
        gluOrtho2D ((-larguraJogo/2), (3*larguraJogo/2), 0, alturaMaximaJogo);
    }
    

  	glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();
}


// Callback para gerenciar eventos de teclado
void HandleKeyboard(unsigned char key, int x, int y)
{
    if(estadoJogo == 1)
    {
        switch (key) {
		case 27 : //ESC
            cout << "ESTADO DO JOGO : MENU\n"; 
            estadoJogo = 0;
            //volta pro menu
        break;
        case ' ':
            ultimatecla = 0;
        break;
	    }
    }
    //glutPostRedisplay();
	
}


// Callback para gerenciar eventos do mouse
void HandleMouse(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON){
		if (state == GLUT_DOWN) {
            
            cout << "x = " << x << "  y = " << y << "(View_h, View_w) = (" << view_h << ", " << view_w << ")" << endl;
						// Troca o tamanho do ret�ngulo, que vai do 
						// centro da janela at� a posi��o onde o usu�rio 
						// clicou com o mouse
		}
    }
	
}


// Callback para gerenciar eventos do teclado para teclas 
// especiais, SETA_
void SpecialKeys(int key, int x, int y)
 {
    if(estadoJogo == 1)
    {

        if(key == GLUT_KEY_RIGHT) {
            //move peça pra direita
            ultimatecla = 2;
            
		}
        else if(key == GLUT_KEY_LEFT) {
			//move peça pra esquerda
            ultimatecla = 1;
            
		}
        
    }
		
        
    //glutPostRedisplay();
  }




// Programa Principal
int main(int argc, char** argv)
{
    //inicialização jogo
    idPecaAtual = "IJLOSTZ"[rand()%7];
	posicaoPecaAtual = larguraJogo/2-2;
	alturaPecaAtual = alturaMaximaJogo;
	rotacaoPecaAtual = 0;

    //inicialização openGL
    //loop_peca_caindo();
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutCreateWindow("Tetris");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(HandleKeyboard);
	glutMouseFunc(HandleMouse);
	glutSpecialFunc(SpecialKeys);
	init();
    glutTimerFunc(velocidade,loop_peca_caindo, 1);
    glutMainLoop();
		
	return 0;
}

