#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <GLUT/GLUT.h>
#include <vector>
#include <math.h>
#include "Nave.h"
#include "Inimigo.h"
#include "Projetil.h"

using namespace std;

Nave *aNave = new Nave();
vector <Inimigo*> v_inimigos;
vector <Projetil*> v_projetil;

bool emJogo=false;
bool fimJogo=false;
bool pausa=false;
bool vitoria=false;
bool ajuda=false;
bool atualizaPosVertical=false;
bool atualizaPosHorizontal=false;
bool disparaProjetil=false;

int totalNumInimigos=0;
int totalNumProjeteis=0;

float red[]= {1,0.3,0.3};
float yellow[]= {1.0,1.0,0.0};

/*
 * Funcao que cria os inimigos e os adiciona ao vector v_inimigos
 */
void criaInimigos(){
    Inimigo *oInimigo;
    for (int i = 0; i < 3; i++){        //colunas
        for (int j = 0; j < 6; j++){    //linhas
            oInimigo=new Inimigo(i*7, j*7);
            oInimigo->setIdInimigo(totalNumInimigos);
            v_inimigos.push_back(oInimigo);
            totalNumInimigos++;
            //printf("Inimigo criado, id: %d\n", oInimigo->getIdInimigo());
        }
    }
}

/*
 * Entidade de controlo dos inimigos responsavel por dar a ordem
 * de deslocacao das naves inimigas
 */
void controloInimigos(){
    static int direcao = 0;
    GLfloat posXatual=0, posYatual=0;
    GLfloat xMin = 0.0, xMax = 0.0;
    GLfloat yMin = 0.0, yMax = 0.0;
    
    //Verificar se o vector esta vazio antes de aceder aos elementos
    if (v_inimigos.size() == 0){
        return;
    }
    
    //Verificar os limites das naves inimigas
    for (int i = 0; i < v_inimigos.size(); i++){
        posXatual = v_inimigos.at(i)->getPosX();
        posYatual = v_inimigos.at(i)->getPosY();
        if (yMax < posYatual)
            yMax = posYatual;
        
        if (yMin > posYatual)
            yMin = posYatual;
        
        if (xMax < posXatual)
            xMax = posXatual;
        
        if (xMin > posXatual)
            xMin = posXatual;
    }
    yMax += 5;
    switch (direcao){
        case 0:
            if (yMax >= 40){
                direcao = 1;
                atualizaPosHorizontal=true;
            }
            break;
        case 1:
            if (yMin <= -38){
                direcao = 0;
                atualizaPosHorizontal=true;
            }
            break;
    }
    
    /* printf("%d\n", direcao);
     printf("posXatual: %f\n", posXatual);
     printf("posYatual: %f\n", posYatual);
     printf("yMax: %f\n", yMax);
     printf("yMin: %f\n", yMin);
     printf("xMax: %f\n", xMax);
     printf("xMin: %f\n", xMin);
     printf("\n");*/
    
    //Mover as naves inimigas na vertical
    for ( int i = 0; i < v_inimigos.size(); i++ )
        v_inimigos.at(i)->deslocarVertical(direcao);
    
    //Mover as naves inimigas na horizontal
    if(atualizaPosHorizontal){
        for(int i=0; i<v_inimigos.size(); i++){
            v_inimigos.at(i)->deslocarHorizontal();
            atualizaPosHorizontal=false;
        }
    }
}

/*
 * Funcao que cria os projeteis
 * Parametro x - posicao do projetil em X
 * Parametro y - posicao do projetil em Y
 * Parametro sentidoDirecao - se negativo, decrementa em X e corresponde aos projeteis dos inimigos
 *                          - se positivo, incrementa em X e corresponde aos projeteis da nave
 * Parametro cor - cor do projetil definida no array
 */
