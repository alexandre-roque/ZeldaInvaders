#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "inimigos.h"
#include "variaveisGlobais.h"

void atualiza(int valor)
{
    // Atualiza a lógica, nenhum desenho deve ser feito aqui
    
    
    // atualiza o quadro atual da animação
    quadroAtual = (quadroAtual + 1) % 3;
    quadroAtualIni3 = (quadroAtualIni3 + 1) % 21;
    
    // avisa o freeglut que a tela deve ser redesenhada
    glutPostRedisplay();
    
    // registra esta função para ser chamada denovo daqui a 100ms
    glutTimerFunc(200, atualiza, 1);
}


int desenhaInimigo(GLint x, GLint y, GLint j){
    float comprimentoDaTextura = 160;
    float larguraDatextura = 34;
    int numeroDeQuadros = 5;
    float quadroDaTextura = comprimentoDaTextura / numeroDeQuadros;
    
    // coordenadas da textura
    float tamanhoDoQuadro = 1.f / numeroDeQuadros;
    float c0 = quadroAtual * tamanhoDoQuadro;


    float comprimentoDaTexturaIni3 = 840;
    float larguraDatexturaIni3 = 47;
    int numeroDeQuadrosIni3 = 21;
    float quadroDaTexturaIni3 = comprimentoDaTexturaIni3 / numeroDeQuadrosIni3;
    
    // coordenadas da textura
    float tamanhoDoQuadroIni3 = 1.f / numeroDeQuadrosIni3;
    float c0Ini3 = quadroAtualIni3 * tamanhoDoQuadroIni3;



    glColor3f(1, 1, 1);
      if(j==0){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, idTexturaInimigo2);
      }

     if(j==1){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, idTexturaInimigo1);
      }

      if(j==2){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, idTexturaInimigo1);
      }

      if(j==3){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, idTexturaInimigo3);


        glPushMatrix();                 // Importante!!
        glTranslatef(x, y, 0);
        glBegin(GL_TRIANGLE_FAN);
          glTexCoord2f(c0Ini3 , 0); glVertex2f(-LINK_LARG/2, -LINK_ALT/2); // v3---v2
          glTexCoord2f(c0Ini3 + tamanhoDoQuadroIni3, 0); glVertex2f( LINK_LARG/2, -LINK_ALT/2); // |     |
          glTexCoord2f(c0Ini3 + tamanhoDoQuadroIni3, 1); glVertex2f( LINK_LARG/2,  LINK_ALT/2); // |     |
          glTexCoord2f(c0Ini3 , 1); glVertex2f(-LINK_LARG/2,  LINK_ALT/2); // v0---v1
          //glTexCoord2f(0 , 0); glVertex2f(-INI_LARG/2, -INI_ALT/2); glTexCoord2f(0.09 , 0); glVertex2f( INI_LARG/2, -INI_ALT/2);glTexCoord2f(0.09 , 0.5); glVertex2f( INI_LARG/2,  INI_ALT/2); glTexCoord2f(0.0 , 0.5); glVertex2f(-INI_LARG/2,  INI_ALT/2); // v0---v1
        glEnd();
      glPopMatrix();

      }

    //glutPostRedisplay(); 
      if(j==0 || j==1 || j==2){
        glPushMatrix();                 // Importante!!
            glTranslatef(x, y, 0);
            glBegin(GL_TRIANGLE_FAN);
              glTexCoord2f(c0, 0); glVertex2f(-LINK_LARG/2, -LINK_ALT/2); // v3---v2
              glTexCoord2f(c0 + tamanhoDoQuadro , 0); glVertex2f( LINK_LARG/2, -LINK_ALT/2); // |     |
              glTexCoord2f(c0 + tamanhoDoQuadro, 1); glVertex2f( LINK_LARG/2,  LINK_ALT/2); // |     |
              glTexCoord2f(c0 , 1); glVertex2f(-LINK_LARG/2,  LINK_ALT/2); // v0---v1
              //glTexCoord2f(quadroInimigo - 0.2 , 0); glVertex2f(-INI_LARG/2, -INI_ALT/2);glTexCoord2f(quadroInimigo , 0); glVertex2f( INI_LARG/2, -INI_ALT/2);glTexCoord2f(quadroInimigo , 1); glVertex2f( INI_LARG/2,  INI_ALT/2);glTexCoord2f(quadroInimigo - 0.2 , 1); glVertex2f(-INI_LARG/2,  INI_ALT/2); // v0---v1

            glEnd();
          glPopMatrix();
      }
}

void criaInimigos(){
  
  for(int i=0;i<NUM_INI_HORI;i++){

    for(int j=0;j<NUM_INI_VERT;j++){

      if(inimigos[i][j].existencia == 1){

        inimigos[i][j].posicao.x = (X_INICIAL_INIMIGOS + i*ESPACO_INI);
        inimigos[i][j].posicao.y = (ALTURA_INICIAL_INIMIGOS + j*ESPACO_INI);
        desenhaInimigo((X_INICIAL_INIMIGOS + i*ESPACO_INI) , (ALTURA_INICIAL_INIMIGOS + j*ESPACO_INI) , j );
      }

      if(inimigos[i][j].existencia == 0){
        inimigos[i][j].posicao.x = 0;
        inimigos[i][j].posicao.y = 0;
      }

    }
  }
}
