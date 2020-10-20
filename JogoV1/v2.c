#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
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

int contador = 0;
int direcao = 1;
int verifica = 92 ;//Posicao que de inicio do  deslocamento dos inimigos 
int teste_tiro = 1;

GLint teste =0;
GLint X_INICIAL_INIMIGOS = 13;
GLint ALTURA_INICIAL_INIMIGOS = 80;

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


void movimentoIni(){
  //direita]
  if(direcao == 1){

    if(verifica != (LARGURA_MUNDO - 2)){// deslIniFinalTela==112

        X_INICIAL_INIMIGOS++;

        //sleep(1);
       // glutPostRedisplay();

        if(verifica == (LARGURA_MUNDO - 3)){//delsIniFinalTela-1==111 PARA MUDAR A DIRECAO PARA O SENTIDO OPOSTO
          direcao*=-1; 
          contador++;
          if(contador % 3 == 0){
            ALTURA_INICIAL_INIMIGOS-=INI_ALT;
          }
        }
        verifica++;
    }
  }

  if(direcao == -1){

    if(verifica != LARGURA_MUNDO/2 ){//deslIniInicioTela==78

        X_INICIAL_INIMIGOS--;
        //sleep(1);
       // glutPostRedisplay();

        if(verifica == 82){//deslIniInicioTela==82 mesma coisa da de cima kkk
          direcao*=-1;
          contador++;
          if(contador % 3 == 0){
            ALTURA_INICIAL_INIMIGOS-=INI_ALT;
          }
        }
        verifica--;
    }
  }
   glutPostRedisplay();
  glutTimerFunc(PERIODO , movimentoIni, 1);
}

void movimentoTiro(){
  teste_tiro*=-1;

  tiro.posicao.y++;

  glutPostRedisplay();
  glutTimerFunc(PERIODO , movimentoTiro, 1);
}

 
int desenhaLink(GLint x, GLint y){
    glColor3f(1, 0, 0);

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
  glPopMatrix();                  // Importante!!
  
}

void desenhaCena(void){
    glClear(GL_COLOR_BUFFER_BIT);
    
    if(teste == 0){
      link1.posicao.y = 10;
      link1.posicao.x= LARGURA_MUNDO/2;
    }

    desenhaLink(link1.posicao.x,link1.posicao.y);
    criaInimigos();
    //movimentoIni();
    glutSwapBuffers();
    //glutPostRedisplay();
}

void inicializa(void){
    // cor para limpar a tela
    glClearColor(1, 1, 1, 0);      // branco
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
    if(teste_tiro == 1){
      tiro.posicao.x = link1.posicao.x; tiro.posicao.y = (link1.posicao.y + 2);
      desenhaTiro(link1.posicao.x , (link1.posicao.y + 2));
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
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    // Configuração inicial da janela do GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    // Abre a janela
    glutCreateWindow("Joguito");

    // Registra callbacks para alguns eventos
    glutDisplayFunc(desenhaCena);
    glutTimerFunc(PERIODO , movimentoIni, 1);
    glutReshapeFunc(redimensiona);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(tecladoEsp);
    inicializa();

    // Entra em loop e nunca sai
    glutMainLoop();
    return 0;
}