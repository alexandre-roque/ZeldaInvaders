#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>	
#include "variaveisGlobais.h"

	int contador = 0;
	int direcao = 1;
	int verifica = 92 ;//Posicao que de inicio do  deslocamento dos inimigos 
	int teste_tiro = -1;
	int direcao_link = 0;
	int frame_link = 1;
	int controladorTempo = 0;
	int valor = 10;
	int inimigosMortosPosI = 0;
	int inimigosMortosPosJ = 0;
	int gravaJDirecao=-1;
	int grava_Pos_Ini_MortoJ = -1 , iDirecao = 0;
	int jDirecao=0;
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
	GLuint idTexturaGameOver;
	GLuint idTexturaVitoria;

	objeto link1;
	objeto inimigos[9][5];
	objeto tiro;
	objeto tiroIni;
	enum Tela tela = MENU;
