#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

using namespace std;

bool init_resources()
{
    return true;
}

void display()
{
    glClear( GL_COLOR_BUFFER_BIT );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum( -1, 1, -1, 1, 1, 1000 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef( 0, 0, -3 );

    glBegin( GL_POLYGON );
        glColor3f( 0, 1, 0 );
        glVertex3f( -1, -1, 0 ); 
        glVertex3f( -1, 1, 0 );  
        glVertex3f( 1, 1, 0 );   
        glVertex3f( 1, -1, 0 ); 
    glEnd();

    glutSwapBuffers();
}

void free_resources()
{

}

int main(int argc, char *argv[]) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutCreateWindow("My First Triangle");

    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK) {
        cerr << "Error: " << glewGetErrorString(glew_status) << endl;
        return 1;
    }

    if (init_resources()) {
        glutDisplayFunc(display);
        glutMainLoop();
    }

    free_resources();
    return 0;
}
