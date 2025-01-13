#include<stdio.h>
#include<GL/glut.h>

int xa, ya, xb, yb;

void DDALine(int a,int b, int c, int d){
  glBegin(GL_LINES);
  glVertex2d(a,b);
  glVertex2d(c,d);
}

void Draw()
{
  glClear(GL_COLOR_BUFFER_BIT);
  DDALine();

  glEnd();
  glFlush();

}


int main(int argc,char** argv)
{

printf("First :");
scanf("%d%d",xa,ya);

printf("Second :");
scanf("%d%d",xb,yb);

glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowPosition(0,0);
glutInitWindowSize(640,480);
glutCreateWindow("Window1");
glClearColor(1.0,1.0,1.0,0);
glColor3f(0.1,0.1,0.1);
gluOrtho2D(0,640,0,480);

glutDisplayFunc(Draw);
glutMainLoop();



return 0;




}
