#ifndef MYTEXTURE_H
#define MYTEXTURE_H

#include <QObject>
#include <QtOpenGL>
#include<QGLWidget>
#include <QtOpenGL/qgl.h>
#include <QtOpenGL>

class MyTexture : public QObject
{
    Q_OBJECT
public:
    explicit MyTexture(QObject *parent = 0);

signals:
    
public slots:
    QImage getImage(){ return this->image;}
    void setImage(QString filename);
    void setImage(QImage imageTmp);

    GLuint getTexture();

    bool IsTexture(){ return this->isTexture;}

private:
    QImage image;
    bool isTexture;
    GLuint texture;
    
};

#endif // MYTEXTURE_H
