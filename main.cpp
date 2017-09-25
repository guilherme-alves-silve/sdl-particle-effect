#include <iostream>
#include <cmath>
#include <SDL.h>
#include "Screen.h"
#include "Particle.h"
#include "Swarm.h"

using namespace std;
using namespace caveofprogramming;

int main(int argc, char** argv) {

    srand(time(NULL));

    Screen screen;
    if (!screen.init()) {
        return 1;
    }

    Swarm swarm;
    Particle* particles = swarm.getParticles();

    int halfWidth = screen.getScreenWidth() / 2;
    int halfHeight = screen.getScreenHeight() / 2;
    while (screen.processEvent()) {
        int elapsed = SDL_GetTicks();
        swarm.update(elapsed);
        //screen.clear();
        unsigned char green = (unsigned char) ((1 + sin(elapsed * 0.0001)) * 128);
        unsigned char red = (unsigned char) ((1 + sin(elapsed * 0.0002)) * 128);
        unsigned char blue = (unsigned char) ((1 + sin(elapsed * 0.0003)) * 128);

        for (int i = 0; i < swarm.N_PARTICLES; i++) {
            Particle particle = particles[i];
            int x = (particle.x + 1) * halfWidth;
            int y = particle.y * halfWidth + halfHeight;
            screen.setPixel(x, y, red, green, blue);
        }
        screen.blurBox();
        screen.update();
    }

    screen.close();

    return 0;
}

