#ifndef BOUNCE_H_INCLUDED
#define BOUNCE_H_INCLUDED

#include <vector>
#include "Ball.h"

// ========================== //

class Bounce {
    public:
        Bounce(unsigned int numBalls = 10);
        void run();
        virtual ~Bounce ();

    private:
        std::vector<Ball> balls;
};

// ========================== //

#endif /* BOUNCE_H_INCLUDED */
