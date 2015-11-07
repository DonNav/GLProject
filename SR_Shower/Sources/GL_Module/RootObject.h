#ifndef ROOTOBJECT_H
#define ROOTOBJECT_H

#include <QObject>
#include "mymesh.h"

class Root_Object : public QObject
{
    Q_OBJECT
public:
    explicit Root_Object(QObject *parent = 0);
    QList<myMesh*> meshList;
    
signals:
    
public slots:
    int draw(CameraGL *camera, LightGL* lightList, QMatrix4x4 projection   , QMatrix4x4 view  , QMatrix4x4 model);


    void setPosition(double x, double y, double z);
    QVector3D* getPosition();
    QVector3D getQtPosition();
    void setScale(double x, double y, double z);
    QVector3D* getScale();
    QVector3D getQtScale();
    void computeRotation(double angleX, double angleY, double angleZ);
    void initShader(){ foreach(myMesh* m, meshList) m->initShader();}

private:
    QVector3D* position;
    QVector3D* scale;
    
};

#endif // ROOTOBJECT_H
