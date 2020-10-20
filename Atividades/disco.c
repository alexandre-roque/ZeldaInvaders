#include <GL/glew.h>      
#include <GL/freeglut.h> 
#include <stdio.h>
#include <time.h>

int modo = -1;

void desenhaMinhaCena() {
  glLineWidth(1.5f);
  if(modo==1){
    glColor3f(0, 0, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  if(modo==-1){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 1, 1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  glBegin(GL_TRIANGLE_FAN);
        glVertex3f(20, 20, 0);
        glVertex3f(30, 30, 0);
        glVertex3f(30, 70, 0);
        glVertex3f(20, 80, 0);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(20, 80, 0);
        glVertex3f(30, 70, 0);
        glVertex3f(70, 70, 0);
        glVertex3f(80, 80, 0);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(80, 80, 0);
        glVertex3f(70, 70, 0);
        glVertex3f(70, 30, 0);
        glVertex3f(80, 20, 0);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(20, 20, 0);
        glVertex3f(30, 30, 0);
        glVertex3f(70, 30, 0);
        glVertex3f(80, 20, 0);
    glEnd();

    glFlush();
  }

void inicializa() {
    glClearColor(1, 1, 1, 1); 
    // desenho preenchido vs. contorno
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void redimensionada(int width, int height) {
   glViewport(0, 0, width, height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, 100, 0, 100, -1, 1);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void teclaPressionada(unsigned char key, int x, int y) {
    switch(key) {
    case 27:      
        exit(0);  
        break;
    case 99:
        modo=modo*(-1);
        glutDisplayFunc(desenhaMinhaCena);
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);

   glutInitContextVersion(1, 1);
   glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100);

   glutCreateWindow("Questao 2");

   //srand(time(0));

   glutDisplayFunc(desenhaMinhaCena);
   glutReshapeFunc(redimensionada);  
   glutKeyboardFunc(teclaPressionada);


   inicializa();

   glutMainLoop();
   return 0;
}