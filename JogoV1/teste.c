#include <SOIL/SOIL.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <SOIL/SOIL.h>
#include<stdlib.h>
#include <unistd.h>
#define LARGURA_MUNDO 114
#define ALTURA_MUNDO 114
#define NUM_MOVIMENTO 2
#define LINK_LARG 10
#define LINK_ALT 10
#define INI_LARG 4
#define INI_ALT 4
#define DIST_INI_TELA 10
#define NUM_INI_HORI 9
#define NUM_INI_VERT 4
#define ESPACO_INI 10
#define PERIODO 33
#define TIRO_LARG 2
#define TIRO_ALT 4

enum Tela { MENU, JOGO, VITORIA, GAMEOVER };
enum Tela tela = MENU;
/*void mudaTela(Tela novaTela) {
    // faz uma "transição" para o novo estado
    switch (novaTela) {
        case MENU:
        case JOGO:
        case VITORIA:
        case GAMEOVER:
            break;
   }
   // efetivamente muda a variável de estado
   telaAtual = novaTela;
}*/

typedef struct{
  
  GLint x,y;

}vetor2d;

typedef struct{
  vetor2d posicao;

  vetor2d dimensoes;
    
}objeto;

objeto link1;
objeto inimigos[9][5];
objeto tiro;

GLuint idTexturaLink;
GLuint idTexturaInimigo1;
GLuint idTexturaInimigo2;
GLuint idTexturaInimigo3;
GLuint idTexturaMenu;


GLuint carregaTextura(const char* arquivo) {
    GLuint idTextura = SOIL_load_OGL_texture(
                           arquivo,
                           SOIL_LOAD_AUTO,
                           SOIL_CREATE_NEW_ID,
                           SOIL_FLAG_INVERT_Y
                       );

    if (idTextura == 0) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }

    return idTextura;
}


void criaInimigos(){
  
  for(int i=0;i<NUM_INI_HORI;i++){

    for(int j=0;j<NUM_INI_VERT;j++){

      inimigos[i][j].posicao.x = (X_INICIAL_INIMIGOS + i*ESPACO_INI);
      //printf("%d) X2= %d\n",i,x2 );
      inimigos[i][j].posicao.y = (ALTURA_INICIAL_INIMIGOS + j*ESPACO_INI);
      desenhaInimigo(X_INICIAL_INIMIGOS + i*ESPACO_INI,ALTURA_INICIAL_INIMIGOS + j*ESPACO_INI);
    }
  }
}

int desenhaInimigo(GLint x, GLint y){
    glColor3f(1, 0, 0);
    //glutPostRedisplay(); 
    glPushMatrix();                 // Importante!!
        glTranslatef(x, y, 0);
        glBegin(GL_TRIANGLE_FAN);

            glVertex2f(-INI_LARG/2, -INI_ALT/2); // v3---v2
            glVertex2f( INI_LARG/2, -INI_ALT/2); // |     |
            glVertex2f( INI_LARG/2,  INI_ALT/2); // |     |
            glVertex2f(-INI_LARG/2,  INI_ALT/2); // v0---v1
        glEnd();
      glPopMatrix();
                       // Importante!!
}

int desenhaLink(GLint x, GLint y){
    glBindTexture(GL_TEXTURE_2D, idTexturaLink);

  glPushMatrix();                 // Importante!!
    glTranslatef(x, y, 0);
    glBegin(GL_TRIANGLE_FAN);

        glVertex2f(-LINK_LARG/2, -LINK_ALT/2); // v3---v2
        glVertex2f( LINK_LARG/2, -LINK_ALT/2); // |     |
        glVertex2f( LINK_LARG/2,  LINK_ALT/2); // |     |
        glVertex2f(-LINK_LARG/2,  LINK_ALT/2); // v0---v1
    glEnd();
  glPopMatrix();                  // Importante!!

}

int desenhaTiro(GLint x, GLint y){
    glColor3f(1, 0, 0);

  glPushMatrix();                 // Importante!!
    glTranslatef(x, y, 0);
    glBegin(GL_TRIANGLE_FAN);

        glVertex2f(-TIRO_LARG/2, -TIRO_ALT/2); // v3---v2
        glVertex2f( TIRO_LARG/2, -TIRO_ALT/2); // |     |
        glVertex2f( TIRO_LARG/2,  TIRO_ALT/2); // |     |
        glVertex2f(-TIRO_LARG/2,  TIRO_ALT/2); // v0---v1
    glEnd();
  glPopMatrix();                   // Importante!!
  
}

