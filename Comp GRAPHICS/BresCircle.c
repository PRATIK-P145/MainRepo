#include<stdio.h>
#include<GL/glut.h>




void BresCircle(int xc, int yc, int r){
	int x, y,d;
	
	x = 0;
	y = r;
	d = 3 - (2*r);
	
	
	
     do{
     
	glVertex2d(xc+x , yc+y);
	glVertex2d(xc+y , yc+x);
	glVertex2d(xc-x , yc+y);
	glVertex2d(xc+y , yc-x);
	glVertex2d(xc+x , yc-y);
	glVertex2d(xc-y , yc+x);
	glVertex2d(xc-x , yc-y);
	glVertex2d(xc-y , yc-x);
	
	
	
	if(d<0){
		x = x + 1;
		d = d + (4*x) +6;
	}
	else{
		x = x +1;
		y = y-1;
		d = d + (4*x) - (4*y) + 10;
	}
	  
	}while(y >= x);
	
	
	
}

void draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	//glVertex2d(320,240);
	BresCircle(320,240,200);
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

