#ifndef LIGHTGL_H
#define LIGHTGL_H

#include <QObject>
#include <QVector4D>
#include <QVector3D>
#include <QtOpenGL>
#include <QDebug>
class LightGL : public QObject
{
    Q_OBJECT
public:
    explicit LightGL(QObject *parent = 0);
    
signals:
    
public slots:
    void setPosition(QVector4D* pos){position = pos;}
    void setPosition(double x, double y, double z, double w){position->setX(x); position->setY(y); position->setZ(z); position->setW(w);}
    QVector4D* getPosition(){return position;}
    QVector4D getQtPosition(){QVector4D result; result.setX( position->x()); result.setY(position->y()); result.setZ(position->z()); result.setW(position->w()); return result;}

    void setDirection(QVector4D* dir){direction = dir;}
    void setDirection(double x, double y, double z, double w){direction->setX(x); direction->setY(y); direction->setZ(z); direction->setW(w);}
    QVector4D* getDirection(){return direction;}
    QVector4D getQtDirection(){QVector4D result; result.setX( direction->x()); result.setY(direction->y()); result.setZ(direction->z()); result.setW(direction->w()); return result;}

    void setSpecular(QVector4D* pos){specular = pos;}
    void setSpecular(double x, double y, double z, double w){specular->setX(x); specular->setY(y); specular->setZ(z); specular->setW(w);}
    QVector4D* getSpecular(){return specular;}
    QVector4D getQtSpecular(){QVector4D result; result.setX( specular->x()); result.setY(specular->y()); result.setZ(specular->z()); result.setW(specular->w()); return result;}

    void setAmbient(QVector4D* pos){ambient = pos;}
    void setAmbient(double x, double y, double z, double w){ambient->setX(x); ambient->setY(y); ambient->setZ(z); ambient->setW(w);}
    QVector4D* getAmbient(){return ambient;}
    QVector4D getQtAmbient(){QVector4D result; result.setX( ambient->x()); result.setY(ambient->y()); result.setZ(ambient->z()); result.setW(ambient->w()); return result;}

    void setDiffuse(QVector4D* pos){diffuse = pos;}
    void setDiffuse(double x, double y, double z, double w){diffuse->setX(x); diffuse->setY(y); diffuse->setZ(z); diffuse->setW(w);}
    QVector4D* getDiffuse(){return diffuse;}
    QVector4D getQtDiffuse(){QVector4D result; result.setX( diffuse->x()); result.setY(diffuse->y()); result.setZ(diffuse->z()); result.setW(diffuse->w()); return result;}

    void setEnable(bool b){ this->isEnable = b;}
    bool getEnable(){return isEnable;}

    void setPointLight(bool b){ this->isPointLight = b;}
    bool getPointLight(){return isPointLight;}

    void setCosCutIn(float f){this->cosCutIn = f;}
    float getCosCutIn(){return cosCutIn;}

    void setCosCutoff(float f){this->cosCutoff = f;}
    float getCosCutoff(){return cosCutoff;}

    void setConstantAttenuation(float f){this->constantAttenuation = f;}
    float getConstantAttenuation(){return constantAttenuation;}

    void setLinearAttenuation(float f){this->linearAttenuation = f;}
    float getLinearAttenuation(){return linearAttenuation;}

    void setQuadraticAttenuation(float f){this->quadraticAttenuation = f;}
    float getQuadraticAttenuation(){return quadraticAttenuation;}



private:
    QVector4D* position;

    QVector4D* direction;
    float cosCutIn;
    float cosCutoff;

    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;

    QVector4D* specular;
    QVector4D* ambient;
    QVector4D* diffuse;

    bool isEnable;
    bool isPointLight;


};

#endif // LIGHTGL_H
