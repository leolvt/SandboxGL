#include <iostream>

#include "Bounce.h"

int main(int argc, const char *argv[]) {

    // Create a new Bounce 
    Bounce bounce = Bounce(100);
    bounce.run();
    
    // ANSI C requires this!
    return 0;
}
