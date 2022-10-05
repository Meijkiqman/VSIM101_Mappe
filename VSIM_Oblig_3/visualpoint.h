#ifndef VISUALPOINT_H
#define VISUALPOINT_H
#include "visualobject.h"

class visualPoint : public VisualObject
{
public:
    visualPoint(const std::vector<Vertex>& v);
    ~visualPoint();
    void init() override;
    void draw() override;
};

#endif // VISUALPOINT_H