void criaProjetil(int x, int y, int sentidoDirecao, const float cor[]){
    Projetil *p = new Projetil(x, y,sentidoDirecao ,cor);
    if (p->dentroDosLimites()) {
        totalNumProjeteis++;
        p->setIdProjetil(totalNumProjeteis);
        //printf("Projetil criado: %d\n", totalNumProjeteis);
        v_projetil.push_back(p);
    }
}

/*
 * Funcao responsavel por criar projeteis aleatorios
 * entre as naves inimigas ao invocar a funcao principal criaProjetil
 */
void inimigoDisparaProjetil(){
    vector<Inimigo*>::iterator it = v_inimigos.begin();
    int i = rand() % v_inimigos.size();
    advance(it, i);
    criaProjetil(((*it)->getPosX()+23),((*it)->getPosY()+1), -1, red);
}

/*
 * Funcao responsavel por criar projeteis da nave ao invocar
 * a funcao principal criaProjetil
 */
void naveDisparaProjetil(){
    criaProjetil((aNave->getPosX()-29), (aNave->getPosY()+1), 1, yellow);
}

/*
 * Funcao booleana que retorna true se o projetil colidiu com uma nave inimiga, caso contrario false
 * Parametro inimigo - ponteiro da classe Inimigo
 * Parametro p - ponteiro da classe Projetil
 */
bool colisaoInimigo(Inimigo* inimigo, Projetil* p){
    if (p->getDirecao() < 0)
        return false;
    float v1;
    int p1[2] = { p-> getPosX()+10, p->getPosY()};
    int p2[2] = { inimigo->getPosX()+10, inimigo->getPosY()};
    v1 = sqrt(pow((p1[0] - p2[0]), 2) + pow((p1[1] - p2[1]), 2));
    return v1 <= 2;
}

/*
 * Funcao booleana que retorna true se o projetil colidiu com a nave, caso contrario false
 * Parametro inimigo - ponteiro da classe Inimigo
 * Parametro p - ponteiro da classe Projetil
 */
bool colisaoNave(Nave* nave, Projetil* p){
    if (p->getDirecao() > 0)
        return false;
    float v1;
    int p1[2] = { p-> getPosX()+10, p->getPosY()};
    int p2[2] = { nave->getPosX(), nave->getPosY()+5};
    v1 = sqrt(pow((p1[0] - p2[0]), 2) + pow((p1[1] - p2[1]), 2));
    return v1 <= 2;
}

/*
 * Entidade de controlo dos projeteis responsavel por eliminar os projeteis
 * que nao se encontram dentro dos limites
 */
void controloProjeteis(){
    // Apaga o projetil quando sai dos limites
    for(int i=0; i<v_projetil.size();i++){
        //printf("Numero de projeteis: %lu\n",v_projetil.size());
        if(!v_projetil.at(i)->dentroDosLimites()){
            v_projetil.erase(v_projetil.begin()+i);
            //printf("Numero de projeteis: %lu\n",v_projetil.size());
        }
    }
}

/*
 * Funcao que altera o valor dos atributos booleanos
 * consoante o estado do jogo
 */
void estadoJogo(){
    if(v_inimigos.size() > 0 && aNave->getVidas()==0){
        fimJogo=true;
        vitoria=false;
    }
    else if(v_inimigos.size()==0 && aNave->getVidas() > 0){
        fimJogo=true;
        vitoria=true;
    }
}

/*
 * Funcao para imprimir texto
 */
void imprimeTexto(void *font, const char *text, float x, float y){
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    glRasterPos2f(x, y);
    int len = (int) strlen(text);
    for (int i = 0; i < len; i++){
        glutBitmapCharacter(font, text[i]);
    }
}

/*
 * Funcao para imprimir numeros
 */
void imprimeNumero(void *font, int n, float x, float y){
    char s[10];
    int len =sprintf (s, "%d", n);
    for (int i = 0; i < len; i++){
        glutBitmapCharacter(font, s[i]);
    }
}
// -------------------------------------------------------------
// CALLBACKS
// -------------------------------------------------------------
/*
 * CALLBACK de desenho
 */
