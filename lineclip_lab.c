#include<GL/glut.h>
#include<stdio.h>
int xmin,ymin,xmax,ymax;
int outcode1[4];
int outcode2[4];
int xa, ya, xb,yb;
int accepted = 1;
int PA = 1;

void ddaLine(int xa, int ya, int xb, int yb){
	glBegin(GL_LINES);
	glVertex2d(xa,ya);
	glVertex2d(xb,yb);
	glEnd();
}
void gen_outcode(int outcode[4], int x, int y){
	for(int i=0; i<4; i++){
		outcode[i] = 0;
	}
	
	if(x< xmin){
		outcode[3] = 1;
	}
	else if(x > xmax){
		outcode[2] = 1;
	}
	
	if(y < ymin){
		outcode[1] = 1;
	}
	else if(y > ymax){
		outcode[0] = 1;
	}
}


void draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	
	ddaLine(xmin, ymin,xmax, ymin);
	ddaLine(xmax, ymin,xmax, ymax);
	ddaLine(xmax, ymax,xmin, ymax);
	ddaLine(xmin, ymax,xmin, ymin);
	
	glColor3f(0,0,1);
	ddaLine( xa, ya, xb,yb);
	
	
	
	glFlush();

}

int main(int argc, char** argv){
	
	//printf("AND operation :%d",c);
	//scanf("%d %d", &xmax,&ymax);

	printf("Enter Xmin & Ymin :\n");
	scanf("%d %d", &xmin,&ymin);
	printf("Enter Xmax & Ymax :\n");
	scanf("%d %d", &xmax,&ymax);
	

	
	printf("Enter Line (xa,ya) & (xb,yb):\n");
	scanf("%d %d %d %d",  &xa, &ya, &xb, &yb);
	
	gen_outcode(outcode1,xa,ya);
	gen_outcode(outcode2,xb,yb);
	
	printf("Outcode_1 is :");
	for(int i=0; i<4; i++){
		printf("\t%d",outcode1[i]);
	}
	printf("\n");
	
	printf("Outcode_2 is :");
	for(int i=0; i<4; i++){
		printf("\t%d",outcode2[i]);
	}
	printf("\n");
	
	for(int i=0; i<4; i++){
		if((outcode1[i]==1 || outcode2[i]) ==1){
			accepted = 0;
			break;
		}
	}
	
	if(accepted){printf("\n Accepted"); }
	else{printf("\nRejected");}
	
	for(int i=0; i<4; i++){
		if((outcode1[i] & outcode2[i]) ==1){
			PA = 0;
			break;
		}
	}
	
	if(PA){printf("\nPartially Accepted"); }
	else{printf("\n completly Rejected");}
	

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
	
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Line Clipping");
	
	glClearColor(0,0,0,0);
	glColor3f(0,1,0);
	
	gluOrtho2D(0,640,0,480);
	
	glutDisplayFunc(draw);

	glutMainLoop();



return 0;
}

