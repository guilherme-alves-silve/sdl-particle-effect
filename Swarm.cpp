#include "Swarm.h"

namespace caveofprogramming {

    Swarm::Swarm(): lastTime(0) {
        particles = new Particle[N_PARTICLES];
    }

    Swarm::~Swarm() {
        delete [] particles;
    }

    Particle* Swarm::getParticles() {
        return particles;
    }

    void Swarm::update(int elapsedTime) {
        
        int interval = elapsedTime - lastTime;
        
        for (int i = 0; i < N_PARTICLES; i++) {
            particles[i].update(interval);
        }
        
        lastTime = elapsedTime;
    }

}