void desenhar (void){
    glClearColor ( 0, 0, 0, 0 );
    glClear ( GL_COLOR_BUFFER_BIT );
    
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glViewport(0, 0, 800, 570);
    gluOrtho2D (-40.0, 40.0, -40.0, 40.0);
    glMatrixMode (GL_MODELVIEW);
    estadoJogo();
    
    if(emJogo==false){
        glColor3f (0.5,0.5,0.5);
        imprimeTexto(GLUT_BITMAP_HELVETICA_18, "SIDE INVADERS", -7, 20);
        imprimeTexto(GLUT_BITMAP_HELVETICA_12,"_ENTER para jogar",-6, 15);
        imprimeTexto(GLUT_BITMAP_HELVETICA_12,"_A para a ajuda", -6, 10);
        imprimeTexto(GLUT_BITMAP_HELVETICA_12,"_ESC para sair", -6, 5);
        imprimeTexto(GLUT_BITMAP_HELVETICA_12,"ESTCB - TIM - Computacao Grafica", -39, -32);
        imprimeTexto(GLUT_BITMAP_HELVETICA_12,"Silvia Fonseca nr 62009048", -39, -35);
        
    } else if(emJogo==true && fimJogo==false && pausa==false){
        //Desenha a nave
        aNave->desenharNave();
        
        //Desenha os inimigos
        for(int i=0; i<v_inimigos.size(); i++){
            v_inimigos.at(i)->desenharInimigo();
        }
        //Desenha os projeteis
        for(int j=0; j<v_projetil.size(); j++){
            v_projetil.at(j)->desenhaProjetil();
        }
        
        glViewport(0, 570, 800, 30);
        gluOrtho2D(0.0,40.0,0.0,40.0);
        glColor3f(1.0,1.0,1.0);
        imprimeTexto(GLUT_BITMAP_HELVETICA_12, "Pontuacao: ", -13, -6);
        imprimeNumero(GLUT_BITMAP_HELVETICA_12, aNave->getPontuacao(), -20, -6);
        imprimeTexto(GLUT_BITMAP_HELVETICA_12, "Vidas: ", 3, -5);
        imprimeNumero(GLUT_BITMAP_HELVETICA_12, aNave->getVidas(), -10, -6);
    }
    if(fimJogo==true && vitoria==true){
        glColor3f (0.5,0.5,0.5);
        imprimeTexto(GLUT_BITMAP_HELVETICA_18, "Vitoria! Ganhou o jogo com ", -20, 5);
        imprimeNumero(GLUT_BITMAP_HELVETICA_18, aNave->getPontuacao(), -30 , 5);
        imprimeTexto(GLUT_BITMAP_HELVETICA_18, "pontos.", 7, 5);
    }
    if (fimJogo==true && vitoria==false){
        glColor3f (0.5,0.5,0.5);
        imprimeTexto(GLUT_BITMAP_HELVETICA_18, "Game Over", -5, 5);
    }
    if(pausa){
        glColor3f (0.5,0.5,0.5);
        imprimeTexto(GLUT_BITMAP_HELVETICA_18, "PAUSA", -4, 20);
        imprimeTexto(GLUT_BITMAP_HELVETICA_12,"_P para continuar",-6, 15);
        imprimeTexto(GLUT_BITMAP_HELVETICA_12,"_ESC para sair", -6, 10);
    }
    if(ajuda){
        glClearColor ( 0, 0, 0, 0 );
        glClear ( GL_COLOR_BUFFER_BIT );
        glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();
        glViewport(0, 0, 800, 570);
        gluOrtho2D (-40.0, 40.0, -40.0, 40.0);
        glMatrixMode (GL_MODELVIEW);
        glColor3f (0.5,0.5,0.5);
        imprimeTexto(GLUT_BITMAP_HELVETICA_18, "AJUDA", -7, 20);
        imprimeTexto(GLUT_BITMAP_HELVETICA_12,"_Tecla para cima para mover a nave para cima", -6, 15);
        imprimeTexto(GLUT_BITMAP_HELVETICA_12,"_Tecla para baixo para mover a nave para baixo", -6, 10);
        imprimeTexto(GLUT_BITMAP_HELVETICA_12,"_Barra de espacos para disparar projeteis", -6, 5);
        imprimeTexto(GLUT_BITMAP_HELVETICA_12,"_A voltar para o menu principal", -6, 0);
        imprimeTexto(GLUT_BITMAP_HELVETICA_12,"_ESC para sair", -6, -5);
    }
    glutSwapBuffers();
}

