#ifndef EMITTER_H
#define EMITTER_H

#include <particle.h>
#include <vector>

class Emitter
{
public:
    Emitter();
    ~Emitter();
    std::vector<Particle *> particleList;

    void addParticle();

    void update();
};

#endif // EMITTER_H
