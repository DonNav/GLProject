#include "utilMoveObjectClass.h"

Util_Move_Object_Class::Util_Move_Object_Class(QObject *parent) :
    QObject(parent)
{
    moveTimer = new QTimer();
    QObject::connect(this->moveTimer, SIGNAL(timeout()), this, SLOT(changedPosition()));

    rotateTimer = new QTimer();
    QObject::connect(this->rotateTimer, SIGNAL(timeout()), this, SLOT(changedRotation()));

    rotateCameraTimer= new QTimer();
         QObject::connect(this->rotateCameraTimer, SIGNAL(timeout()), this, SLOT(changedCameraRotation()));
}

void Util_Move_Object_Class::MoveObjectTo(QVector3D positionSource, QVector3D positionFinale, int time, Function::Type easingType){
   // intervalleTranslate = QVector3D( positionSource.x()/time*16, positionSource.y()/time*16, positionSource.z()/time*16);
    calculIntervalle(positionSource, positionFinale, time, easingType);
    moveFrom = positionSource;
    translateTo = positionFinale;
    moveTimer->stop();
    moveTimer->start(16);

}

void Util_Move_Object_Class::RotateObjectTo(double angleX, double angleY, double angleZ, int time, Function::Type easingType){
    rotateTimer->stop();
    intervalleRotate.clear();
    emit newRotation(rotateTo.x(), rotateTo.y(),  rotateTo.z());
    calculIntervalle(angleX, angleY, angleZ, time, easingType);
    rotateTo = QVector3D(angleX, angleY, angleZ);
    rotateTimer->start(16);
}

void Util_Move_Object_Class::RotateCameraTo(double angleX, double toAngleX, double angleY, double toAngleY, double angleZ, double toAngleZ, int time, Function::Type easingType){
    rotateTimer->stop();
    intervalleRotate.clear();
 //   emit newRotation(rotateTo.x(), rotateTo.y(),  rotateTo.z());
    calculIntervalleCamera(angleX,toAngleX,angleY,toAngleY ,angleZ,toAngleZ , time, easingType);
    rotateCameraTimer->start(16);
}

void Util_Move_Object_Class::changedPosition(){
    if (qAbs(moveFrom.x() - translateTo.x()) < 1 && qAbs(moveFrom.y() - translateTo.y()) < 1 &&  qAbs(moveFrom.z() - translateTo.z()) < 1 ){
        moveTimer->stop();
        moveFrom = translateTo;
        intervalleTranslate.clear();
        emit translationOver();
    }
    else {
        moveFrom += intervalleTranslate.first();
        intervalleTranslate.removeFirst();
    }
    emit this->newPosition(moveFrom);
}

void Util_Move_Object_Class::changedRotation(){
    if (qAbs(rotateTo.x()) < 5 && qAbs(rotateTo.z()) < 5 && qAbs(rotateTo.y()) < 5){
        emit newRotation(rotateTo.x(), rotateTo.y(),  rotateTo.z());
        rotateTo = QVector3D(0, 0, 0);
        rotateTimer->stop();
        emit rotationOver();
    }
    else{
        emit newRotation(intervalleRotate.first().x(), intervalleRotate.first().y(),  intervalleRotate.first().z());
        rotateTo -= intervalleRotate.first();
        intervalleRotate.removeFirst();

    }

}

void Util_Move_Object_Class::changedCameraRotation(){
    if (!intervalleRotate.isEmpty()){
        emit newRotation(intervalleRotate.first().x(), intervalleRotate.first().y(),  intervalleRotate.first().z());
        rotateTo -= intervalleRotate.first();
        intervalleRotate.removeFirst();
        emit rotationCameraOver();
    }
    else {
        rotateCameraTimer->stop();
    }

}

void Util_Move_Object_Class::calculIntervalle(QVector3D positionSource, QVector3D positionFinale, int time, Function::Type easingType){
    if (easingType == 0){
        for (int i = 0; i < time/16; i++){ // number of position to calcul
            intervalleTranslate.append(QVector3D((positionFinale.x() - positionSource.x())/time*16, (positionFinale.y()-positionSource.y())/time*16, (positionFinale.z()- positionSource.z())/time*16));
        }
    }
    else if(easingType == 1){

    }
    else if(easingType == 2){

    }
    else if(easingType == 3){

    }
}

void Util_Move_Object_Class::calculIntervalle(double angleX, double angleY, double angleZ, int time, Function::Type easingType){
    if (easingType == 0){
        for (int i = 0; i < time/16; i++){ // number of position to calcul
            intervalleRotate.append(QVector3D(angleX/time*16, angleY/time*16,angleZ/time*16));
        }
    }
    else if(easingType == 1){

    }
    else if(easingType == 2){

    }
    else if(easingType == 3){

    }

}

void Util_Move_Object_Class::calculIntervalleCamera(double angleX, double toAngleX, double angleY, double toAngleY, double angleZ, double toAngleZ, int time, Function::Type easingType){
    if (easingType == 0){
        if (angleX - toAngleX > 180) angleX = angleX - 360;
        if (angleY - toAngleZ > 180) angleY = angleY - 360;
        if (angleZ - toAngleY > 180) angleZ = angleZ - 360;
        double IntervalleX = (angleX-toAngleX)/time*16;
        double IntervalleY = (angleY-toAngleY)/time*16;
        double IntervalleZ = (angleZ-toAngleZ)/time*16;
        for (int i = 0; i <= time/16; i++){ // number of position to calcul
            intervalleRotate.append(QVector3D(angleX- IntervalleX*i, angleY- IntervalleY*i,angleZ- IntervalleZ*i));
        }
        intervalleRotate.append(QVector3D(0,0,0));
    }
    else if(easingType == 1){

    }
    else if(easingType == 2){

    }
    else if(easingType == 3){

    }
}
