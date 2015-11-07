#ifndef UTILMOVEOBJECTCLASS_H
#define UTILMOVEOBJECTCLASS_H

#include <QObject>
#include <QVector>
#include <QVector3D>
#include <QTimer>
#include <QDebug>

namespace Function {
    typedef enum {
        Linear = 0,
        Quadratic = 1,
        Cubic = 2,
        Quart = 3
    } Type;
}

class Util_Move_Object_Class : public QObject
{
    Q_OBJECT
public:
    explicit Util_Move_Object_Class(QObject *parent = 0);

protected slots:
    void changedPosition();
    void changedRotation();
    void changedCameraRotation();
    void calculIntervalle(QVector3D positionSource, QVector3D positionFinale, int time, Function::Type easingType);
    void calculIntervalle(double angleX, double angleY, double angleZ, int time, Function::Type easingType);
    void calculIntervalleCamera(double angleX, double toAngleX, double angleY, double toAngleY, double angleZ, double toAngleZ, int time, Function::Type easingType);

signals:
    void newPosition(QVector3D);
    void newRotation(float angleX, float angleY, float angleZ);
    void rotationOver();
    void translationOver();
    void rotationCameraOver();
    
public slots:
    void MoveObjectTo(QVector3D positionSource, QVector3D positionFinale, int time, Function::Type easingType = Function::Linear);
    void RotateObjectTo(double angleX, double angleY, double angleZ, int time, Function::Type easingType = Function::Linear);
    void RotateCameraTo(double angleX, double toAngleX, double angleY, double toAngleY, double angleZ, double toAngleZ, int time, Function::Type easingType);


private:
    QTimer *moveTimer, *rotateTimer, *rotateCameraTimer;
    QVector3D moveFrom, rotateTo, translateTo;
    QList<QVector3D> intervalleRotate, intervalleTranslate;
    
};

#endif // UTILMOVEOBJECTCLASS_H
