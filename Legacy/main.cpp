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
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//    glMatrixMode( GL_PROJECTION );
//    glLoadIdentity();
//    glFrustum( -1, 1, -1, 1, 1, 1000 );
//    glMatrixMode( GL_MODELVIEW );
//    glLoadIdentity();
//    glTranslatef( 0, 0, -3 );
    glEnable(GL_DEPTH_TEST);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(45, 1, 0, 3);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(5, 0, -5, 0, 0, 0, 0, 1, 0);

    glBegin( GL_TRIANGLE_FAN );
        glColor3f( 1, 0, 0 );
        glVertex3f(-1, -1, 0);
        glVertex3f(-1, 1, 0);
        glVertex3f(-1, 1, 1);
        glVertex3f(-1, -1, 1);
    glEnd();

    glBegin( GL_TRIANGLE_FAN );
        glColor3f( 0, 0, 1 );
        glVertex3f(-1, -1, 0);
        glVertex3f(-1, -1, 1);
        glVertex3f(1, -1, 1);
        glVertex3f(1, -1, 0);
    glEnd();

    glBegin( GL_TRIANGLE_FAN );
        glColor3f( 0, 0.5, 0 );
        glVertex3f( -1, -1, 1 ); 
        glVertex3f( -1, 1, 1 );  
        glVertex3f( 1, 1, 1 );   
        glVertex3f( 1, -1, 1 ); 
    glEnd();

    glBegin( GL_TRIANGLE_FAN );
        glColor3f( 0, 0, 0.5 );
        glVertex3f(-1, 1, 0);
        glVertex3f(-1, 1, 1);
        glVertex3f(1, 1, 1);
        glVertex3f(1, 1, 0);
    glEnd();

    glBegin( GL_TRIANGLE_FAN );
        glColor3f( 0.5, 0, 0 );
        glVertex3f(1, -1, 0);
        glVertex3f(1, 1, 0);
        glVertex3f(1, 1, 1);
        glVertex3f(1, -1, 1);
    glEnd();

    glBegin( GL_TRIANGLE_FAN );
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
