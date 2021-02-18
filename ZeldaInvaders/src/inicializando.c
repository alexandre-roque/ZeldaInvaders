#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>	
#include "variaveisGlobais.h"
#include "tiroLink.h"
#include "inicializando.h"

void inicializa(){
    // cor para limpar a tela branco
    glClearColor(1, 1, 1, 0);
    //Registra Callback do Tiro
    glutTimerFunc(PERIODO/3, movimentoTiroLink, 1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    idTexturaLink = carregaTextura("spritelink.png");
    idTexturaMenu = carregaTextura("menu.jpg");
    idTexturaGameOver = carregaTextura("gameOver.jpeg");
    idTexturaInimigo1 = carregaTextura("spriteinimigo1.png");
    idTexturaInimigo2 = carregaTextura("spriteinimigo2.png");
    idTexturaInimigo3 = carregaTextura("spriteinimigo3.png");
    idTexturaFundo = carregaTextura("fundo.jpg");
    idTexturaFlecha = carregaTextura("flecha.png");
    idTexturaVitoria = carregaTextura("vitoria.png");
    
    
    for(int i=0;i<NUM_INI_HORI;i++){
        for(int j=0;j<NUM_INI_VERT;j++){
            inimigos[i][j].existencia = 1;
        }
    }
    tiro.existencia = 0;
    link1.existencia = 1;
}

// Callback de redimensionamento
void redimensiona(GLint w, GLint h){

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, LARGURA_MUNDO, 0, ALTURA_MUNDO, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
