#ifndef BOUNCE_H_INCLUDED
#define BOUNCE_H_INCLUDED

#include "GLRenderer.h"

// ========================== //

class Bounce {
    public:
        Bounce();
        void run();
        virtual ~Bounce ();

    private:
        bool running;
        Renderer renderer;
};

// ========================== //

#endif /* BOUNCE_H_INCLUDED */
