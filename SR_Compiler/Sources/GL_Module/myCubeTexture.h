#ifndef MYCUBETEXTURE_H
#define MYCUBETEXTURE_H

#include <QObject>
#include <QtOpenGL>
#include<QGLWidget>

class MyCubeTexture: public QObject
{
    Q_OBJECT
public:
    MyCubeTexture(QObject *parent = 0);

public slots:
    void setImage(QString directory);

    GLuint getTexture(){return this->texture;}

    bool IsTexture(){ return this->isTexture;}

private:
    bool isTexture;
    GLuint texture;
};

#endif // MYCUBETEXTURE_H
