#ifndef PARTICLE_H
#define PARTICLE_H

#include <cstdlib>

namespace caveofprogramming {

    struct Particle {
        double x;
        double y;
    private:
        double direction;
        double speed;
        void init();
    public:
        Particle();
        void update(int interval);
    };

}

#endif /* PARTICLE_H */

