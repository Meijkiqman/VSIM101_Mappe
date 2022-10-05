#include "rollingball.h"
#include "surfacemesh.h"
#include "visualpoint.h"
RollingBall::RollingBall(std::string fileName, Shader* shader) : ObjMesh(fileName, shader)
{
//SetScale(QVector3D(5,5,5));
    oldPos = GetPosition();

}

void RollingBall::SetSurface(VisualObject* surface)
{
    m_Surface = surface;

    m_SurfaceMesh = dynamic_cast<SurfaceMesh*>(m_Surface);
}

void RollingBall::DoPhysics()
{
    QVector3D gravity(0, -9.81f, 0);

    //radius av ballen er størrelsen / 2
    float radius = GetScale().x()/2;
    if(true)
    {
        QVector3D nyPos = GetPosition() + oldVel/60 + 1/2*gravity/60;
        oldPos = GetPosition();
        oldVel = oldVel + gravity /60;
        SetPosition(nyPos);
        return;
    }

    if(m_SurfaceMesh)
    {

        //Får resultatet fra surfacemesh
        Result r = m_SurfaceMesh->GetHeight(GetPosition());



        //Lagerer vertexene på triangelt
        Vertex* v1 = &r.v1;
        Vertex* v2 = &r.v2;
        Vertex* v3 = &r.v3;
        //Nåværende posistjon
        QVector3D currPos = GetPosition();
        //Finner friksjonen på denne trekanten
        float friction = r.friction;

        //Sjekk at vertex finnes
        if(v1 && v2 && v3){
            //Lager punkter fra vertexene
            QVector3D p1(v1->x, v1->y, v1->z);
            QVector3D p2(v2->x, v2->y, v2->z);
            QVector3D p3(v3->x, v3->y, v3->z);
            //Finner normalen
            QVector3D a = p2 - p1;
            QVector3D b = p3 - p1;
            QVector3D normal = QVector3D::crossProduct(a, b).normalized();

            long double t = 1/60;
            //Akselerasjon, Lignign 7
            QVector3D acc = gravity.y() * QVector3D(normal.x() * normal.y(), normal.y() * normal.z(), pow(normal.y(), 2)-1);
            //R = r0 + v0t + 1/2at^2
            QVector3D nyPos = currPos + oldVel/60 + 1/2*acc/60;
            //Setter høyde + radius så den sitter på flaten
            nyPos.setY(r.height + radius);
            //Setter nye posisjonen
            SetPosition(nyPos);
            //Oppdater hastigheten
            oldVel = oldVel + acc /60;

            //SJekk om ballen er på ny trekant
            if(oldv1 && oldv2 && oldv3){
                if(normal != oldNormal){
                     //Ballen har rullet over på nytt triangel
                     //Beregner normalen til kolisjonsplanet, ligning 9
                     //Lage punkter fra de gamle vertexene
                     //Regne normalen mellom planene
                     float alpha = QVector3D::crossProduct(normal, oldNormal).length();
                     qDebug() << "alpha: " << alpha;
                     if(alpha <= 3.14f){
                         //Oppover møte
                     }else{
                         //Nedover møte
                     }
                     //Finner en vector mellom de to veggene
                     QVector3D x = (normal + oldNormal)/(normal+oldNormal).lengthSquared();
                     qDebug() << "x: " << x;
                     //Formel 8.8 skal finne den nye hastighet vektoren
                     QVector3D nyHastighet = oldVel - 2*(oldVel*x)*x;

                     qDebug() << "Ny hast:" << nyHastighet;
                     qDebug() << "Gammel hast: " << oldVel;
                     oldVel = nyHastighet;
                    //Finne om det er kollisjon
                     QVector3D r = GetPosition() - oldPos;
                     if(r.lengthSquared() <= radius){
                        //Har kollisjon
                        qDebug() << "kollisjojn";
                        //Sett ny posisjon over punktet

                     }else{
                        //Har ikke kollisjon
                        qDebug() << "ikke kollisjon";
                     }
                }
            }

            oldv1 = &r.v1;
            oldv2 = &r.v2;
            oldv3 = &r.v3;
            oldNormal = normal;
            oldPos = GetPosition();
        }

    }
}

void RollingBall::ResetPhysics()
{
    oldVel = QVector3D(0,0,0);
}

void RollingBall::AddLife()
{
    //adds lifetime for creating points
    timeLived += 1;
    if(timeLived % BsplinePointCounter)
    {
        CreateBsplineP();
    }
}

void RollingBall::EnableSpline()
{
    if(!drawSpline)
    {
        CreateBspline();
        drawSpline = true;
    }
}

void RollingBall::DisableSpline()
{
     drawSpline = false;
}

void RollingBall::CreateBsplineP()
{
    QVector3D ballPos = GetPosition();
    Vertex* v = new Vertex(ballPos.x(), ballPos.y(), ballPos.z());
    //qDebug() << "Creating control point at " << ballPos;
    //qDebug() << "Vertexen er  på : " <<  QVector3D(v->x, v->y, v->z);
    ControlPs.push_back(v);
}

void RollingBall::CreateBspline()
{
    //clears controlspoints
    t.clear();
    float step = 0.01f;
    //-1 pga 0 indeksering
    n = ControlPs.size();
    //d=2, for kvadratisk spline
    d = 2;
    //Skjøter i hver ende
       float s = d + 1; //d + 1 like skjøter i hver ende
       float total = n + d + 1;
       //Lager skjøtevektoren
       for(int i = 0; i < total-s; i++)
       {
           if(i == 0)
           {
               for(int k = 0 ; k < s ; k++)
               {
                   t.push_back(i);
               }
           }
           else if(i == total-s-1){
               for(int k = 0; k < s; k++)
               {
                   t.push_back(i);
               }
           }
           else
           {
               t.push_back(i);
           }
       }
    for(int i = 0; i < ControlPs.size(); i++)
    {
           c.push_back(QVector3D(ControlPs[i]->x, ControlPs[i]->y,ControlPs[i]->z));
    }

    std::vector<Vertex> mVisualPoints;
    for(float time = 0; time < 1; time += step)
    {
        QVector3D point = EvaluateBezier(time);
        qDebug() << "Bezier function returned : " << point << " for time " << time;

        mVisualPoints.push_back(Vertex(point.x(), point.y(), point.z(), 1, 1,1));
    }
    mBspline = new visualPoint(mVisualPoints);
    mBspline->init();
    drawSpline = true;



}
//deBoors fra compendium
QVector3D  RollingBall::EvaluateBezier(float x)
{
    int my = findKnotInterval(x);

    std::vector<QVector3D> a;

    a.reserve(d+1);

    for( int j =0; j<=d ; j++)
    {
        a[d-j]= c[my-j];
    }
    for(int k=d ; k>0; k--)
    {
        int j = my-k;
        for ( int i =0; i<k ; i++)
        {
            j ++;
            float w = (x-t[j] ) / ( t[j+k]-t[j] ) ;
            a[i] = a[i] * (1-w) + a [i +1] * w;
        }
    }
    return a[0] ;
}
//fra compendium
int RollingBall::findKnotInterval(float x)
{
    int my = n;
    while(x < t[my])
    {
        my--;
    }
    return my;
}
