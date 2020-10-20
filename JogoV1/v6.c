#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
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
#define TIRO_LARG 6
#define TIRO_ALT 6

int contador = 0;
int direcao = 1;
int verifica = 92 ;//Posicao que de inicio do  deslocamento dos inimigos 
int teste_tiro = -1;
int direcao_link = 0;
int frame_link = 1;
int controladorTempo = 0;
int valor = 10;
int i=0,j=0;
int gravaJDirecao=-1,gravaJ=-1,iDirecao=0,jDirecao=0;
float quadroInimigo = 0.2;


GLint teste =0;
GLint X_INICIAL_INIMIGOS = 13;
GLint ALTURA_INICIAL_INIMIGOS = 80;

GLuint idTexturaLink;
GLuint idTexturaInimigo1;
GLuint idTexturaInimigo2;
GLuint idTexturaInimigo3;
GLuint idTexturaMenu;
GLuint idTexturaFundo;
GLuint idTexturaFlecha;

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

enum Tela { MENU, JOGO, VITORIA, GAMEOVER };
enum Tela tela = MENU;

typedef struct{
  
  GLint x,y;

}vetor2d;

typedef struct{
  vetor2d posicao;
  int existencia;
  int raio;

}objeto;

objeto link1;
objeto inimigos[9][5];
objeto tiro;
objeto tiroIni;

