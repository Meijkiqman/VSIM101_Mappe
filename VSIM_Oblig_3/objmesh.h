#ifndef OBJMESH_H
#define OBJMESH_H

#include "visualobject.h"
class ObjMesh : public VisualObject
{
public:
    ObjMesh(std::string filename);
    ObjMesh(std::string fileName, Shader* shader);
    ObjMesh(std::string fileName, Shader* shader, Texture* texture);
    virtual void draw() override;
    virtual void init() override;
    virtual void DoPhysics() override;

protected:
    void readFile(std::string filePath);
    void writeFile(std::string filePath);
    GLuint mIBO{0};
};

#endif // OBJMESH_H
