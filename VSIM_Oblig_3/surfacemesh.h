#ifndef SURFACEMESH_H
#define SURFACEMESH_H

#include "vertex.h"
#include "visualobject.h"
#include <iostream>
#include <string>

class Vertex;
struct Result{
    float height;
    Vertex v1;
    Vertex v2;
    Vertex v3;
    float friction = 0;

public:
    void setV1(const Vertex &newV1);
};

class SurfaceMesh : public VisualObject
{
public:
    SurfaceMesh(Shader* s);
    void draw() override;
    void init() override;
    //
    QVector3D GetBarycentric(QVector3D point, Vertex v1,  Vertex v2, Vertex v3);
    //
    Result GetHeight(QVector3D pos);


};

#endif // SURFACEMESH_H
