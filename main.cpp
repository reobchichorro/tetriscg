// Interaction.c
// Marcus Vin�cius A. Andrade

#include <GL/glut.h>
#include "Tetris.h"
#include "INF390.h"
#include <iostream>
using namespace std;

//variaveis globais da janela
float win=250;
int view_w, view_h;
double scale_x = 1, scale_y = 1;
GLint l=100, h=40, ldiff=10, hdiff=20;
GLint ll3 = (3*l + 2*ldiff)/2, ll2 = (2*l + ldiff)/2;

//variaveis de menu
float cor_background[3] = {0.3, 0.3, 0.3};
float cor_quadrado[3] = {1.0, 0.3, 0.3};
float contorno_quadrado[3] = {1.0, 1.0, 1.0};


//variaveis globias de jogo
unsigned int estadoJogo = 0; //0 == Menu, 1 == Jogo, 2 == Perdeu
const int possiveisRotacoes[] = {0,90,180,270};
int larguraJogo = 10;
int alturaMaximaJogo = 20;
int velocidade = 100; //velocidade com que as pessas caem em ms
Tetris jogo(larguraJogo);
Tetris jogoComPecaCaindo(larguraJogo);
bool bebado = false; //modo bêbado
int rot = 0; //modo bebado
int alturaPecaAtual=alturaMaximaJogo;
char idPecaAtual;
int posicaoPecaAtual,rotacaoPecaAtual;
int ultimatecla = -1; //0 == espaco, 1 == left, 2 == right, 3 == baixo

//estrutura de dados que repsenta o menu
struct Menu {
    int linha=0;
    int coluna[6] = {0,0,0,0,0,0};
    int select[6] = {0,0,0,0,0,0};
    const int maxMenu[6] = {1,3,3,3,2,1};
};

