#include <stdio.h>
#include <GL/glut.h>

int xa, ya, xb, yb;

void DDALine(int a, int b, int c, int d) {
    float dx = c - a;
    float dy = d - b;
    int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    float x = a, y = b;

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2d(x, y);
        x += xIncrement;
        y += yIncrement;
    }
    glEnd();
}

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    DDALine(xa, ya, xb, yb);
    glFlush();
}

int main(int argc, char **argv) {
    printf("Enter first point (xa, ya): ");
    scanf("%d%d", &xa, &ya);

    printf("Enter second point (xb, yb): ");
    scanf("%d%d", &xb, &yb);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("DDA Line Drawing");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    gluOrtho2D(0, 640, 0, 480);

    glutDisplayFunc(Draw);
    glutMainLoop();

    return 0;
}
