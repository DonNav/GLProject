#ifndef MYFOG_H
#define MYFOG_H

#include <QObject>
#include <QVector4D>
#include <QtOpenGL>

class myFog : public QObject
{
    Q_OBJECT
public:
    explicit myFog(QObject *parent = 0);
    
signals:
    
public slots:
    void setColor(double r, double g, double b, double a){Color[0] = r; Color[1] = g; Color[2] = b; Color[3] = a; }
    GLfloat* getGLColor(){ return Color;}


    void setDensity(float d){ density = d;}
    float getDensity(){ return density;}

    void setEnabled(bool b){this->enabled = b;}
    bool getEnabled(){return enabled;}

private:
    float density;
    bool enabled;
    GLfloat Color[4];

};

#endif // MYFOG_H
