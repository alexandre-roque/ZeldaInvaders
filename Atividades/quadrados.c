#include <GL/glew.h>      
#include <GL/freeglut.h> 
#include <stdio.h>
#include <time.h>

void desenhaQuadrado(int x, int y, float* cor){
  glColor3f(cor[0], cor[1], cor[2]);

    
    glBegin(GL_POLYGON);
        glVertex3f(x, y, 0);
        glVertex3f(x+50, y, 0);
        glVertex3f(x+50, y+50, 0);
        glVertex3f(x, y+50, 0);

    glEnd();
    glFlush();
}

void desenhaMinhaCena() {
    glClear(GL_COLOR_BUFFER_BIT);
    int aux=0,x=0,y=0;
    float cor[3]={0.6,0.6,0.6};
    while(aux==0){
      desenhaQuadrado(x,y,cor);
      if(x!=150){
        x+=75;
        if(x==75 && y==0){ cor[0]=1.0; cor[1]=1.0; cor[2]=0.0; }
        if(x==75 && y==75) { cor[0]=0.0; cor[1]=1.0; cor[2]=0.0; }
        if(x==75 && y==150){ cor[0]=1.0; cor[1]=0.7; cor[2]=0.7; }
        if(x==150 && y==0){ cor[0]=0.0; cor[1]=1.0; cor[2]=1.0; }
        if(x==150 && y==75){ cor[0]=1.0; cor[1]=0.0; cor[2]=0.0; }
        if(x==150 && y==150) { cor[0]=0.5; cor[1]=0.5; cor[2]=1.0; }
      desenhaQuadrado(x,y,cor);
      }
      if(x==150 && y==150){
        aux=1;
      }
      if(x==150){
        x=0;
        y+=75;
        if(x==0 && y==75){ cor[0]=0.0; cor[1]=0.0; cor[2]=1.0; }
        if(x==0 && y==150){ cor[0]=0.5; cor[1]=0.1; cor[2]=0.5; }
      desenhaQuadrado(x,y,cor);
      }
    }
}

void inicializa() {
    glClearColor(1, 1, 1, 1); 
    // desenho preenchido vs. contorno
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void redimensionada(int width, int height) {
   glViewport(0, 0, width, height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, 200, 0, 200, -1, 1);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void teclaPressionada(unsigned char key, int x, int y) {
    switch(key) {
    case 27:      
        exit(0);  
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

   glutCreateWindow("Questao 1");

   //srand(time(0));

   glutDisplayFunc(desenhaMinhaCena);
   glutReshapeFunc(redimensionada);  
   glutKeyboardFunc(teclaPressionada);


   inicializa();

   glutMainLoop();
   return 0;
}
/* behind the the scenes
    while(aux==0){
      desenhaQuadrado(x,y,cor);
      cor[0]= (float)rand()/RAND_MAX;
      cor[1]= (float)rand()/RAND_MAX;
      cor[2]= (float)rand()/RAND_MAX;
      if(x!=150){
        x+=75;
      desenhaQuadrado(x,y,cor);
      cor[0]= (float)rand()/RAND_MAX;
      cor[1]= (float)rand()/RAND_MAX;
      cor[2]= (float)rand()/RAND_MAX;
      }
      if(x==150 && y==150){
        aux=1;
      }
      if(x==150){
        x=0;
        y+=75;
      desenhaQuadrado(x,y,cor);
      cor[0]= (float)rand()/RAND_MAX;
      cor[1]= (float)rand()/RAND_MAX;
      cor[2]= (float)rand()/RAND_MAX;
      }
    }
    desenhaQuadrado(x,y,cor);

    x+=75;
    cor[0]=1.0; cor[1]=1.0; cor[2]=0.0;
    desenhaQuadrado(x,y,cor);

    x+=75;
    cor[0]=0.0; cor[1]=1.0; cor[2]=1.0;
    desenhaQuadrado(x,y,cor);

    x=0; y+=75;
    cor[0]=0.0; cor[1]=0.0; cor[2]=1.0;
    desenhaQuadrado(x,y,cor);

    x+=75;
    cor[0]=0.0; cor[1]=1.0; cor[2]=0.0;
    desenhaQuadrado(x,y,cor);

    x+=75;
    cor[0]=1.0; cor[1]=0.0; cor[2]=0.0;
    desenhaQuadrado(x,y,cor);

    x=0; y+=75;
    cor[0]=0.5; cor[1]=0.1; cor[2]=0.5;
    desenhaQuadrado(x,y,cor);

    x+=75;
    cor[0]=1.0; cor[1]=0.7; cor[2]=0.7;
    desenhaQuadrado(x,y,cor);

    x+=75;
    cor[0]=0.5; cor[1]=0.5; cor[2]=1.0;
    desenhaQuadrado(x,y,cor);*/