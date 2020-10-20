#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "inimigos.h"
#include "variaveisGlobais.h"
#include "tiroLink.h"
#include "desenhaJogo.h"
#include "estadoJogo.h"
#include "estadoTela.h"
#include "teclado.h"
#include "inicializando.h"
#include "texturas.h"

 int verificaExistenciaInimigosFinal(){


      for(int posIInimigo = (NUM_INI_HORI-1)-inimigosMortosPosI; posIInimigo >= 0 ;posIInimigo--){

        for(int posJInimigo = inimigosMortosPosJ; posJInimigo < NUM_INI_VERT; posJInimigo++){
            
            if(inimigos[posIInimigo][posJInimigo].posicao.x==0  &&  grava_Pos_Ini_MortoJ !=posJInimigo){
              grava_Pos_Ini_MortoJ = posJInimigo;
              return 1;
            }
            else{return 0;}    
        }
    }
}

int verificaExistenciaInimigosInicial(){

    for(int posIInimigo = iDirecao; iDirecao <NUM_INI_HORI ;iDirecao++){

        for(int posJInimigo = jDirecao;jDirecao < NUM_INI_VERT; jDirecao++){
            if(inimigos[posIInimigo][posJInimigo].posicao.x==0  && gravaJDirecao!=posJInimigo){
                
                gravaJDirecao = posJInimigo;
                return 1;
            }
            else{return 0;}

        }
    }
}



void verificaColisaoBorda(){
    


    if(direcao == 1){

        //verifica a Existencia dos Inimigos na Coluna Final
        inimigosMortosPosJ += verificaExistenciaInimigosFinal();
        //verifica se Inimigo Vivo  na coluna encostou no final Tela
        if((inimigos[(NUM_INI_HORI-1)-inimigosMortosPosI][inimigosMortosPosJ].posicao.x +LINK_LARG/2)==LARGURA_MUNDO){

            //Inverte a direcao
            direcao *= -1 ;   
            contador ++;

            // desece a Altura Inicial dos Inimigos apos cada tres toque no final da tela
            if(contador % 3 == 0){
                ALTURA_INICIAL_INIMIGOS-=INI_ALT;
            }
        }
       

        X_INICIAL_INIMIGOS++;
    }

    if(direcao == -1){
        
        jDirecao += verificaExistenciaInimigosInicial();

        if((inimigos[iDirecao][jDirecao].posicao.x - LINK_LARG/2) == 0){

            //Inverte a direcao
            direcao *= -1 ; 
            contador ++;  
            // desece a Altura Inicial dos Inimigos apos cada tres toque no final da tela
            if(contador % 3 == 0){
                ALTURA_INICIAL_INIMIGOS-=INI_ALT;
            }
        }
          
        
        X_INICIAL_INIMIGOS--;
    }

    
    //verifica se todos inimigos da coluna Final foram mortos
    if(inimigosMortosPosJ == 4){
      
        inimigosMortosPosJ =0;
        inimigosMortosPosI ++;
    }
    //verifica se todos inimigos da coluana Inicial foram mortos
    if(jDirecao==4){
        
        jDirecao=0;
        iDirecao++;
    }
      
    if(ALTURA_INICIAL_INIMIGOS<=20){
        verificaGameOver();
    }
  
    glutPostRedisplay();
    glutTimerFunc(PERIODO , verificaColisaoBorda, 1);
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


/*void movimentoTiroIni(){
  
  tiroIni.posicao.y--;
  if(tiroIni.posicao.y == 0){
    tiroIni.existencia = 0;
  }

  glutPostRedisplay();
  glutTimerFunc(PERIODO, movimentoTiroIni, 1);
}*/


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