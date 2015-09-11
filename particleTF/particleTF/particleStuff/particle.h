#ifndef PARTICLE_H
#define PARTICLE_H

#include <Eigen/Eigen>

class Particle
{
public:
    Particle();

    Eigen::Matrix4f model;
    Eigen::Vector4f velocity;

    void setPosition(float x, float y, float z);
    void setPosition(Eigen::Vector4f v);
    void translate(Eigen::Vector4f v);
    Eigen::Vector4f getPosition();

    void update();
};

#endif // PARTICLE_H