Menu omenu;

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
    
    if(estadoJogo == 0)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        gluOrtho2D (-win, win, -win, win);
        

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        // Define a cor corrente
        glColor3f(cor_background[0],cor_background[1],cor_background[2]);

        GLint baixo, cima;
        GLint esq, dir;
        for(int i=0; i<6; i++) {
            baixo = hdiff/2 + (2-i)*(hdiff+h), cima = baixo + h;
            for(int j=0; j<omenu.maxMenu[i]; j++) {
                if(i > 0 && i < 4) {
                    esq = -1*ll3 + j*(ldiff+l); dir = esq + l;
                } else if(i == 4) {
                    esq = -1*ll2 + j*(ldiff+l); dir = esq + l;
                } else {
                    dir = l/2; esq = -1*dir;
                }
                if(omenu.select[i]==j && (i > 0 && i < 5))
                    glColor3f(cor_quadrado[0],cor_quadrado[1],cor_quadrado[2]);
                else
                    glColor3f(cor_background[0],cor_background[1],cor_background[2]);
                glBegin(GL_POLYGON);
                    glVertex2i(esq, baixo);
                    glVertex2i(esq, cima);
                    glVertex2i(dir, cima);
                    glVertex2i(dir, baixo);
                glEnd();
            }
        }

        glColor3f(1.0,0.0,0.0);
        glLineWidth(2.0);
        baixo = hdiff/2 - 2 + (2-omenu.linha)*(hdiff+h), cima = baixo + h + 4;
        if(omenu.linha > 0 && omenu.linha < 4) {
            esq = -1*ll3 + omenu.coluna[omenu.linha]*(ldiff+l) - 2; dir = esq + l + 4;
        } else if(omenu.linha == 4) {
            esq = -1*ll2 + omenu.coluna[4]*(ldiff+l) - 2; dir = esq + l + 4;
        } else {
            dir = l/2 + 2; esq = -1*dir;
        }
        glBegin(GL_LINE_LOOP);
            glVertex2i(esq, baixo);
            glVertex2i(esq, cima);
            glVertex2i(dir, cima);
            glVertex2i(dir, baixo);
        glEnd();

        std::string menutxt;
        glColor3f(1.0f,0.0f,0.0f);

        GLint offset = 4, xoffset=20;

        for(int i=0; i<4; i++) {
            if(i==0) {
                menutxt = "VELOCIDADE:";
            } else if(i==1) {
                menutxt = "TAMANHO:";
            } else if(i==2) {
                menutxt = "CORES:";
            } else {
                menutxt = "MODO:";
            }
            baixo = (2-i)*(hdiff+h);
            auto it = menutxt.begin();
            glPushMatrix();
                glRasterPos2f(-40.0,baixo-offset);
                // std::cerr << -40.0 << " " << 2*hdiff+2*h << std::endl;
                while(it != menutxt.end())
                    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,*it++);
            glPopMatrix();
        }

        glColor3f(contorno_quadrado[0],contorno_quadrado[1],contorno_quadrado[2]);
        for(int i=0; i<6; i++) {
            baixo = (hdiff+h)/2;
            baixo += (2-i)*(hdiff+h);

            for(int j=0; j<omenu.maxMenu[i]; j++) {
                if(i==0) {
                    menutxt = "INICIAR";
                } else if(i==1) {
                    if(j==0)
                        menutxt = "NORMAL";
                    else if(j==1)
                        menutxt = "RAPIDO";
                    else
                        menutxt = "TURBO";
                } else if(i==2) {
                    if(j==0)
                        menutxt = "20x10";
                    else if(j==1)
                        menutxt = "30x15"; 
                    else
                        menutxt = "50x25";
                } else if(i==3) {
                    menutxt = "Cores" + std::to_string(j+1);
                } else if(i==4) {
                    if(j==0)
                        menutxt = "NORMAL";
                    else
                        menutxt = "BEBADO";
                } else {
                    menutxt = "SAIR";
                }
                if(i > 0 && i < 4)
                    esq = -1*ll3 + j*(ldiff+l);
                else if(i == 4)
                    esq = -1*ll2 + j*(ldiff+l);
                else
                    esq = -1*l/2;
                auto it = menutxt.begin();
                glPushMatrix();
                    glRasterPos2f(esq+xoffset,baixo-offset);
                    // std::cerr << -40.0 << " " << 2*hdiff+2*h << std::endl;
                    while(it != menutxt.end())
                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,*it++);
                glPopMatrix();
            }
        }
    }
    else if(estadoJogo == 1)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        gluOrtho2D ((-larguraJogo/2), (3*larguraJogo/2), 0, alturaMaximaJogo);


        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        // Desenha o back ground do jogo
        glScalef(scale_x, scale_y, 0);
        glColor3f(cor_background[0], cor_background[1], cor_background[2]);
        if(bebado){glTranslatef(larguraJogo/2,alturaMaximaJogo/2,0); glRotatef(rot,0.0,0.0,1.0); glTranslatef(-larguraJogo/2,-alturaMaximaJogo/2,0);} 
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
                    if(bebado) {glTranslatef(0.5,0.5,0); glRotatef(rot,0.0,0.0,1.0); glTranslatef(-0.5,-0.5,0);}
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
        if(bebado) rot+=5;

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
    if(estadoJogo == 0)
    {
        switch(key)
        {
            case 13: //sair
                if(omenu.linha==5)
                    exit(0);
                else if(omenu.linha==0)
                    estadoJogo = 1;
                else if(omenu.linha==1) // velocidade
                {
                    omenu.select[omenu.linha] = omenu.coluna[omenu.linha];
                    if(omenu.select[omenu.linha] == 0)
                        velocidade = 100;
                    else if(omenu.select[omenu.linha] == 1)
                        velocidade = 50;
                    else
                        velocidade = 30;
                }
                else if(omenu.linha==2) //tamanho do jogo
                {
                    omenu.select[omenu.linha] = omenu.coluna[omenu.linha];
                    if(omenu.select[omenu.linha] == 0)
                    {
                        alturaMaximaJogo = 20;
                        larguraJogo = 10;
                    }
                    else if(omenu.select[omenu.linha] == 1)
                    {
                        alturaMaximaJogo = 30;
                        larguraJogo = 15;
                    }
                    else
                    {
                        alturaMaximaJogo = 50;
                        larguraJogo = 25;
                    }
                }
                else if(omenu.linha == 3) //cores
                {
                    omenu.select[omenu.linha] = omenu.coluna[omenu.linha];
                    if(omenu.select[omenu.linha] == 0)
                    {
                        cor_background[0] = 0.3;
                        cor_background[1] = 0.3;
                        cor_background[2] = 0.3;
                        
                        cor_quadrado[0] = 1.0;
                        cor_quadrado[1] = 0.3;
                        cor_quadrado[2] = 0.3;
                        
                        contorno_quadrado[0] = 1.0;
                        contorno_quadrado[1] = 1.0;
                        contorno_quadrado[2] = 1.0;
                    }
                    else if(omenu.select[omenu.linha] == 1)
                    {
                        cor_background[0] = 0.0;
                        cor_background[1] = 0.59;
                        cor_background[2] = 0.3;
                        
                        cor_quadrado[0] = 0.3;
                        cor_quadrado[1] = 0.3;
                        cor_quadrado[2] = 0.6;
                        
                        contorno_quadrado[0] = 0.0;
                        contorno_quadrado[1] = 0.0;
                        contorno_quadrado[2] = 0.0;
                    }
                    else
                    {
                        cor_background[0] = 0.275;
                        cor_background[1] = 0.153;
                        cor_background[2] = 0.349;
                        
                        cor_quadrado[0] = 0.831;
                        cor_quadrado[1] = 0.686;
                        cor_quadrado[2] = 0.216;
                        
                        contorno_quadrado[0] = 0.0;
                        contorno_quadrado[1] = 0.0;
                        contorno_quadrado[2] = 0.0;
                    }
                }
                else if(omenu.linha == 4)
                {
                    omenu.select[omenu.linha] = omenu.coluna[omenu.linha];
                    if(omenu.select[omenu.linha] == 0)
                        bebado = false;
                    else
                        bebado = true;
                }
            break;
        }
    }
    else if(estadoJogo == 1)
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
    else if(estadoJogo == 2)
    {
        if(key == 27) estadoJogo=0;
    }
        
    //glutPostRedisplay();
	
}


