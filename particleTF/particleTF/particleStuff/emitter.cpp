#include "emitter.h"
#include <iostream>
Emitter::Emitter()
{

}

Emitter::~Emitter()
{
    // if(!particleList.empty()) particleList.clear();
}

void Emitter::addParticle()
{
    particleList.push_back(new Particle());
}

void Emitter::update()
{
    addParticle();
    if(!particleList.empty()){
        for(int i =0; i<particleList.size(); i++)
        {
            particleList.at(i)->update();
        }
    }
}

