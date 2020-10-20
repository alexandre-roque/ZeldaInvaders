#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>	
#include <math.h>
#include "variaveisGlobais.h"
#include "estadoJogo.h"


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

void verificaGameOver(){
  link1.raio = LINK_LARG;
  for(int i = 0;i < NUM_INI_HORI;i++){
    for(int j = 0;j < NUM_INI_VERT; j++){
      inimigos[i][j].raio = INI_LARG;
      int dx = link1.posicao.x - inimigos[i][j].posicao.x;
      int dy = link1.posicao.y - inimigos[i][j].posicao.y;
      double distancia = sqrt((dx * dx) + (dy * dy));
      if(distancia < link1.raio + inimigos[i][j].raio) {
        link1.existencia = 0;
        tela = GAMEOVER;
      }
      if(inimigos[i][j].existencia==1 && inimigos[i][j].posicao.y<=0){
      	link1.existencia = 0;
        tela = GAMEOVER;
      }
    }
  }
}
