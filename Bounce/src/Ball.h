#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#define MAX_VEL 0.02
#define MAX_POS 1.0
#define MIN_POS -1.0

// ========================= //

class Ball
{
    public:
        Ball(float x=0.0, float y=0.0, float radius=0.1);
        virtual ~Ball();
        void update();
        void randomizeSpeed();
        void draw();

    private:
        float X, Y;
        float Radius;
        float velX, velY;
        float R, G, B;
};

// ========================= //

#endif /* BALL_H_INCLUDED */
