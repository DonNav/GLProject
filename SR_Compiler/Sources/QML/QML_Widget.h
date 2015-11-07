#ifndef QML_Widget_Header
#define QML_Widget_Header

#include <QObject>
#include <iostream>

#include <QWidget>
#include <QDeclarativeView>
#include <QDeclarativeContext>
#include <QGraphicsObject>
#include <QFocusEvent>
#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLFormat>

// ******************************************
class QML_Widget_Class: public QDeclarativeView
{
 Q_OBJECT

public:
    QML_Widget_Class(QWidget *parent=0, bool SoftGL=false ) ;

public slots:
    void setSize(QSize Widget_Size);
    void setShow(bool Widget_State);
    int getHeight();
    int getWidth();

signals:
    void sizeChanged();
    void modeChanged();
    void requestForward();
    void requestBackward();

private:
    QGLWidget *OpenGL_Display;
    bool OpenGL_Enabled;


};
#endif