int desenhaInimigo(GLint x, GLint y, GLint j){
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
          glTexCoord2f(0 , 0); glVertex2f(-LINK_LARG/2, -LINK_ALT/2); // v3---v2
          glTexCoord2f(0.09 , 0); glVertex2f( LINK_LARG/2, -LINK_ALT/2); // |     |
          glTexCoord2f(0.09 , 0.5); glVertex2f( LINK_LARG/2,  LINK_ALT/2); // |     |
          glTexCoord2f(0.0 , 0.5); glVertex2f(-LINK_LARG/2,  LINK_ALT/2); // v0---v1
          //glTexCoord2f(0 , 0); glVertex2f(-INI_LARG/2, -INI_ALT/2); glTexCoord2f(0.09 , 0); glVertex2f( INI_LARG/2, -INI_ALT/2);glTexCoord2f(0.09 , 0.5); glVertex2f( INI_LARG/2,  INI_ALT/2); glTexCoord2f(0.0 , 0.5); glVertex2f(-INI_LARG/2,  INI_ALT/2); // v0---v1
        glEnd();
      glPopMatrix();

      }

    //glutPostRedisplay(); 
      if(j==0 || j==1 || j==2){
        glPushMatrix();                 // Importante!!
            glTranslatef(x, y, 0);
            glBegin(GL_TRIANGLE_FAN);
              glTexCoord2f(quadroInimigo - 0.2 , 0); glVertex2f(-LINK_LARG/2, -LINK_ALT/2); // v3---v2
              glTexCoord2f(quadroInimigo , 0); glVertex2f( LINK_LARG/2, -LINK_ALT/2); // |     |
              glTexCoord2f(quadroInimigo , 1); glVertex2f( LINK_LARG/2,  LINK_ALT/2); // |     |
              glTexCoord2f(quadroInimigo - 0.2 , 1); glVertex2f(-LINK_LARG/2,  LINK_ALT/2); // v0---v1
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

void verificaGameOver(){
  link1.raio = LINK_LARG;
  for(int i = 0;i < NUM_INI_HORI;i++){
    for(int j = 0;j < NUM_INI_VERT; j++){
      inimigos[i][j].raio = INI_LARG;
      int dx = link1.posicao.x - inimigos[i][j].posicao.x;
      int dy = link1.posicao.y - inimigos[i][j].posicao.y;
      double distancia = sqrt(dx * dx + dy * dy);
      if(distancia < link1.raio + inimigos[i][j].raio) {
        link1.existencia = 0;
        tela = GAMEOVER;
      }
    }
  }
}
 int num(){

      for(int i1 = (NUM_INI_HORI-1)-i; i1 >= 0 ;i1--){

        for(int j1 = j;j1< NUM_INI_VERT; j1++){
        
        if(inimigos[i1][j1].posicao.x==0  && gravaJ!=j1){

          gravaJ=j1;
          return 1;
        }
        else{return 0;}
      
      }
    }
}

int num1(){

      for(int i2 = iDirecao; iDirecao <NUM_INI_HORI ;iDirecao++){

        for(int j2 = jDirecao;jDirecao < NUM_INI_VERT; jDirecao++){
          if(inimigos[i2][j2].posicao.x==0  && gravaJDirecao!=j2){
            gravaJDirecao=j2;
            return 1;
        }
        else{return 0;}
      
      }
    }
}



void verificaColisaoBorda(){
      
      if(direcao == 1){
        j+=num();
        if((inimigos[8-i][j].posicao.x + LINK_LARG/2) == LARGURA_MUNDO){
          direcao*=-1; 
          contador++;
          if(contador % 3 == 0){
            ALTURA_INICIAL_INIMIGOS-=INI_ALT;
          }
        }
        X_INICIAL_INIMIGOS++;
      }

      if(direcao == -1){
        
        jDirecao += num1();

        if((inimigos[iDirecao][jDirecao].posicao.x - LINK_LARG/2) == 0){
          direcao*=-1; 
          contador++;
          if(contador % 3 == 0){
            ALTURA_INICIAL_INIMIGOS-=INI_ALT;
          }
        }
        X_INICIAL_INIMIGOS--;
      }
      if(jDirecao==4){
        jDirecao=0;
        iDirecao++;
      }

    if(j==4){
      j=0;
      i++;
    }
    if(ALTURA_INICIAL_INIMIGOS<=20){
    verificaGameOver();
    }
  
  glutPostRedisplay();
  glutTimerFunc(PERIODO , verificaColisaoBorda, 1);
}

void verificaVitoria(){
  int contador = 0;
  for(int i = 0;i < NUM_INI_HORI;i++){
    for(int j = 0;j < NUM_INI_VERT; j++){
      if(inimigos[i][j].existencia == 0){
        contador++ ;
      }
      else
        contador = 0;
    }
  }
  if(contador == (NUM_INI_HORI*NUM_INI_VERT)){
    tela = VITORIA;
  }
}

/*void movimentoIni(){
  //direita]
  if(direcao == 1){

    if(verifica != (LARGURA_MUNDO - 2)){// deslIniFinalTela==112

        X_INICIAL_INIMIGOS++;

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
  if(ALTURA_INICIAL_INIMIGOS<=20){
    verificaGameOver();
  }

   glutPostRedisplay();
  glutTimerFunc(PERIODO , movimentoIni, 1);
}
*/
void movimentoTiroLink(){
  
  tiro.posicao.y++;
  if(tiro.posicao.y == ALTURA_MUNDO){
    tiro.existencia = 0;
  }

  glutPostRedisplay();
  glutTimerFunc(PERIODO/3, movimentoTiroLink, 1);
}

void movimentoTiroIni(){
  
  tiroIni.posicao.y--;
  if(tiroIni.posicao.y == 0){
    tiroIni.existencia = 0;
  }

  glutPostRedisplay();
  glutTimerFunc(PERIODO, movimentoTiroIni, 1);
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

int desenhaTiro(GLint x, GLint y){
  if(tiro.existencia == 1){
    verificaColisaoTiroLink();
    glColor3f(1, 1, 1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, idTexturaFlecha);
    glPushMatrix();                 // Importante!!
      glTranslatef(x, y, 0);
      glBegin(GL_TRIANGLE_FAN);
          glTexCoord2f(0 , 0); glVertex2f(-TIRO_LARG/2, -TIRO_ALT/2); // v3---v2
          glTexCoord2f(1 , 0); glVertex2f( TIRO_LARG/2, -TIRO_ALT/2); // |     |
          glTexCoord2f(1 , 1); glVertex2f( TIRO_LARG/2,  TIRO_ALT/2); // |     |
          glTexCoord2f(0 , 1); glVertex2f(-TIRO_LARG/2,  TIRO_ALT/2); // v0---v1
      glEnd();
      glEnd();
    glPopMatrix();                   // Importante!!
  }
}

void desenhaTexto(void *font, char *string){  
  // Exibe caractere a caractere
  while(*string)
    glutStrokeCharacter(GLUT_STROKE_ROMAN,*string++); 
}


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
            glColor3f(1,0,0);

            glPushMatrix();
                glTranslatef(LARGURA_MUNDO/10,ALTURA_MUNDO/2,0);
                glScalef(0.1, 0.1, 0.2); // diminui o tamanho do fonte
                //glRotatef(15, 0,0,1); // rotaciona o texto
                glLineWidth(5); // define a espessura da linha
                desenhaTexto(GLUT_STROKE_ROMAN,"GAME OVER !!!");
                glPopMatrix();
            glPushMatrix();

            desenhaLink(link1.posicao.x , link1.posicao.y);
            glutSwapBuffers();
        break;

        case VITORIA:

            glClear(GL_COLOR_BUFFER_BIT);
            glColor3f(1,0,0);

            glPushMatrix();
                glTranslatef(LARGURA_MUNDO/10,ALTURA_MUNDO/2,0);
                glScalef(0.1, 0.1, 0.2); // diminui o tamanho do fonte
                //glRotatef(15, 0,0,1); // rotaciona o texto
                glLineWidth(5); // define a espessura da linha
                desenhaTexto(GLUT_STROKE_ROMAN,"VITORIA !!!");
                glPopMatrix();
            glPushMatrix();

            glutSwapBuffers();
        break;

        default:
        break;
    }
}

