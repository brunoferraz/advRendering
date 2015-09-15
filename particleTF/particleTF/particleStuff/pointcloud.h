#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include <mesh.hpp>
#include "vector"
#include <particle.h>
#include <emitter.h>

class PointCloud : public Tucano::Mesh
{
public:
    PointCloud();

    vector<Eigen::Vector4f> v;
    vector<Eigen::Vector4f> velocity;


    void loadParticles(vector<Particle *> &particlelist);
    void loadParticles(Emitter &e);
    void update();
};

#endif // POINTCLOUD_H
