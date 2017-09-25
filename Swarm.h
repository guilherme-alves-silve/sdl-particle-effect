#ifndef SWARM_H
#define SWARM_H

#include "Particle.h"

namespace caveofprogramming {

    class Swarm {
    public:
        const static int N_PARTICLES = 5000;
        Swarm();
        Particle* getParticles();
        virtual ~Swarm();
        void update(int elapsedTime);
    private:
        Particle* particles;
        int lastTime;
    };

}

#endif /* SWARM_H */