void mudaTela(){

	switch(tela){

		case MENU:

			glClear(GL_COLOR_BUFFER_BIT);
			glBindTexture(GL_TEXTURE_2D, idTexturaMario);
      glBegin(GL_TRIANGLE_FAN);
        // Associamos um canto da textura para cada vértice
        glTexCoord2f(0, 0);
        glVertex3f(-LARGURA_MUNDO, -ALTURA_MUNDO,  0);

        glTexCoord2f(1, 0);
        glVertex3f( LARGURA_MUNDO, -ALTURA_MUNDO,  0);

        glTexCoord2f(1, 1);
        glVertex3f( LARGURA_MUNDO,  ALTURA_MUNDO,  0);

        glTexCoord2f(0, 1);
        glVertex3f(-LARGURA_MUNDO,  ALTURA_MUNDO,  0);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();
			
			glutSwapBuffers();
			break;

		case JOGO:

			glClear(GL_COLOR_BUFFER_BIT);
		    
		    if(teste == 0){
		      
		      link1.posicao.y = 10;
		      link1.posicao.x= LARGURA_MUNDO/2;  
		    }

		    criaInimigos();
		    desenhaLink(link1.posicao.x,link1.posicao.y);
		    if(teste_tiro == 1 ){

		    	desenhaTiro(tiro.posicao.x,tiro.posicao.y);
		    	printf("tiro\n");
		    }
		    glutSwapBuffers();
			break;

		case GAMEOVER:

			glClear(GL_COLOR_BUFFER_BIT);
			glColor3f(1,0,0);

			glPushMatrix();

				glTranslatef(LARGURA_MUNDO/10,ALTURA_MUNDO/2,0);
				glScalef(0.1, 0.1, 0.2); // diminui o tamanho do fonte
				//glRotatef(15, 0,0,1); // rotaciona o texto
				glLineWidth(5); // define a espessura da linha
				desenhaTexto(GLUT_STROKE_ROMAN,"GAME OVER !!!");

			glPopMatrix();
			glPushMatrix();

			glutSwapBuffers();
			break;

		default:
			break;
	}
}

void desenhaCena(void){

  glEnable(GL_TEXTURE_2D);   
	mudaTela();
}

void inicializa(void){
    // cor para limpar a tela
    glClearColor(1, 1, 1, 0);      // branco
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    idTexturaLink = carregaTextura("link.jpeg");
    idTexturaMenu = carregaTextura("menu.jpg");
    idTexturaInimigo1 = carregaTextura("inimigo1.jpeg");
    idTexturaInimigo2 = carregaTextura("inimigo2.jpeg");
    idTexturaInimigo3 = carregaTextura("inimigo3.jpeg");
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

// Callback de evento de teclado
void tecladoEsp(int special, int x, int y){
  switch(special){
    case GLUT_KEY_LEFT:
      teste =1;
      if(link1.posicao.x> 2 + LINK_LARG/2){
       link1.posicao.x -= NUM_MOVIMENTO;
      }
      break;
    case GLUT_KEY_RIGHT:
      teste =1;
      if(link1.posicao.x< (LARGURA_MUNDO - LINK_LARG + 2)){
        link1.posicao.x +=NUM_MOVIMENTO;
      }
      break;
    default:
       break;
   }
}

void teclado(unsigned char key, int x, int y){
   switch(key){
    case 27:
      exit(0);
      break;

    case 32:

    	if(teste_tiro==-1){
    		glutTimerFunc(PERIODO, movimentoTiro, 1);
	    	tiro.posicao.x = link1.posicao.x; tiro.posicao.y = (link1.posicao.y + 2);
	   	  	teste_tiro *= -1;
	   	}
        //desenhaTiro(link1.posicao.x , (link1.posicao.y + 2));
        //movimentoTiro();
      	//glutPostRedisplay();
	break;
	 
	 case 13:

     if(tela == MENU){
  	 	tela = JOGO;
  	 	glutTimerFunc(PERIODO , movimentoIni, 1);
  	  break;
     }

    default:
       break;
   }
}

// Rotina principal
int main(int argc, char **argv){
    // Acordando o GLUT
    glutInit(&argc, argv);

    // Definindo a versão do OpenGL que vamos usar
    glutInitContextVersion(1, 1);

    // Configuração inicial da janela do GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    // Abre a janela
    glutCreateWindow("Joguito");

    // Registra callbacks para alguns eventos
    glutDisplayFunc(desenhaCena);
    //glutTimerFunc(PERIODO/2 , movimentoTiro, 1);
    glutReshapeFunc(redimensiona);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(tecladoEsp);
    inicializa();

    // Entra em loop e nunca sai
    glutMainLoop();
    return 0;
}