#include "particle.h"
#include <iostream>

Particle::Particle()
{
    model <<    1,  0,  0,  0,
                0,  1,  0,  0,
                0,  0,  1,  0,
                0,  0,  0,  1;
    velocity << (rand()%100)/10000.0, (rand()%100)/10000.0, (rand()%100)/10000.0, 0;
}

void Particle::setPosition(float x, float y, float z)
{
    Eigen::Vector4f v;
    v << x, y, z, model(3, 3);
    model.col(3) = v.transpose();
}

void Particle::setPosition(Eigen::Vector4f v)
{
    model.col(3) = v.transpose();
}

void Particle::translate(Eigen::Vector4f v)
{
    setPosition((getPosition()+v));
}

Eigen::Vector4f Particle::getPosition()
{
    return model.col(3).transpose();
}

void Particle::update()
{
    //translate(velocity);
}

