#include "QML_Widget.h"
// ######################################################################
QML_Widget_Class::QML_Widget_Class(QWidget *parent, bool SoftGL):QDeclarativeView(parent)
{

    bool HardGL= QGLFormat::hasOpenGL();
    if (HardGL) { std::cout << "[Widget] => OpenGL hardware acceleration detected." << std::endl;    }

    OpenGL_Enabled = (!SoftGL && HardGL);
    if (OpenGL_Enabled)
    {
        QGLFormat OpenGL_Format = QGLFormat::defaultFormat();
        OpenGL_Format.setSampleBuffers(false);
        OpenGL_Display = new QGLWidget(OpenGL_Format);
        OpenGL_Display->setAutoFillBackground(true);
        this->setViewport(OpenGL_Display);
    }
    else std::cout << "[Widget] => Disabling OpenGL hardware acceleration." << std::endl;

    this->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
   // this->setWindowFlags(Qt::FramelessWindowHint);// Set Windows to Borderless
    this->autoFillBackground();
    this->setFocusPolicy(Qt::ClickFocus); // Focus Management setting
    this->setResizeMode(QDeclarativeView::SizeRootObjectToView);
    this->hide(); // Starting in hidden mode ...

    this->rootContext()->setContextProperty("backend",this);
    this->setSource(QUrl("qrc:/Graphics/Standard/QML/MainQML.qml"));
}
// ######################################################################
void QML_Widget_Class::setSize(QSize Widget_Size)
{
    this->resize(Widget_Size);
    if (OpenGL_Enabled) OpenGL_Display->resize(Widget_Size);
    emit this->sizeChanged();
}
// ######################################################################
void QML_Widget_Class::setShow(bool Widget_State)
{
    if (Widget_State == false)
        this->hide();
    else
        this->show();
}
// ######################################################################
// ######################################################################
int QML_Widget_Class::getWidth()
{ return this->width();}
// ######################################################################
int QML_Widget_Class::getHeight()
{ return this->height();}
