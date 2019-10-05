#include <GL/glut.h>
#include <iostream>
#include <string.h>
#include <stdio.h>


char texto[30];
GLfloat win;
GLint view_w, view_h;

//estrutura de dados que repsenta o menu
struct Menu {
    int linha=0;
    int coluna[6] = {0,0,0,0,0,0};
    const int maxMenu[6] = {1,3,3,3,2,1};
};

Menu omenu;

//funções de tratamento das opções do menu deverão estar aqui
void opcao_menu(int opcao, int x, int y)
{
    switch(opcao)
    {
        case 8 : //sair
            exit(0);
        break;
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
}

void DesenhaRet(void) {

    // glBegin(GL_POLYGON);
    //         glVertex2f(-160.0f, -180.0f);
    //         glVertex2f(-160.0f, 180.0f);
    //         glVertex2f(160.0f, 180.0f);
    //         glVertex2f(160.0f, -180.0f);
    //  glEnd();
    GLint l=100, h=40, ldiff=10, hdiff=20;
    GLint ll3 = (3*l + 2*ldiff)/2, ll2 = (2*l + ldiff)/2;
    glBegin(GL_POLYGON);
        glVertex2i(-1*l/2, hdiff/2 + 2*hdiff + 3*h);
        glVertex2i(-1*l/2, hdiff/2 + 2*hdiff + 2*h);
        glVertex2i(l/2, hdiff/2 + 2*hdiff + 2*h);
        glVertex2i(l/2, hdiff/2 + 2*hdiff + 3*h);
    glEnd();
    for(int i=0; i<3; i++) {
        GLint esq = -1*ll3 + i*(ldiff+l), dir = esq + l;
        glBegin(GL_POLYGON);
            glVertex2i(esq, hdiff + hdiff/2 + h);
            glVertex2i(esq, hdiff + hdiff/2 + 2*h);
            glVertex2i(dir, hdiff + hdiff/2 + 2*h);
            glVertex2i(dir, hdiff + hdiff/2 + h);
        glEnd();
    }
    for(int i=0; i<3; i++) {
        GLint esq = -1*ll3 + i*(ldiff+l), dir = esq + l;
        glBegin(GL_POLYGON);
            glVertex2i(esq, hdiff/2);
            glVertex2i(esq, hdiff/2 + h);
            glVertex2i(dir, hdiff/2 + h);
            glVertex2i(dir, hdiff/2);
        glEnd();
    }
    for(int i=0; i<3; i++) {
        GLint esq = -1*ll3 + i*(ldiff+l), dir = esq + l;
        glBegin(GL_POLYGON);
            glVertex2i(esq, -1*hdiff/2);
            glVertex2i(esq, -1*hdiff/2 - h);
            glVertex2i(dir, -1*hdiff/2 - h);
            glVertex2i(dir, -1*hdiff/2);
        glEnd();
    }
    for(int i=0; i<2; i++) {
        GLint esq = -1*ll2 + i*(ldiff+l), dir = esq + l;
        glBegin(GL_POLYGON);
            glVertex2i(esq, -1*hdiff/2 - hdiff - 2*h);
            glVertex2i(esq, -1*hdiff/2 - hdiff - h);
            glVertex2i(dir, -1*hdiff/2 - hdiff - h);
            glVertex2i(dir, -1*hdiff/2 - hdiff - 2*h);
        glEnd();
    }
    glBegin(GL_POLYGON);
        glVertex2i(-1*l/2, -1*hdiff/2 - 2*hdiff - 3*h);
        glVertex2i(-1*l/2, -1*hdiff/2 - 2*hdiff - 2*h);
        glVertex2i(l/2, -1*hdiff/2 - 2*hdiff - 2*h);
        glVertex2i(l/2, -1*hdiff/2 - 2*hdiff - 3*h);
    glEnd();
}
// Desenha um texto na janela GLUT
void DesenhaTexto(char *string)
{
  	glPushMatrix();
        // Posi��o no universo onde o texto ser� colocado
        glRasterPos2f(-win,win-(win*0.08));
        // Exibe caracter a caracter
        while(*string)
             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,*string++);
	glPopMatrix();
}

// Fun��o callback chamada para fazer o desenho
void Desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    // Define a cor corrente
    glColor3f(0.0,1.0,1.0);
    DesenhaRet();

    // Exibe a posi��o do mouse na janela
    glColor3f(0.0f,0.0f,0.0f);
    DesenhaTexto(texto);

    glutSwapBuffers();
}

// Gerenciamento do menu principal
void MenuPrincipal(int op)
{
}

// // Criacao do Menu
// void CriaMenu()
// {
//     // int menu,submenu1,submenu2;

//     // submenu1 = glutCreateMenu();
//     // glutAddMenuEntry("Vermelho",0);
//     // glutAddMenuEntry("Verde",1);
//     // glutAddMenuEntry("Azul",2);

//     // submenu2 = glutCreateMenu();
//     // glutAddMenuEntry("Quadrado",0);
//     // glutAddMenuEntry("Tri�ngulo",1);
//     // glutAddMenuEntry("Losango",2);

//     // menu = glutCreateMenu();
//     // glutAddSubMenu("Cor",submenu1);
//     // glutAddSubMenu("Primitivas",submenu2);
//     DesenhaRet();

//     glFlush();
// }

// Inicializa par�metros de rendering
void Inicializa (void)
{
    // Define a cor de fundo da janela de visualiza��o como branca
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    win=250.0f;
    strcpy(texto, "(0,0)");

    // CriaMenu();

}

// Fun��o callback chamada sempre que o mouse � movimentado
// sobre a janela GLUT com um bot�o pressionado
void MoveMouseBotaoPressionado(int x, int y)
{
    sprintf(texto, "Botao pressionado (%d,%d)", x, y);
    glutPostRedisplay();
}

// Fun��o callback chamada sempre que o mouse � movimentado
// sobre a janela GLUT
void MoveMouse(int x, int y)
{
    sprintf(texto, "(%d,%d)", x, y);
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
    glutMotionFunc(MoveMouseBotaoPressionado);
    glutPassiveMotionFunc(MoveMouse);
    glutSpecialFunc(opcao_menu);
    Inicializa();
    glutMainLoop();
}
