/*
 * Header da classe Nave.cpp
 */

#ifndef __SideInvaders__Nave__
#define __SideInvaders__Nave__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GLUT/GLUT.h>

class Nave{
private:
    GLfloat posX,posY;
    GLfloat stepY;
    GLfloat maxY, minY;
    int pontuacao, vidas;
    void desenharCockpit(void);
    void desenharCorpo(void);
    void desenharAsaEsquerda(void);
    void desenharAsaDireita(void);
    
public:
    Nave(void);
    void desenharNave(void);
    void naveParaCima(void);
    void naveParaBaixo(void);
    void setPosX(float);
    int getPosX();
    int getPosY();
    void specialKeyboard(int, int, int);
    int getPontuacao();
    void setPontuacao(int);
    void setVidas(int);
    int getVidas();
};

#endif /* defined(__SideInvaders__Nave__) */
