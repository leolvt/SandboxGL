#include <cstdlib>
#include <ctime>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Ball.h"

Ball::Ball(float x, float y, float radius)
{
    X = x;
    Y = y;
    Radius = radius;
    R = drand48();
    G = drand48();
    B = drand48();
    velX = (-1.0 + 2*drand48()) * MAX_VEL;
    velY = (-1.0 + 2*drand48()) * MAX_VEL;
}

// ========================== //

Ball::~Ball()
{

}

// ========================== //

void Ball::update()
{
    // Increase Position
    X += velX;
    Y += velY;

    // Check Bounds
    if (X >= 1.0 || X <= -1.0)
    {
        velX *= -1;
    }

    if (Y >= 1.0 || Y <= -1.0)
    {
        velY *= -1;
    }
}

// ========================== //

void Ball::randomizeSpeed()
{
    velX = (-1.0 + 2*drand48()) * MAX_VEL;
    velY = (-1.0 + 2*drand48()) * MAX_VEL;
}

// ========================== //

void Ball::draw()
{
    // Draw Circle using GL_TRIANGLE_FAN
    const float PI = 3.1415926f;
    const int nVertices = 36;
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(R, G, B);
        glVertex2f(X, Y);
        for (int i = 0; i <= nVertices; i++) {
            float deg = 2*PI / nVertices * i;
            float vX = X + Radius * glm::cos(deg);
            float vY = Y + Radius * glm::sin(deg);
            glVertex2f(vX, vY);
        }
    glEnd();
}

// ========================== //

