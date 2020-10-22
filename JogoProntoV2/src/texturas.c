#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "variaveisGlobais.h"
#include "texturas.h"

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
