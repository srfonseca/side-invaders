/*
 * Header da classe Projetil.cpp
 */

#ifndef __SideInvaders__Projetil__
#define __SideInvaders__Projetil__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GLUT/GLUT.h>

class Projetil{
private:
    GLfloat posX, posY;
    void desenhaCorpo();
    int idProjetil;
    int direcao; 
    float corProjetil[3];
    
public:
    Projetil(float, float, int, const GLfloat[]);
    void desenhaProjetil();
    int getPosX();
    int getPosY();
    int getIdProjetil();
    void setIdProjetil(int);
    bool dentroDosLimites();
    int getDirecao();
};

#endif /* defined(__SideInvaders__Projetil__) */
