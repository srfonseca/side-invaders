#include "Projetil.h"

using namespace std;

/*
 * Construtor da classe Projetil
 * Parametros x e y - posicao do projetil
 * Parametro sentidoDirecao - velocidade de deslocamento e sentido de direcao
 */
Projetil::Projetil(float x, float y, int sentidoDirecao, const GLfloat cor[]){
    idProjetil=0;               // ID do projetil
    posX=x;                     // Posicao em X
    posY=y;                     // Posicao em Y
    direcao=sentidoDirecao;     /* Velocidade/direcao do projetil, 
                                 se positivo corresponde ao projetil da nave, 
                                 se negativo corresponde aos inimigos */
    corProjetil[0]= cor[0];
    corProjetil[1]= cor[1];
    corProjetil[2]= cor[2];
}

/*
 * Funcao que especifica as primitivas dos vertices do projetil
 */
void Projetil::desenhaCorpo(){
    glColor3f(corProjetil[0], corProjetil[1], corProjetil[2]);
    glBegin(GL_QUADS);{
        glVertex2f (0.0,0.0);
        glVertex2f (0.0,0.5);
        glVertex2f (1.5,0.5);
        glVertex2f (1.5,0.0);
    }glEnd();
    glBegin(GL_TRIANGLES);
    {
        glVertex2f(0.0, 0.0);
        glVertex2f(-0.5, 0.25);
        glVertex2f(0.0, 0.5);
        
        glVertex2f(1.5, 0.0);
        glVertex2f(1.5, 0.5);
        glVertex2f(2.0, 0.25);
        
    }glEnd();
}

/*
 * Funcao que desenha e move o projetil, aplica as translacoes e
 *  manipula a matriz de modelacao e visualizacao
 */
void Projetil::desenhaProjetil(){
    posX=posX+direcao;
    glMatrixMode (GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(posX, posY, 0);
    glPushMatrix();
    desenhaCorpo();
    glPopMatrix();
    glPopMatrix();
}

/*
 * Funcao que retorna a posicao do projetil em X
 */
int Projetil::getPosX(){
    return posX;
}

/*
 * Funcao que retorna a posicao do projetil em Y
 */
int Projetil::getPosY(){
    return posY;
}

/*
 * Funcao que retorna o id do projetil
 */
int Projetil::getIdProjetil(){
    return idProjetil;
}


/*
 * Funcao que retorna o id do projetil
 */
int Projetil::getDirecao(){
    return direcao;
}


/*
 * Funcao que altera o id do projetil
 */
void Projetil::setIdProjetil(int new_idProjetil){
    idProjetil=new_idProjetil;
}

/*
 * Funcao que verifica se o projectil esta dentro dos limites
 * Retorna true se o projectil esta dentro dos limites
 * Retorna false se o projectil esta fora dos limites
 */
bool Projetil::dentroDosLimites(){
    return (getPosX() <= 40) && (getPosX() >= -40);
}


