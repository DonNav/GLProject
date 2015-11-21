#ifndef Data_Model_Header
#define Data_Model_Header

#include <QObject>
#include <QApplication>
#include <QDesktopWidget>

#include "Parameters/Parameters.h"

#include "GL_Module/GlWidget.h"
#include "GL_Module/SceneRoot.h"

#include "Interface/main_windows.h"
#include "Interface/toolbar.h"
#include "Interface/main_panel.h"
#include "Interface/second_panel.h"

class Manager_Class : public QObject
{
    Q_OBJECT

public:
    explicit Manager_Class(QStringList Commands =  QStringList());
    bool isValid; // Mandatory for initialisation ...
    void init_scene();

public slots:
    void resize_widget();


signals:


private:
    GLWidget* GL_Widget;
    Scene_Root_Class* scene;
    Main_Windows* SR_Compiler_Windows;
    Toolbar* my_toolbar;
    Main_Panel* my_main_Panel;
    Second_Panel* my_second_Panel;

};
#endif
