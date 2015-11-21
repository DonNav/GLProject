#ifndef CAMERAGL_H
#define CAMERAGL_H

#include <QObject>
#include <QVector3D>
#include <QDebug>
#include <QMatrix4x4>
#include "qmath.h"
#include "utilMoveObjectClass.h"

class CameraGL : public QObject
{
    Q_OBJECT
    public:
        explicit CameraGL(QObject *parent = 0);

    signals:

    public slots:
        void setXRotation(double angle);
        void setYRotation(double angle);
        void setZRotation(double angle);
        double getXRot(){return xRot;}
        double getYRot(){return yRot;}
        double getZRot(){return zRot;}

        void setDistance(double distance);
        double getDistance(){return this->distance;}
        void zooming(double d){ this->distance -= d;}
        QVector3D getQtPositionEye();

        void setFarPlane(double fp){ this->farPlane = fp;}
        double getFarPlane(){ return this->farPlane;}

        void setNearPlane(double np){this->nearPlane = np;}
        double getNearPlane(){return this->nearPlane;}

        void setFOV(double f){this->fov = f;}
        double getFOV(){return this->fov;}

        QMatrix4x4 lookAt();

    private:
        double distance;
        double xRot;
        double yRot;
        double zRot;

        double farPlane;
        double nearPlane;
        double fov;

        Util_Move_Object_Class moveCamera;


};

#endif // CAMERAGL_H
