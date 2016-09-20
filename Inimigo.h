/*
 * Header da classe Inimigo.cpp
 */

#ifndef __SideInvaders__Inimigo__
#define __SideInvaders__Inimigo__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GLUT/GLUT.h>

class Inimigo{
private:
    GLfloat stepY, stepX, posY, posX;
    GLfloat minX;
    int idInimigo;
    void desenharCorpo(void);
    
public:
    Inimigo(float, float);
    void desenharInimigo(void);
    void deslocarHorizontal();
    void deslocarVertical(int);
    int getIdInimigo();
    void setIdInimigo(int);
    void setPosX(float);
    void setPosY(float);
    int getPosX();
    int getPosY();
};
#endif /* defined(__SideInvaders__Inimigo__) */
