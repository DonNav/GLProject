#ifndef Data_Model_Header
#define Data_Model_Header

#include <QObject>
#include <QApplication>
#include <QDesktopWidget>

#include "Parameters/Parameters.h"

#include "GL_Module/GlWidget.h"
#include "GL_Module/SceneRoot.h"

#include "QML/QML_ImageProvider.h"
#include "QML/QML_Widget.h"


class Manager_Class : public QObject
{
    Q_OBJECT

public:
    explicit Manager_Class(QStringList Commands =  QStringList());
    bool isValid; // Mandatory for initialisation ...

    void init_scene();


private:
    GLWidget* GL_Widget;
    Scene_Root_Class* scene;

    QML_Widget_Class* QML_Widget;
    QML_ImageProvider* ImageProvider;
};
#endif