// Callback para gerenciar eventos do mouse
void HandleMouse(int button, int state, int x, int y)
{
    if(estadoJogo == 0)
    {
        if(button != GLUT_LEFT_BUTTON) return;
        //texto = "Botao pressionado (" + std::to_string(x) + "," + std::to_string(y) + ")";

        x -= 250; y = 250 - y;

        GLint baixo, cima;
        GLint esq, dir;
        bool found = false;
        for(int i=0; i<6 && !found; i++) {
            baixo = hdiff/2 + (2-i)*(hdiff+h), cima = baixo + h;
            for(int j=0; j<omenu.maxMenu[i] && !found; j++) {
                if(i > 0 && i < 4) {
                    esq = -1*ll3 + j*(ldiff+l); dir = esq + l;
                } else if(i == 4) {
                    esq = -1*ll2 + j*(ldiff+l); dir = esq + l;
                } else {
                    dir = l/2; esq = -1*dir;
                }
                if(esq <= x && x <= dir && baixo <= y && y <= cima) {
                    found = true;
                    if(i==5)
                        exit(0);
                    else if(i==0)
                        estadoJogo = 1;
                    else {
                        omenu.linha = i;
                        omenu.select[i] = j;
                        omenu.coluna[i] = j;
                        if(omenu.linha==1) // velocidade
                        {
                            if(omenu.select[omenu.linha] == 0)
                                velocidade = 100;
                            else if(omenu.select[omenu.linha] == 1)
                                velocidade = 50;
                            else
                                velocidade = 30;
                        }
                        else if(omenu.linha==2) //tamanho do jogo
                        {
                            if(omenu.select[omenu.linha] == 0)
                            {
                                alturaMaximaJogo = 20;
                                larguraJogo = 10;
                            }
                            else if(omenu.select[omenu.linha] == 1)
                            {
                                alturaMaximaJogo = 30;
                                larguraJogo = 15;
                            }
                            else
                            {
                                alturaMaximaJogo = 50;
                                larguraJogo = 25;
                            }
                        }
                        else if(omenu.linha == 3) //cores
                        {
                            if(omenu.select[omenu.linha] == 0)
                            {
                                cor_background[0] = 0.3;
                                cor_background[1] = 0.3;
                                cor_background[2] = 0.3;
                                
                                cor_quadrado[0] = 1.0;
                                cor_quadrado[1] = 0.3;
                                cor_quadrado[2] = 0.3;
                                
                                contorno_quadrado[0] = 1.0;
                                contorno_quadrado[1] = 1.0;
                                contorno_quadrado[2] = 1.0;
                            }
                            else if(omenu.select[omenu.linha] == 1)
                            {
                                cor_background[0] = 0.0;
                                cor_background[1] = 0.59;
                                cor_background[2] = 0.3;
                                
                                cor_quadrado[0] = 0.3;
                                cor_quadrado[1] = 0.3;
                                cor_quadrado[2] = 0.6;
                                
                                contorno_quadrado[0] = 0.0;
                                contorno_quadrado[1] = 0.0;
                                contorno_quadrado[2] = 0.0;
                            }
                            else
                            {
                                cor_background[0] = 0.275;
                                cor_background[1] = 0.153;
                                cor_background[2] = 0.349;
                                
                                cor_quadrado[0] = 0.831;
                                cor_quadrado[1] = 0.686;
                                cor_quadrado[2] = 0.216;
                                
                                contorno_quadrado[0] = 0.0;
                                contorno_quadrado[1] = 0.0;
                                contorno_quadrado[2] = 0.0;
                            }
                        }
                        else if(omenu.linha == 4)
                        {
                            if(omenu.select[omenu.linha] == 0)
                                bebado = false;
                            else
                                bebado = true;
                        }
                    }
                }
            }
        }
    }
}

