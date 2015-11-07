#ifndef MYMATERIAL_H
#define MYMATERIAL_H

#include <QObject>
#include <QVector4D>
#include "myTexture.h"
#include "myCubeTexture.h"

class myMaterial : public QObject
{
    Q_OBJECT
public:
    explicit myMaterial(QObject *parent = 0);

    void readMlt(QString filename);

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

    void setDiffuseSecond(QVector4D* pos){diffuseSecond = pos;}
    void setDiffuseSecond(double x, double y, double z, double w){diffuseSecond->setX(x); diffuseSecond->setY(y); diffuseSecond->setZ(z); diffuseSecond->setW(w);}
    QVector4D* getDiffuseSecond(){return diffuseSecond;}
    QVector4D getQtDiffuseSecond(){QVector4D result; result.setX( diffuseSecond->x()); result.setY(diffuseSecond->y()); result.setZ(diffuseSecond->z()); result.setW(diffuseSecond->w()); return result;}

    void setEmission(QVector4D* a){this->emission = a;}
    void setEmission(double r, double g, double b, double a){this->emission->setX(r); this->emission->setY(g); this->emission->setZ(b); this->emission->setW(a);}
    QVector4D* getEmission(){return emission;}
    QVector4D getQtEmission(){ QVector4D a; a.setX(emission->x()); a.setY(emission->y()); a.setZ(emission->z()); a.setW(emission->w()); return a; }

    void setGloss(float g){this->gloss = g;}
    float getGloss(){return gloss;}

    void setReflectivity(float r){this->reflectivity = r;}
    float getReflectivity(){return reflectivity;}

    void setTextureScaling(QVector2D* v){ this->textureScaling = v;}
    void setTextureScaling(double x, double y){ this->textureScaling->setX(x); this->textureScaling->setY(y);}
    QVector2D getTextureScaling(){ return QVector2D(textureScaling->x(), textureScaling->y());}

    void setRefraction(float r){this->refraction = r;}
    float getRefraction(){return this->refraction;}

    MyTexture* texture;
    MyTexture* bumpMap;
    MyCubeTexture* cubeTexture;
    MyCubeTexture* reflexionTexture;


signals:

public slots:

private:
    QVector4D* ambient;
    QVector4D* diffuse;
    QVector4D* diffuseSecond;
    QVector4D* specular;
    QVector4D* emission;

    float reflectivity;
    float gloss;
    float refraction;
    QVector2D* textureScaling;

};

#endif // MYMATERIAL_H
