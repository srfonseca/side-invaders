#include "Nave.h"

using namespace std;

/*
 * Construtor da classe Nave
 */
Nave::Nave(void){
    posX= 0.0;      // Posicao em X
    posY= 0.0;      // Posicao em Y
    stepY= 2.5;     // Velocidade de deslocamento da nave em Y
    maxY= 33.0;     // Limite maximo em Y
    minY=-33.0;     // Limite minimo em Y
    pontuacao= 0;   // Pontuacao da nave
    vidas= 5;       // Vidas da nave
}

/*
 * Funcao que especifica as primitivas dos vertices do cockpit
 */
void Nave::desenharCockpit(void){
    glColor3f (0.5,0.5,0.5);
    glBegin(GL_QUADS);
    {
        glVertex2f(3.0, 0.3);
        glVertex2f(3.0, 1.7);
        glVertex2f(3.5, 1.7);
        glVertex2f(3.5, 0.3);
        
        glVertex2f(3.5, 0.5);
        glVertex2f(3.5, 1.3);
        glVertex2f(4.0, 1.3);
        glVertex2f(4.0, 0.5);
    }
    glEnd();
    glColor3f (0.1,0.3,0.9);
    glBegin(GL_QUADS);
    {
        glVertex2f(4.0, 0.8);
        glVertex2f(4.0, 1.1);
        glVertex2f(4.5, 1.1);
        glVertex2f(4.5, 0.8);
    }
    glEnd();
}

/*
 * Funcao que especifica as primitivas dos vertices do corpo do inimigo
 */
void Nave::desenharCorpo(void){
    glColor3f (1.0,1.0,1.0);
    
    glBegin(GL_QUADS);
    {
        glVertex2f (0.0,0.0);
        glVertex2f (0.0,2.0);
        glVertex2f (3.0,2.0);
        glVertex2f (3.0,0.0);
        
        glVertex2f(0.0, 0.3);
        glVertex2f(-0.5, 0.3);
        glVertex2f(-0.5, 1.7);
        glVertex2f(0.0, 1.7);
    }
    glEnd();
    glColor3f (0.1,0.3,0.9);
    glRectf(0.5, 0.7, 2.5, 1.3);
}

/*
 * Funcao que especifica as primitivas dos vertices da asa esquerda
 */
void Nave::desenharAsaEsquerda(void){
    glColor3f (0.1,0.3,0.9);
    glBegin(GL_TRIANGLES);
    {
        glVertex2f (0.5, 2.0);
        glVertex2f (0.5, 5.0);
        glVertex2f (2.6, 2.0);
    }
    glEnd();
    glColor3f(0.9, 0, 0);
    glRectf(0.0, 2.5, 0.5, 4.0);
    
    glColor3f (1.0,0.5,0.0);
    glRectf(0.1, 2.8, 0.3, 3.8);
    
    glColor3f (0.9,0.0,0.0);
    glRectf(0.0, 2.7, -0.3, 3.8);
}

/*
 * Funcao que especifica as primitivas dos vertices da asa direita
 */
void Nave::desenharAsaDireita(void){
    glColor3f (0.1,0.3,0.9);
    glBegin(GL_TRIANGLES);
    {
        glVertex2f (0.5, -3.0);
         glVertex2f (0.5, 0.0);
        glVertex2f (2.6, 0.0);
    }
    glEnd();
    glColor3f (0.9,0.0,0.0);
    glRectf(0.0, -0.8, 0.5, -2.3);
    glColor3f (1.0,0.5,0.0);
    glRectf(0.1, -1.0, 0.3, -2.0);
    glColor3f (0.9,0.0,0.0);
    glRectf(0.0, -1.2, -0.3, -2.0);
}

/*
 * Funcao que desenha a nave, aplica as translacoes e
 *  manipula a matriz de modelacao e visualizacao
 */
void Nave::desenharNave(void){
    glMatrixMode (GL_MODELVIEW);
    glPushMatrix();
    
    glTranslatef(0, posY, 0);
    
    glPushMatrix();
    glTranslatef(-38, 2, 0);
    desenharCorpo();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-38, 2, 0);
    desenharAsaEsquerda();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-38, 2, 0);
    desenharAsaDireita();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-38, 2, 0);
    desenharCockpit();
    glPopMatrix();
    glPopMatrix();
}

/*
 * Funcao que recebe a tecla especial do teclado (seta para cima ou baixo) e move a nave
 */
void Nave::specialKeyboard(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_UP:
            if (posY <= maxY)
            {
                posY+=stepY;
                glutPostRedisplay();
            }
            break;
        case GLUT_KEY_DOWN:
            if (posY > minY){
                posY-=stepY;
                glutPostRedisplay();
            }
            break;
    }
}

/*
 * Funcao que altera a posicao da nave em X
 */
void Nave::setPosX(float x){
    posX=x;
}

/*
 * Funcao que retorna a posicao da nave em X
 */
int Nave::getPosX(){
    return posX;
}

/*
 * Funcao que retorna a posicao da nave em Y
 */
int Nave::getPosY(){
    return posY;
}

/*
 * Funcao que altera a pontuacao
 */
void Nave::setPontuacao(int pontos){
    pontuacao+=pontos;
}

/*
 * Funcao que retorna a pontuacao
 */
int Nave::getPontuacao(){
    return pontuacao;
}

/*
 * Funcao que altera o numero de vidas
 */
void Nave::setVidas(int v){
    vidas=v;
}

/*
 * Funcao que retorna o numero de vidas
 */
int Nave::getVidas(){
    return vidas;
}