/*
 * CALLBACK de temporizador responsavel por atualizar a posicao vertical
 * das naves inimigas
 */
void timerAtualizaPosInimigo(int value){
    atualizaPosVertical=true;
    glutPostRedisplay();
    glutTimerFunc(100, timerAtualizaPosInimigo, 1);
}

/*
 * CALLBACK de temporizador responsavel por invocar a funcao inimigoDisparaProjetil()
 * a cada 0.7 segundos
 */
void timerInimigoDisparaProjetil(int value){
    inimigoDisparaProjetil();
    glutPostRedisplay();
    glutTimerFunc(700, timerInimigoDisparaProjetil, 2);
}

/*
 * CALLBACK idle
 * Metodos de detecao de colisao e consequencias
 */
void idle(void){
    if(atualizaPosVertical){
        controloInimigos();
        atualizaPosVertical = false;
    }
    if(!v_projetil.empty())
        controloProjeteis();
    
    // Apaga a nave inimiga e o projetil quando colidem
    for(int j=0; j<v_projetil.size(); j++){
        for(int i=0; i<v_inimigos .size(); i++){
            if(colisaoInimigo(v_inimigos.at(i), v_projetil.at(j))){
                //printf("Atingiu o INIMIGO\n");
                v_inimigos.erase(v_inimigos.begin()+i);
                aNave->setPontuacao(10);
                //printf("Pontuacao da nave: %d\n", aNave->getPontuacao());
            }
        }
    }
    
    // Verifica quando a nave e atingida por um projetil
    for(int j=0; j<v_projetil.size(); j++){
        for(int i=0; i < 1; i++){
            if(colisaoNave(aNave, v_projetil.at(j))){
                //printf("Atingiu a NAVE\n");
                if(aNave->getVidas() > 0){
                    aNave->setVidas(aNave->getVidas()-1);
                    v_projetil.erase(v_projetil.begin()+j);
                    //printf("Vidas da nave:%d\n", aNave->getVidas());
                }
            }
        }
    }
    glutPostRedisplay();
}

/*
 * CALLBACK de teclado
 */
void trataTeclado (unsigned char tecla, int x, int y){
    switch (tecla) {
        case 13:
            emJogo=true;
            break;
        case 27:
            exit(0);
            break;
        case 32:
            naveDisparaProjetil();
            disparaProjetil=true;
            break;
        case 97:
            if(ajuda==false)
                ajuda=true;
            else
                ajuda=false;
            break;
        case 112:
            if(pausa==false)
                pausa=true;
            else
                pausa=false;
            break;
    }
}
/*
 * CALLBACK de teclado especial
 */
void specialKeyboard(int key, int x, int y){
    aNave->specialKeyboard(key, x, y);
}
/*
 * Funcao main
 */
int main(int argc, char *argv[]){
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE);
    
    glutInitWindowSize (800,600);
    glutCreateWindow ("Side Invaders");
    
    criaInimigos();
    
    glutDisplayFunc (desenhar);
    glutKeyboardFunc (trataTeclado);
    glutSpecialFunc(specialKeyboard);
    
    glutIdleFunc(idle);
    
    glutTimerFunc(100, timerAtualizaPosInimigo, 1);
    glutTimerFunc(1000, timerInimigoDisparaProjetil, 2);
    glutMainLoop ();
    
    return 0;
}