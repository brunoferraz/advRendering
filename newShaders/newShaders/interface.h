#ifndef INTERFACE_H
#define INTERFACE_H


class Interface
{
public:
    Interface();
    static bool showNormals;
    enum {PHONG=0, SHADOWMAP =1, GOOCH=2};

    static int renderType;
};

#endif // INTERFACE_H
