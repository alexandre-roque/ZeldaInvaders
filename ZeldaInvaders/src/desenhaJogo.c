#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h> 
#include "variaveisGlobais.h"
#include "desenhaJogo.h"
#include "estadoJogo.h"



int desenhaFundo(){
  glColor3f(1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);
      glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, idTexturaFundo);
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex3f( 0, 0,  0);
        glTexCoord2f(1, 0); glVertex3f( LARGURA_MUNDO, 0,  0);
        glTexCoord2f(1, 1); glVertex3f( LARGURA_MUNDO,  ALTURA_MUNDO,  0);
        glTexCoord2f(0, 1); glVertex3f( 0,  ALTURA_MUNDO,  0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void desenhaObejeto(int x,int y, double cordX,double cordY){

  glPushMatrix();                 // Importante!!
        glTranslatef(x, y, 0);
        glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(cordX , cordY); glVertex2f(-LINK_LARG/2, -LINK_ALT/2);       // v3---v2
            glTexCoord2f(cordX + 0.1 , cordY); glVertex2f( LINK_LARG/2, -LINK_ALT/2); // |     |
            glTexCoord2f(cordX + 0.1 , cordY + 0.5); glVertex2f( LINK_LARG/2,  LINK_ALT/2); // |     |
            glTexCoord2f(cordX , cordY+0.5); glVertex2f(-LINK_LARG/2,  LINK_ALT/2);       // v0---v1
        glEnd();
        glDisable(GL_TEXTURE_2D);
      glPopMatrix();
}

int desenhaLink(GLint x, GLint y){
    
  verificaVitoria();
  glColor3f(1, 1, 1);
    glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, idTexturaLink);
  
  if(link1.existencia == 1){
    if(direcao_link == -1){
      if(frame_link == 1){
        desenhaObejeto(x,y,0.1,0.0);
      }                 

      if(frame_link == -1){
        desenhaObejeto(x,y,0.0,0.0);
      } 
    }

    if(direcao_link == 1){
      if(frame_link == 1){
        desenhaObejeto(x,y,0.4,0.0);
      }

      if(frame_link == -1){
        desenhaObejeto(x,y,0.3,0.0);
      }
    }

    if(direcao_link == 0){
    desenhaObejeto(x,y,0.5,0.5);
    }
  }

  if(link1.existencia == 0){
    desenhaObejeto(x,y,0.6,0.0);
  }

}

void desenhaTexto(void *font, char *string){  
  // Exibe caractere a caractere
  while(*string)
    glutStrokeCharacter(GLUT_STROKE_ROMAN,*string++); 
}