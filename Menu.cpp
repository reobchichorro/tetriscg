#include <GL/glut.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <string>

std::string texto;
GLfloat win;
GLint view_w, view_h;

GLint l=100, h=40, ldiff=10, hdiff=20;
GLint ll3 = (3*l + 2*ldiff)/2, ll2 = (2*l + ldiff)/2;

//estrutura de dados que repsenta o menu
struct Menu {
    int linha=0;
    int coluna[6] = {0,0,0,0,0,0};
    const int maxMenu[6] = {1,3,3,3,2,1};
};

Menu omenu;

void DesenhaRet(void) {

    // Define a cor corrente
    glColor3f(0.0,1.0,0.0);

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
            if(omenu.coluna[i]==j && (i > 0 && i < 5))
                glColor3f(0.0,0.0,1.0);
            else
                glColor3f(0.0,1.0,0.0);
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

    GLint offset = 4;

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
}

//funções de tratamento das opções do menu deverão estar aqui
void opcao_menu(int opcao, int x, int y) {
    switch(opcao)
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
            omenu.linha--;
            if(omenu.linha<0)
                omenu.linha=5;
        break;
        case GLUT_KEY_DOWN:
            omenu.linha++;
            if(omenu.linha>=6)
                omenu.linha=0;
        break;
    }
    glutPostRedisplay();
}

void opcao_menu2(unsigned char opcao, int x, int y) {
    switch(opcao)
    {
        case 13: //sair
            if(omenu.linha==5)
                exit(0);
            // else if(omenu.linha==0)
                //initgame
        break;
    }
    glutPostRedisplay();
}

// Desenha um texto na janela GLUT
void DesenhaTexto(std::string& texto)
{
    auto it = texto.begin();
  	glPushMatrix();
        // Posi��o no universo onde o texto ser� colocado
        glRasterPos2f(-win,win-(win*0.08));
        // Exibe caracter a caracter
        while(it != texto.end())
             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,*it++);
	glPopMatrix();
}

// Fun��o callback chamada para fazer o desenho
void Desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    DesenhaRet();

    // Exibe a posi��o do mouse na janela
    glColor3f(0.0f,0.0f,0.0f);
    DesenhaTexto(texto);

    glutSwapBuffers();
}

// Inicializa par�metros de rendering
void Inicializa (void)
{
    // Define a cor de fundo da janela de visualiza��o como branca
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    win=250.0f;
    texto = "(0,0)";

    // CriaMenu();

}

// Fun��o callback chamada sempre que o mouse � movimentado
// sobre a janela GLUT com um bot�o pressionado
void MouseBotaoPressionado(int button, int state, int x, int y)
{
    if(button != GLUT_LEFT_BUTTON) return;
    texto = "Botao pressionado (" + std::to_string(x) + "," + std::to_string(y) + ")";

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
                // else if(i==0)
                    //initgame
                else {
                    omenu.linha = i;
                    omenu.coluna[i] = j;
                }
            }
        }
    }

    glutPostRedisplay();
}

// Fun��o callback chamada sempre que o mouse � movimentado
// sobre a janela GLUT
void MoveMouse(int x, int y)
{
    texto = "(" + std::to_string(x) + "," + std::to_string(y) + ")";
    glutPostRedisplay();
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

  	gluOrtho2D (-win, win, -win, win);
    

  	glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        glutInitWindowSize(500,500);
        glutInitWindowPosition(10,10);
        glutCreateWindow("Exemplo de Menu");
        glutDisplayFunc(Desenha);
        glutReshapeFunc(ChangeSize);
        glutMouseFunc(MouseBotaoPressionado);
        glutPassiveMotionFunc(MoveMouse);
        glutSpecialFunc(opcao_menu);
        glutKeyboardFunc(opcao_menu2);
        Inicializa();
    glutMainLoop();
}