void desenhaCena(void){
   
    mudaTela();
}

void inicializa(void){
    // cor para limpar a tela branco
    glClearColor(1, 1, 1, 0);
    //Registra Callback do Tiro
    glutTimerFunc(PERIODO/3, movimentoTiroLink, 1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    idTexturaLink = carregaTextura("spritelink.png");
    idTexturaMenu = carregaTextura("menu.jpg");
    idTexturaInimigo1 = carregaTextura("spriteinimigo1.png");
    idTexturaInimigo2 = carregaTextura("spriteinimigo2.png");
    idTexturaInimigo3 = carregaTextura("spriteinimigo3.png");
    idTexturaFundo = carregaTextura("fundo.jpg");
    idTexturaFlecha = carregaTextura("flecha.png");
    
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

// Callback de evento de teclado Especial
void tecladoEsp(int special, int x, int y){

    switch(special){
        
        case GLUT_KEY_LEFT:
            if(tela == JOGO){
                frame_link*=-1;
                direcao_link = 1;
                teste =1;
                if(link1.posicao.x> 2 + LINK_LARG/2){
                    link1.posicao.x -= NUM_MOVIMENTO;
                }
            }
        break;

        case GLUT_KEY_RIGHT:
            if(tela == JOGO){
                frame_link*=-1;
                direcao_link = -1;
                teste =1;
                if(link1.posicao.x< (LARGURA_MUNDO - LINK_LARG + 2)){
                link1.posicao.x +=NUM_MOVIMENTO;
                }
            }
        break;
        
        default:
        break;
    }
}

// Callback de evento de teclado
void teclado(unsigned char key, int x, int y){
  
    switch(key){
        
        case 27:
            exit(0);
        break;

        case 32:
            if(tela == JOGO){
                if(tiro.existencia == 0){
                  direcao_link = 0;
                  tiro.existencia = 1;
                  tiro.posicao.x = link1.posicao.x; tiro.posicao.y = (link1.posicao.y + 2);
                }
            }
        break;
       
       case 13:
            if(tela == MENU){
                tela = JOGO;
                glutTimerFunc(PERIODO , verificaColisaoBorda, 1);
            }    
        break;

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
    inicializa();
    glutDisplayFunc(desenhaCena);
    //glutTimerFunc(PERIODO/2 , movimentoTiroLink, 1);
    glutReshapeFunc(redimensiona);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(tecladoEsp);

    // Entra em loop e nunca sai
    glutMainLoop();
    return 0;
}