void MoveMouse(int x, int y)
{
    if(estadoJogo !=0) return;
    x -= 250; y = 250 - y;

    GLint baixo, cima;
    GLint esq, dir;
    bool found = false;
    for(int i=0; i<6 && !found; i++) {
        baixo = hdiff/2 + (2-i)*(hdiff+h), cima = baixo + h;
        for(int j=0; j<omenu.maxMenu[i] && !found; j++) {
            if(i > 0 && i < 4) {
                esq = -1*ll3 + j*(ldiff+l); dir = esq + l;
            } else if(i == 4) {
                esq = -1*ll2 + j*(ldiff+l); dir = esq + l;
            } else {
                dir = l/2; esq = -1*dir;
            }
            if(esq <= x && x <= dir && baixo <= y && y <= cima) {
                found = true;
                omenu.linha = i;
                omenu.coluna[i] = j;
            }
        }
    }
    glutPostRedisplay();
}


// Callback para gerenciar eventos do teclado para teclas 
// especiais, SETA_
void SpecialKeys(int key, int x, int y)
{
    if(estadoJogo == 0)
    {
        switch(key)
        {
            case GLUT_KEY_LEFT:
                omenu.coluna[omenu.linha]--;
                if(omenu.coluna[omenu.linha]<0)
                    omenu.coluna[omenu.linha] = omenu.maxMenu[omenu.linha]-1;
            break;
            case GLUT_KEY_RIGHT:
                omenu.coluna[omenu.linha]++;
                if(omenu.coluna[omenu.linha]>=omenu.maxMenu[omenu.linha])
                    omenu.coluna[omenu.linha] = 0;
            break;
            case GLUT_KEY_UP:
                omenu.coluna[omenu.linha] = omenu.select[omenu.linha];
                omenu.linha--;
                if(omenu.linha<0)
                    omenu.linha=5;
            break;
            case GLUT_KEY_DOWN:
                omenu.coluna[omenu.linha] = omenu.select[omenu.linha];
                omenu.linha++;
                if(omenu.linha>=6)
                    omenu.linha=0;
            break;
        }
    }
    else if(estadoJogo == 1)
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
        glutPassiveMotionFunc(MoveMouse);
        glutSpecialFunc(SpecialKeys);
        init();
    glutTimerFunc(velocidade,loop_peca_caindo, 1);
    glutMainLoop();
		
	return 0;
}

