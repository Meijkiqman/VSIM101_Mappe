#include "camera.h"

Camera::Camera() : mEye{0,0,0}
{
    mPmatrix = new QMatrix4x4{};
    mPmatrix->setToIdentity();
    mVmatrix = new QMatrix4x4{};
    mVmatrix->setToIdentity();
}

void Camera::init()
{
    mPmatrix->setToIdentity();
    mVmatrix->setToIdentity();
}

void Camera::perspective(int degrees, double aspect, double nearplane, double farplane)
{
    mPmatrix->perspective(degrees, aspect, nearplane, farplane);
}

void Camera::lookAt(const QVector3D& eye, const QVector3D& at, const QVector3D& up)
{
    mEye = eye;
    mVmatrix->lookAt(eye, at, up);
}

void Camera::translate(float dx, float dy, float dz)
{
    mVmatrix->translate(dx, dy, dz);

    //mVmatrix->translate(0, 0, -9);
    // Rotates the camera
    mVmatrix->rotate(-20.f, 0.1f, 0.0f);
}

void Camera::rotate(float dx, float dy, float dz) {
    mVmatrix->rotate(dx, dy, dz);
}

QVector3D Camera::GetPosition(){
    return mEye;
}
