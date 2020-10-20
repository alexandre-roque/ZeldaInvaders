#ifndef VARIAVEISGLOBAIS_H_INCLUED
#define VARIAVEISGLOBAIS_H_INCLUED

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
	#define TIRO_LARG 4
	#define TIRO_ALT 6

	int contador;
	int direcao;
	int verifica;//Posicao que de inicio do  deslocamento dos inimigos 
	int teste_tiro;
	int direcao_link;
	int frame_link;
	int controladorTempo;
	int valor;
	int inimigosMortosPosI,inimigosMortosPosJ;
	int gravaJDirecao,grava_Pos_Ini_MortoJ,iDirecao,jDirecao;
	float quadroInimigo;
	int quadroAtual;
	int quadroAtualIni3;


	GLint teste;
	GLint X_INICIAL_INIMIGOS;
	GLint ALTURA_INICIAL_INIMIGOS;

	GLuint idTexturaLink;
	GLuint idTexturaInimigo1;
	GLuint idTexturaInimigo2;
	GLuint idTexturaInimigo3;
	GLuint idTexturaMenu;
	GLuint idTexturaFundo;
	GLuint idTexturaFlecha;
	GLuint idTexturaGameOver;
	GLuint idTexturaVitoria;
	
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

	enum Tela { MENU, JOGO, VITORIA, GAMEOVER };
	enum Tela tela;

#endif
