#include <GL/glut.h>
#include <stdio.h>

int clickCount = 0;
int x1, y1, x2, y2;  // Coordinates of the two points

void drawLine() {
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (clickCount == 2) {  // Draw the line only after two points are selected
        glColor3f(0.0, 0.0, 0.0);
        drawLine();
    }
    glFlush();
}

void mouseCallback(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {  // On left-click
        if (clickCount == 0) {
            x1 = x;
            y1 = 480 - y;  // Invert y to match OpenGL coordinates
            clickCount++;
            printf("First Point: (%d, %d)\n", x1, y1);
        } else if (clickCount == 1) {
            x2 = x;
            y2 = 480 - y;  // Invert y to match OpenGL coordinates
            clickCount++;
            printf("Second Point: (%d, %d)\n", x2, y2);
            glutPostRedisplay();  // Redraw the window
        }
    }
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // White background
    glColor3f(0.0, 0.0, 0.0);         // Black drawing color
    gluOrtho2D(0, 640, 0, 480);       // Set the coordinate system
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Draw Line Using Mouse");

    init();

    glutDisplayFunc(display);          // Register display callback
    glutMouseFunc(mouseCallback);      // Register mouse callback

    glutMainLoop();
    return 0;
}
