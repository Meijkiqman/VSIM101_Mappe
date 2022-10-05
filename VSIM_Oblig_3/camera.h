#ifndef CAMERA_H
#define CAMERA_H
#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <QVector3D>
class Camera : public QOpenGLFunctions_4_1_Core
{
private:
    QVector3D mEye{0,0,0};
public:
    QMatrix4x4* mPmatrix{nullptr};         // denne,
    QMatrix4x4* mVmatrix{nullptr};         // og denne, skal legges inn i kameraklasse
public:
    Camera();
    ~Camera() { }
    void init();
    void perspective(int degrees, double aspect, double nearplane, double farplane);
    void lookAt(const QVector3D& eye, const QVector3D& at, const QVector3D& up);
    void translate(float dx, float dy, float dz);
    void rotate(float dx, float dy, float dz);
    QVector3D GetPosition();
};

#endif // CAMERA_H
