#include "vertex.h"
#include "vector3d.h"
Vertex::Vertex()
{
}

Vertex::Vertex(float x, float y, float z)
    :x(x), y(y), z(z)
{

}

Vertex::Vertex(Vector3D verts, Vector3D norms, std::pair<float, float> uvs)
{
    x = verts.mX;
    y = verts.mY;
    z = verts.mZ;

    r = norms.mX;
    g = norms.mY;
    b = norms.mZ;

    t1 = uvs.first;
    t2 = uvs.second;
}
Vertex::Vertex(float x, float y, float z, float t1, float t2)
    : x(x), y(y), z(z), t1(t1), t2(t2)
{
}

Vertex::Vertex(float x, float y, float z, float r, float g, float b)
    :x(x),y(y),z(z),r(r),g(g),b(b)
{
}

Vertex::Vertex(float x, float y, float z, float r, float g, float b, float t1, float t2)
    : x(x), y(y), z(z), r(r), g(g), b(b), t1(t1), t2(t2)
{
}

Vertex::~Vertex()
{
}

std::ostream& operator<< (std::ostream& os, const Vertex& v) {
  os << std::fixed;
  os << "(" << v.x << ", " << v.y << ", " << v.z << ") ";
  os << "(" << v.r << ", " << v.g << ", " << v.b << ") ";
  os << "(" << v.t1 << ", " << v.t2 << ") ";
  return os;
}
std::istream& operator>> (std::istream& is, Vertex& v) {
// Trenger fire temporære variabler som kun skal lese inn parenteser og komma
  char dum, dum2, dum3, dum4;
  is >> dum >> v.x >> dum2 >> v.y >> dum3 >> v.z >> dum4;
  is >> dum >> v.r >> dum2 >> v.r >> dum3 >> v.g >> dum4;
  is >> dum >> v.t1 >> dum2 >> v.t2 >> dum3;
  return is;
}
