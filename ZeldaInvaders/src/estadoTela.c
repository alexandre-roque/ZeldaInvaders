#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h> 
#include "variaveisGlobais.h"
#include "desenhaJogo.h"
#include "inimigos.h"
#include "tiroLink.h"
#include "estadoTela.h"

void mudaTela(){

    switch(tela){

        case MENU:

            glClear(GL_COLOR_BUFFER_BIT);

            glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, idTexturaMenu);
                glBegin(GL_TRIANGLE_FAN);
                glTexCoord2f(0, 0); glVertex3f( 0, 0,  0);
                glTexCoord2f(1, 0); glVertex3f( LARGURA_MUNDO, 0,  0);
                glTexCoord2f(1, 1); glVertex3f( LARGURA_MUNDO,  ALTURA_MUNDO,  0);
                glTexCoord2f(0, 1); glVertex3f( 0,  ALTURA_MUNDO,  0);
                glEnd();
            glDisable(GL_TEXTURE_2D);

            glutSwapBuffers();
        break;

        case JOGO:

            glClear(GL_COLOR_BUFFER_BIT);

            desenhaFundo();
            if(teste == 0){
      
                link1.posicao.y = 10;
                link1.posicao.x= LARGURA_MUNDO/2;  
            }

            criaInimigos();
            desenhaLink(link1.posicao.x,link1.posicao.y);

            if(tiro.existencia == 1){
                desenhaTiro(tiro.posicao.x,tiro.posicao.y);
            }

            glutSwapBuffers();
        break;

        case GAMEOVER:

	    glClear(GL_COLOR_BUFFER_BIT);

	    glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, idTexturaGameOver);
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0, 0); glVertex3f( 0, 0,  0);
		glTexCoord2f(1, 0); glVertex3f( LARGURA_MUNDO, 0,  0);
		glTexCoord2f(1, 1); glVertex3f( LARGURA_MUNDO,  ALTURA_MUNDO,  0);
		glTexCoord2f(0, 1); glVertex3f( 0,  ALTURA_MUNDO,  0);
		glEnd();
	    glDisable(GL_TEXTURE_2D);

	    glutSwapBuffers();
            /*glClear(GL_COLOR_BUFFER_BIT);
            glColor3f(1,0,0);

            glPushMatrix();
                glTranslatef(LARGURA_MUNDO/10,ALTURA_MUNDO/2,0);
                glScalef(0.1, 0.1, 0.2); // diminui o tamanho do fonte
                //glRotatef(15, 0,0,1); // rotaciona o texto
                glLineWidth(5); // define a espessura da linha
                desenhaTexto(GLUT_STROKE_ROMAN,"GAME OVER !!!");
                glPopMatrix();
            glPushMatrix();*/

            desenhaLink(link1.posicao.x , link1.posicao.y);
            glutSwapBuffers();
        break;

        case VITORIA:
		
	    glClear(GL_COLOR_BUFFER_BIT);

	    glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, idTexturaVitoria);
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0, 0); glVertex3f( 0, 0,  0);
		glTexCoord2f(1, 0); glVertex3f( LARGURA_MUNDO, 0,  0);
		glTexCoord2f(1, 1); glVertex3f( LARGURA_MUNDO,  ALTURA_MUNDO,  0);
		glTexCoord2f(0, 1); glVertex3f( 0,  ALTURA_MUNDO,  0);
		glEnd();
	    glDisable(GL_TEXTURE_2D);

	    glutSwapBuffers();
	
           /* glClear(GL_COLOR_BUFFER_BIT);
            glColor3f(1,0,0);

            glPushMatrix();
                glTranslatef(LARGURA_MUNDO/10,ALTURA_MUNDO/2,0);
                glScalef(0.1, 0.1, 0.2); // diminui o tamanho do fonte
                //glRotatef(15, 0,0,1); // rotaciona o texto
                glLineWidth(5); // define a espessura da linha
                desenhaTexto(GLUT_STROKE_ROMAN,"VITORIA !!!");
                glPopMatrix();
            glPushMatrix();*/

            //glutSwapBuffers();
        break;

        default:
        break;
    }

}

void desenhaCena(){
   
    mudaTela();
}
