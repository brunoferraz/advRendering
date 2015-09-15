#include "pointcloud.h"
PointCloud::PointCloud()
{
    int size = 200;
    for(int i =0; i < 1000; i++){
        Eigen::Vector4f p;
        p <<rand()%size, rand()%size, rand()%size, size/2;
        p/=size/2;
        p(0)-=1;
        p(1)-=1;
        p(2)-=1;
        v.push_back(p);
    }
    loadVertices(v);
}

void PointCloud::loadParticles(Emitter &e)
{
    //reset();
    vector<Eigen::Vector4f> vl;
    velocity.clear();
    if(!e.particleList.empty()){
        for(int i = 0; i < e.particleList.size(); i++)
        {
            Eigen::Vector4f v = e.particleList.at(i)->getPosition();
            vl.push_back(v);
            Eigen::Vector4f vel =  e.particleList.at(i)->velocity;
            velocity.push_back(vel);
        }
    }
    loadVertices(vl);
    createAttribute("in_Velocity", velocity);
}

void PointCloud::update()
{

}

