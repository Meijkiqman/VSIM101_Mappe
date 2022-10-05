#ifndef ROLLINGBALL_H
#define ROLLINGBALL_H

#include "objmesh.h"

class Vertex;
class RollingBall : public ObjMesh
{
public:
    RollingBall(std::string fileName, Shader* shader);

    void SetSurface(VisualObject* surface);
    VisualObject* GetSurface(){return m_Surface;};
    void DoPhysics() override;
    void ResetPhysics();
    void AddLife();
    bool Alive()
    {
        return timeLived <= totalLifeTime ? true : false;
    }

    //funksjoner for å aktivire/deaktivere splines
    void EnableSpline();
    void DisableSpline();

    int GettimeLived()
    {
        return timeLived;
    };

    int GetTotalLifeTime()
    {
        return totalLifeTime;
    };

    class visualPoint* GetSpline()
    {
        return mBspline;
    };

private:
    VisualObject* m_Surface;
    class SurfaceMesh* m_SurfaceMesh;
    float m_Weight = 0.2f;
    QVector3D m_Velocity;
    QVector3D mAcceleration;
    float m_GravityConstant = 9.81f;
    Vertex* oldv1;
    Vertex* oldv2;
    Vertex* oldv3;
    QVector3D oldNormal;
    QVector3D oldVel = QVector3D(0, -9.81f, 0)/60;
    QVector3D oldPos;


    //levetid for regn
    int timeLived = 0;
    int totalLifeTime = 600;

    //B-spline ting:
    int BsplinePointCounter = 60;
    void CreateBsplineP();
    std::vector<Vertex*> ControlPs;
    void CreateBspline();

    class visualPoint* mBspline;
    bool drawSpline = false;

    //skjøtepunkt
    std::vector<float> t;

    std::vector<QVector3D> c;


    int findKnotInterval(float x);


    int n;
    //grad
    int d;
    //deBoors
    QVector3D EvaluateBezier(float x);



};

#endif // ROLLINGBALL_H
