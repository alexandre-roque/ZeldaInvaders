CC = gcc
OPCOES_COMPILADOR = -lglut -lGLU -lGL -lGLEW -lSOIL -lm
SRC = ./src
OBJ = ./obj
BIN = ./bin
IMG = ./imagensJogo
LIBRARIES = ./libraries

$(OBJ)/%.o:	$(SRC)/%.c $(LIBRARIES)/%.h
	$(CC) -c $< -I $(LIBRARIES) -I $(IMG) -o $@ $(OPCOES_COMPILADOR)

all:	lib
	$(CC) $(BIN)/v6.c $(OBJ)/*.o -I $(LIBRARIES) -I $(IMG) -o $(BIN)/executavel $(OPCOES_COMPILADOR)

lib:	\
	$(OBJ)/desenhaJogo.o	\
	$(OBJ)/estadoJogo.o	\
	$(OBJ)/estadoTela.o	\
	$(OBJ)/inicializando.o	\
	$(OBJ)/inimigos.o	\
	$(OBJ)/teclado.o	\
	$(OBJ)/texturas.o	\
	$(OBJ)/tiroLink.o	\
	$(OBJ)/variaveisGlobais.o	\

run:
	$(BIN)/./executavel
	
clean:			
	rm $(OBJ)/*.o
	rm $(BIN)/executavel
