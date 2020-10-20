#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>	
#include <math.h>
#include "variaveisGlobais.h"
#include "tiroLink.h"

void movimentoTiroLink(){
  
  tiro.posicao.y++;
  if(tiro.posicao.y == ALTURA_MUNDO){
    tiro.existencia = 0;
  }

  glutPostRedisplay();
  glutTimerFunc(PERIODO/3, movimentoTiroLink, 1);
}

void verificaColisaoTiroLink(){
  tiro.raio = TIRO_LARG;

  for(int i = 0;i < NUM_INI_HORI;i++){
    for(int j = 0;j < NUM_INI_VERT; j++){
      inimigos[i][j].raio = INI_LARG;
      int dx = tiro.posicao.x - inimigos[i][j].posicao.x;
      int dy = tiro.posicao.y - inimigos[i][j].posicao.y;
      double distancia = sqrt(dx * dx + dy * dy);
      if(distancia < tiro.raio + inimigos[i][j].raio) {
        inimigos[i][j].existencia = 0;
        tiro.existencia = 0;
      }
    }
  }
}

int desenhaTiro(GLint x, GLint y){
  if(tiro.existencia == 1){
    verificaColisaoTiroLink();
    glColor3f(1, 1, 1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, idTexturaFlecha);
    glPushMatrix();                 // Importante!!
      glTranslatef(x, y, 0);
      glBegin(GL_TRIANGLE_FAN);
          glTexCoord2f(0 , 0); glVertex2f(-TIRO_LARG/3, -TIRO_ALT/2); // v3---v2
          glTexCoord2f(1 , 0); glVertex2f( TIRO_LARG/3, -TIRO_ALT/2); // |     |
          glTexCoord2f(1 , 1); glVertex2f( TIRO_LARG/3,  TIRO_ALT/2); // |     |
          glTexCoord2f(0 , 1); glVertex2f(-TIRO_LARG/3,  TIRO_ALT/2); // v0---v1
      glEnd();
      glEnd();
    glPopMatrix();                   // Importante!!
  }
}