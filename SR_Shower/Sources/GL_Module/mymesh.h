#ifndef MYMESH_H
#define MYMESH_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QStringList>
#include "qmath.h"
#include "myMaterial.h"
#include "shadergl.h"
#include "cameraGL.h"
#include "lightGL.h"
#include "utilMoveObjectClass.h"


struct Shadding {
    ShaderGL* shader;
    int quality;
};

class myMesh : public QObject
{
    Q_OBJECT
public:
    explicit myMesh(QObject *parent = 0);
    bool read(QString filename);
    bool readFar(QString filename);
    int getSimilarVertexIndex(QVector3D vertIn, QVector3D normalIn, QVector2D uvIn, QVector<QVector3D> vArray, QVector<QVector3D> nArray, QVector<QVector2D> uvArray);
    bool is_near(float v1, float v2);

    void addShader(QString vertfile, QString fragFile, int quality);
    void initShader();
    void setCurrShader(int quality);
    // Getter and Setter
    void setPosition(double x, double y, double z);
    void setCenter(double x, double y, double z) { if (NULL == this->center) this->center = new QVector3D(); center->setX(x); center->setY(y); center->setZ(z);}

    void setVisible(bool v){ this->visible = v;}
    bool isVisible(){return this->visible;}

    QVector3D* getPosition();
    QVector3D* getCenter(){ return this->center;}
    void setScale(double x, double y, double z, double w);
    QVector4D* getScale();
    QVector4D getQtScale();

    int drawObject(CameraGL *camera, LightGL *lightList, QMatrix4x4 projection   , QMatrix4x4 view  , QMatrix4x4 model, QVector3D position = QVector3D(0,0,0));



    void lightShader(LightGL* light);

    myMaterial* mat;

    Util_Move_Object_Class* getUtilObject() { return &moveObject;}

    QString exportFar();
signals:

public slots:
    void moveObjectTo(QVector3D position, int time);

    void rotateObjectTo(double angleX, double angleY, double angleZ, int time);

    void setPosition(QVector3D position);
    void computeRotation(float angleX, float angleY, float angleZ);
    void setDoubleFaced(bool b){this->isDoubleFace = b;}


private:
        QVector3D* position;
        QVector3D* center; // use for the reflectivity: the point where the camera is going to wrap the scene
        QVector4D* scale;
        QVector<QVector3D> verticesArray;
        QVector<QVector3D> normalArray;
        QVector<QVector2D> uvsArray;
        QVector<GLuint> indices;

        QHash<int, ShaderGL*> shadersHash;
        ShaderGL* currShader;

        QGLBuffer verticesBuffer;
        QGLBuffer normalBuffer;
        QGLBuffer uvsBuffer;
        QGLBuffer indicesBuffer;

        Util_Move_Object_Class moveObject;

        bool visible;
        bool isDoubleFace;

};

#endif // MYMESH_H
