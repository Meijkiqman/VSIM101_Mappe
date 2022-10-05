#ifndef Vector3D_H
#define Vector3D_H

#include <iostream>
#include <cmath>
class Vector3D
{
private:


public:
    float mX;
    float mY;
    float mZ;

    Vector3D operator+(const Vector3D& v3d) const
    {
        Vector3D v3d1;
        v3d1.mX = mX + v3d.mX;
        v3d1.mY = mY + v3d.mY;
        v3d1.mZ = mZ + v3d.mZ;
        return v3d1;
    }

    Vector3D operator-(const Vector3D& v3d) const
    {
        Vector3D v3d1;
        v3d1.mX = mX - v3d.mX;
        v3d1.mY = mY - v3d.mY;
        v3d1.mZ = mZ - v3d.mZ;
        return v3d1;
    }

    Vector3D operator*(const Vector3D& v3d) const
    {
        Vector3D v3d1;
        v3d1.mX = mX * v3d.mX;
        v3d1.mY = mY * v3d.mY;
        v3d1.mZ = mZ * v3d.mZ;
        return v3d1;
    }

    Vector3D operator/(const Vector3D& v3d) const
    {
        Vector3D v3d1;
        v3d1.mX = mX / v3d.mX;
        v3d1.mY = mY / v3d.mY;
        v3d1.mZ = mZ / v3d.mZ;
        return v3d1;
    }


    Vector3D();
    Vector3D(const float &x, const float &y, const float &z);
    // Dot product
    float scalarProduct(Vector3D& vecA, Vector3D& vecB);
    // Cross product
    Vector3D vectorProduct(Vector3D& vecA, Vector3D& VecB);
    float vectorMagnitude(Vector3D& vecA);
    Vector3D normalize(Vector3D& vecA);
};

#endif // Vector3D_H
