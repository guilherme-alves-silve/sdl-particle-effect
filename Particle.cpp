#include "Particle.h"
#include <iostream>
#include <cmath>

using namespace std;

namespace caveofprogramming {

    Particle::Particle() {
        init();
    }

    void Particle::init() {
        x = 0;
        y = 0;
        direction = (2 * M_PI * rand()) / RAND_MAX;
        speed = (0.04 * rand()) / RAND_MAX;

        speed *= speed;
    }

    void Particle::update(int interval) {
        
        if (x < -1 || x > 1 || y < -1 || y > 1 || (rand() < RAND_MAX / 100)) {
            init();
        }

        direction += interval * 0.0003;

        double xspeed = speed * cos(direction);
        double yspeed = speed * sin(direction);
        x += xspeed * interval;
        y += yspeed * interval;
    }
}