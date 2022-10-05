#include "vector3d.h"

Vector3D::Vector3D()
{}

Vector3D::Vector3D(const float &x, const float &y, const float &z)
    : mX{x}, mY{y}, mZ{z}
{}

float Vector3D::scalarProduct(Vector3D &vecA, Vector3D &vecB)
{
    float tempVal = (vecA.mX * vecB.mX) + (vecA.mY * vecB.mY) + (vecA.mZ * vecB.mZ);
    return tempVal;
}

Vector3D Vector3D::vectorProduct(Vector3D &vecA, Vector3D &vecB)
{
    float i, j, k;

    i = ((vecA.mY * vecB.mZ) - (vecA.mZ * vecB.mY));
    j = -1 * ((vecA.mX * vecB.mZ) - (vecA.mZ * vecB.mX));
    k = ((vecA.mX * vecB.mY) - (vecA.mY * vecB.mX));

    Vector3D tempVector{i, j, k};

    return tempVector;
}

float Vector3D::vectorMagnitude(Vector3D &vecA)
{
    float tempVal;

    tempVal = sqrt((pow(vecA.mX, 2) + (pow(vecA.mY, 2)) + (pow(vecA.mZ, 2))));
    return tempVal;
}

Vector3D Vector3D::normalize(Vector3D &vecA)
{
    float tempMagnitude;
    float i, j, k;
    tempMagnitude = vectorMagnitude(vecA);

    i = ((vecA.mX) / tempMagnitude);
    j = ((vecA.mY) / tempMagnitude);
    k = ((vecA.mZ) / tempMagnitude);

    Vector3D tempVector{i, j, k};
    return tempVector;
}
