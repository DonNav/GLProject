#include "lightGL.h"

LightGL::LightGL(QObject *parent) :
    QObject(parent)
{
    position = new QVector4D();
    specular= new QVector4D();
    diffuse= new QVector4D();
    ambient= new QVector4D();
    direction = new QVector4D();
    this->isPointLight = true;
    this->isEnable = true;
}



