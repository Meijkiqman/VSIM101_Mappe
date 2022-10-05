#ifndef VERTEX_H
#define VERTEX_H

#include<iostream>
#include <fstream>
#include <istream>
class Vector3D;
class Vertex {
   //! Overloaded ostream operator which writes all vertex data on an open textfile stream
   friend std::ostream& operator<< (std::ostream&, const Vertex&);

   //! Overloaded ostream operator which reads all vertex data from an open textfile stream
   friend std::istream& operator>> (std::istream&, Vertex&);

public:
   float x{0.f}, y{ 0.f }, z{ 0.f };
   float r{ 1.f }, g{ 1.f }, b{ 1.f };
   float t1{ 0.f }, t2{ 0.f };
public:
   Vertex();
   Vertex(float x, float y, float z);
   Vertex(Vector3D verts, Vector3D norms, std::pair<float, float> uvs);
   Vertex(float x, float y, float z, float t1, float t2);
   Vertex(float x, float y, float z, float r, float g, float b);
   Vertex(float x, float y, float z, float r, float g, float b, float t1, float t2);
   ~Vertex();
};

#endif // VERTEX_H
