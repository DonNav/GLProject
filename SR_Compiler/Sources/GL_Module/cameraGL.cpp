#include "cameraGL.h"


CameraGL::CameraGL(QObject *parent) :
    QObject(parent)
{
    this->distance = 0.0;
    this->xRot = 0;
    this->yRot = 0;
    this->zRot = 0;

    this->nearPlane = 1.0;
    this->farPlane = 1000.0;
    this->fov = 32.0;
}

static void qNormalizeAngle(double &angle)
{
    while (angle < -180)
        angle += 360;
    while (angle > 180)
        angle -= 360;
}


void CameraGL::setXRotation(double angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
    }

}

void CameraGL::setYRotation(double angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;

    }

}

void CameraGL::setZRotation(double angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
    }

}

void CameraGL::setDistance(double distance){
    this->distance = distance;
}

QVector3D CameraGL::getQtPositionEye(){

    QVector3D result;
    result.setX(this->distance * qSin(yRot * M_PI / 180.0));
    result.setY(this->distance * qSin( xRot * M_PI / 180.0 ));
    result.setZ(this->distance * qCos(yRot * M_PI / 180.0) * qCos(xRot * M_PI / 180) ) ;


    return result;
 }


QMatrix4x4 CameraGL::lookAt(){
    QMatrix4x4 mat;
    mat.lookAt( getQtPositionEye(), QVector3D(0,0,0), QVector3D(0,1,0));
    return mat;
}


