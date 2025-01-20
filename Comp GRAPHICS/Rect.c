#include<stdio.h>
#include<GL/glut.h>

void Rectangle(int x, int y, int l, int b){
	glBegin(GL_LINES);
   
   glVertex2d(x,y);
   glVertex2d(x+l,y);
   
   glVertex2d(x+l,y);
   glVertex2d(x+l,y+b);
   
   glVertex2d(x+l,y+b);
   glVertex2d(x,y+b);
   
   glVertex2d(x,y);
   glVertex2d(x,y+b);
   
   glEnd();
	
}

void draw(){
   glClear(GL_COLOR_BUFFER_BIT);
   glBegin(GL_LINES);
   
   Rectangle(100,100,300,200);
   
   /*glVertex2d(100,100);
   glVertex2d(400,100);
   
   glVertex2d(100,100);
   glVertex2d(100,300);
   
   glVertex2d(400,300);
   glVertex2d(400,100);
   
   glVertex2d(400,300);
   glVertex2d(100,300);
   */
   glEnd();
   glFlush();

}




int main(int argc,char ** argv)
 {
        
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	
	glutCreateWindow("Bresnham Circle");
	
	glClearColor(0.0, 0.0, 0.0, 0);
	glColor3f(0.0, 1.0, 0.0);
	
	gluOrtho2D(0,640,0,480);
	
	glutDisplayFunc(draw);
	
	glutMainLoop();
	
	return 0;
 } 
