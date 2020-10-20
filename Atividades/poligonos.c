#include <GL/glew.h>      
#include <GL/freeglut.h> 
#include <stdio.h>
#include <time.h>
#include <math.h>

float numVertice=3;
int modo=-1;
int status=-1;

void desenhaPoligono() {
  int x,y;
  y=x=50;
  int raio=30;
  if(status==-1){
    glBegin(GL_LINE_LOOP);
      for(int i=0;i<=numVertice;i++){
      glVertex3f((raio*cos(2*M_PI*i/numVertice))+50,(raio*sin(2*M_PI*i/numVertice))+50, 0);
    }
    glEnd();
    glFlush();
  }
  if(status==1){
    glBegin(GL_TRIANGLE_FAN);
      glVertex3f(50,50,0);
      for(int i=0;i<=numVertice;i++){
      glVertex3f((raio*cos(2*M_PI*i/numVertice))+50,(raio*sin(2*M_PI*i/numVertice))+50, 0);
    }
    glEnd();
    glFlush();
  }
}


void desenhaMinhaCena() {
  glClear(GL_COLOR_BUFFER_BIT);
  if(modo==1){
    glColor3f(0, 0, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  if(modo==-1){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 1, 1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
  glColor3f(0, 1, 0);
  glLineWidth(3.0f);
  desenhaPoligono();
  }

void inicializa() {
    glClearColor(1, 1, 1, 1); 
    // desenho preenchido vs. contorno
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
    case '+':
        numVertice++;
        glutPostRedisplay();
        break;
    case '-':
        numVertice--;
        glutPostRedisplay();
        break;
    case 'c':
        modo=modo*-1;
        glutPostRedisplay();
        break;
    case 'v':
        status=status*-1;
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

   glutCreateWindow("Questao 3");

   //srand(time(0));

   glutDisplayFunc(desenhaMinhaCena);
   glutReshapeFunc(redimensionada);  
   glutKeyboardFunc(teclaPressionada);


   inicializa();

   glutMainLoop();
   return 0;
}