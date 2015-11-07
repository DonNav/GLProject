#include "RootObject.h"

Root_Object::Root_Object(QObject *parent) :
    QObject(parent)
{
    this->position = new QVector3D(0,0,0);
    this->scale = new QVector3D(1,1,1);
}

int Root_Object::draw(CameraGL *camera, LightGL *lightList, QMatrix4x4 projection, QMatrix4x4 view, QMatrix4x4 model){
    int s = 0;
    foreach(myMesh* m, meshList){
        s += m->drawObject(camera, lightList, projection   , view  , model, this->getQtPosition());
    }
    return s;
}




 void Root_Object::setPosition(double x, double y, double z){
     this->position->setX(x);
     this->position->setY(y);
     this->position->setZ(z);
 }

 QVector3D* Root_Object::getPosition(){
     return this->position;

 }

 QVector3D Root_Object::getQtPosition(){
     return QVector3D(this->position->x(), this->position->y(), this->position->z());

 }

 void Root_Object::setScale(double x, double y, double z){
     this->scale->setX(x);
     this->scale->setY(y);
     this->scale->setZ(z);
     foreach(myMesh* m, meshList){
         m->setScale(x,y,z,1);
     }
 }

 QVector3D *Root_Object::getScale(){
    return this->scale;
 }

 QVector3D Root_Object::getQtScale(){
     return QVector3D(this->scale->x(), this->scale->y(), this->scale->z());
 }

 void Root_Object::computeRotation(double angleX, double angleY, double angleZ){
     foreach(myMesh* m, meshList){
         m->computeRotation(angleX, angleY, angleZ);
     }
 }
