#include "Inimigo.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

/*
 * Construtor da classe Inimigo
 * Parametros x e y - posicao do inimigo
 */
Inimigo::Inimigo(float x, float y){
    idInimigo=0;        // ID do inimigo
    minX = -60.0;       // Limite minimo em X
    stepY = 2.5;        // Velocidade de deslocamento do inimigo em Y
    stepX = 1.0;        // Velocidade de deslocamento do inimigo em X
    posX=x;             // Posicao do inimigo em X
    posY=y;             // Posicao do inimigo em Y
}

/*
 * Funcao que especifica as primitivas dos vertices do corpo do inimigo
 */
void Inimigo::desenharCorpo(){
    glColor3f( 0.0, 0.8, 0);
    //Corpo
    glRectf(0.0, 0.0, 5.5, 1.5);
    glRectf(0.5, -0.5, 5.0, 0.0);
    glRectf(1.0, 1.0, 4.5, 2.0);
    
    //Pernas
    glRectf(1.0, -1.0, 1.5, -0.5);
    glRectf(1.5, -1.5, 2.5, -1.0);
    glRectf(3.0, -1.5, 4.0, -1.0);
    glRectf(4.0, -1.0, 4.5, -0.5);
    
    //Bracos
    glRectf(0.0, 1.5, 0.5, 2.5);
    glRectf(5.0, 1.5, 5.5, 2.5);
    
    //Antenas
    glRectf(2.0, 1.5, 2.5, 2.0);
    glRectf(1.5, 2.0, 2.0, 2.5);
    glRectf(1.0, 2.5, 1.5, 3.0);
    
    glRectf(3.0, 1.5, 3.5, 2.0);
    glRectf(3.5, 2.0, 4.0, 2.5);
    glRectf(4.0, 2.5, 4.5, 3.0);
    
    //Olhos
    glColor3f(1, 1, 1);
    glRectf(1.5, 1.0, 2.0, 1.5);
    glRectf(3.5, 1.0, 4.0, 1.5);
}
/*
 * Funcao que desenha o inimigo, aplica as translacoes e
 *  manipula a matriz de modelacao e visualizacao
 */
void Inimigo::desenharInimigo(){
    glMatrixMode (GL_MODELVIEW); //selecao da matriz de modelacao e visualizacao
    glPushMatrix();
    glTranslatef(posX, posY, 0);
    glPushMatrix();
    glTranslatef(20, 2, 0);
    desenharCorpo();
    glPopMatrix();
    glPopMatrix();
}

/*
 * Funcao que desloca o inimigo em Y consoante a direcao recebida
 * 0 = para cima, 1 = para baixo
 */
void Inimigo::deslocarVertical(int direcao){
    switch (direcao){
        case 0:
            posY+=stepY;
            break;
        case 1:
            posY-=stepY;
            break;
    }
}

/*
 * Funcao que desloca o inimigo em X
 */
void Inimigo::deslocarHorizontal(){
    if (posX >= minX){
        posX-=stepX;
    }
    glutSwapBuffers();
}

/*
 * Funcao que retorna o id do inimigo
 */
int Inimigo::getIdInimigo(){
    return idInimigo;
}

/*
 * Funcao que define o id do inimigo
 */
void Inimigo::setIdInimigo(int new_idInimigo){
    idInimigo=new_idInimigo;
}

/*
 * Funcao que retorna a posicao do inimigo em X
 */
int Inimigo::getPosX(){
    return posX;
}

/*
 * Funcao que retorna a posicao do inimigo em Y
 */
int Inimigo::getPosY(){
    return posY;
}


/*
 * Funcao que altera a posicao do inimigo em X
 */
void Inimigo::setPosX(float x){
    posX+=x;
}

/*
 * Funcao que altera a posicao do inimigo em Y
 */
void Inimigo::setPosY(float y){
    posY+=y;
}