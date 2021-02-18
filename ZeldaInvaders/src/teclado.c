#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h> 
#include "variaveisGlobais.h"
#include "teclado.h"


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