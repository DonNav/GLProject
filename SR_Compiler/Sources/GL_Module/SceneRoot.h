#ifndef SCENEROOT_H
#define SCENEROOT_H

#include <QObject>
#include <QXmlStreamReader>
#include <QRgb>
#include "cameraGL.h"
#include "lightGL.h"
#include "mymesh.h"
#include "RootObject.h"
#include "myfog.h"
#include "myTexture.h"
#include "utilMoveObjectClass.h"

class Scene_Root_Class : public QObject
{
    Q_OBJECT
public:
    explicit Scene_Root_Class(QObject *parent = 0);
    LightGL* light;
    void is_Loaded_Layout(QString Requested_File);

    // mandatory !!!
    CameraGL* camera;
    myMesh* mSkyBox;


signals:
    void sceneChanged();
    
public slots:
        int draw(CameraGL* camera, QMatrix4x4 projection, QMatrix4x4 view, QMatrix4x4 model);

        QVector4D* getBacgroundColor(){return this->backgroundColor;}
        void setBackgroundColor(QVector4D* Color){ this->backgroundColor = Color; emit sceneChanged();}
        void setBackgroundColor(double r, double g, double b, double a){ if(NULL == this->backgroundColor) backgroundColor= new QVector4D(r,g,b,a); else {backgroundColor->setW(a);backgroundColor->setX(r);backgroundColor->setY(g);backgroundColor->setZ(b);}emit sceneChanged();}
        void setBackgroundColor(QColor Color){ if(NULL == this->backgroundColor) backgroundColor= new QVector4D(Color.red(),Color.green(),Color.blue(),Color.alpha()); else {backgroundColor->setW(Color.alpha()/255.0);backgroundColor->setX(Color.red()/255.0);backgroundColor->setY(Color.green()/255.0);backgroundColor->setZ(Color.blue()/255.0);}emit sceneChanged();}


        void reset();
        void addObject(QString path);
        void export3d(QString path);

private:
    myFog* fog;
    QList<myMesh*> objectList;
    QList<Root_Object*> rootList;
    QVector4D* backgroundColor;

    QVector4D main_car_color;

    QImage imgPicker;

    myMaterial* mMaterial;


};

#endif // SCENEROOT_H
