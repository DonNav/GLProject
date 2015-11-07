#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QObject>
#include <QtOpenGL>
#include <QGLWidget>
#include <QBasicTimer>
#include <QtCore/qmath.h>
#include <QtOpenGL/QGLFunctions>
#include <iostream>
#include <QtWidgets/QFileDialog>

#include "mymesh.h"
#include "SceneRoot.h"
#include "shadergl.h"

class QBasicTimer;


class GLWidget : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    CameraGL* camera;

protected:
    void initializeGL();
    void paintGL();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *);

    void resizeGL(int width, int height);

    void direct_render();

    void render_OffScreen();
    void renderGL();




    void timerEvent(QTimerEvent *e);

public slots:
    void setScene(Scene_Root_Class* sc);
    Scene_Root_Class* getScene() { return this->scene;}

    void init() { initializeGL();}

    void setMousePressEvent(QMouseEvent *event) { this->mousePressEvent(event);}
    void setMousePressEvent(int x, int y);
    void setMouseMoveEvent(QMouseEvent *event) { this->mouseMoveEvent(event);}
    void setMouseMoveEvent(int x, int y);
    void wheelEvent ( QWheelEvent * event );

    void setMode(QString Widget_Mode);
    void setPosition(QPoint Widget_Position);
    void setSize(QSize Widget_Size);
    void setShow(bool Widget_Status);

    void  Open();
    void Export();

signals:
    void paintOver();
    void finished(QImage);

private:
    int Width, Height;

    int xRot;
    int yRot;
    int zRot;

    QPoint lastPos;

    QBasicTimer* tRender;
    QTime* tFPS;

    Scene_Root_Class* scene;

    QPoint Stored_Position;
    QString Stored_Mode;

    QGLFramebufferObject* m_render_offscreen;
    QGLFramebufferObject* m_render;

    ShaderGL* render_shader;


    int count;







};

#endif // GLWIDGET_H
