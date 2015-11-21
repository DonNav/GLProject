#include "Manager.h"
//##################################################################
Manager_Class::Manager_Class(QStringList Commands)
{
    //qmlRegisterType<QML_ImageProvider>("CustomComponents", 1, 0, "SharedImage");

    this->isValid = true;
    QRect Desktop = QApplication::desktop()->screenGeometry(-1);

    // Main Windows instantiation.
    SR_Compiler_Windows = new Main_Windows();
    SR_Compiler_Windows->resize( Desktop.width(), Desktop.height());
    SR_Compiler_Windows->setWindowFlags(Qt::Window);
    SR_Compiler_Windows->showMaximized();
    SR_Compiler_Windows->setMinimumSize(800,600);

    // 3D OpenGL Widget instantiation.
    GL_Widget = new GLWidget(SR_Compiler_Windows);
    GL_Widget->makeCurrent();
    scene = new Scene_Root_Class(0);
    GL_Widget->setScene(scene);
    GL_Widget->setSize(QSize(0.7*SR_Compiler_Windows->width(), 0.7*SR_Compiler_Windows->height()));
    GL_Widget->move(0.3*SR_Compiler_Windows->width(), 0);
    GL_Widget->setMode("normal");
    GL_Widget->setShow(true);

    //Toolbar instantation
    my_toolbar = new Toolbar(SR_Compiler_Windows);
    my_toolbar->sizeChanged(0.05*SR_Compiler_Windows->width(), SR_Compiler_Windows->height());
    my_toolbar->show();

    //Main Panel instantation
    my_main_Panel = new Main_Panel(SR_Compiler_Windows);
    my_main_Panel->sizeChanged(0.25*SR_Compiler_Windows->width(), SR_Compiler_Windows->height());
    my_main_Panel->move(0.05*SR_Compiler_Windows->width(), 0);
    my_main_Panel->show();

    //Secondary Panel instantation
    my_second_Panel = new Second_Panel(SR_Compiler_Windows);
    my_second_Panel->sizeChanged(0.7*SR_Compiler_Windows->width(), 0.3 * SR_Compiler_Windows->height());
    my_second_Panel->move(0.3*SR_Compiler_Windows->width(), 0.7 * SR_Compiler_Windows->height());
    //my_second_Panel->setStyleSheet("background-color:#AAA; border-top: 1px solid #333;");
    my_second_Panel->show();

    QObject::connect(SR_Compiler_Windows, SIGNAL(sizeChange()),this, SLOT(resize_widget()));

    //Button connection
    QObject::connect(my_toolbar, SIGNAL(btn_quit_clicked()), SR_Compiler_Windows, SLOT(close()));
    QObject::connect(my_toolbar, SIGNAL(btn_world_clicked()), my_main_Panel, SLOT(show_world_panel()));
    QObject::connect(my_toolbar, SIGNAL(btn_object_clicked()), my_main_Panel, SLOT(show_object_panel()));
    QObject::connect(my_toolbar, SIGNAL(btn_light_clicked()), my_main_Panel, SLOT(show_light_panel()));
    QObject::connect(my_toolbar, SIGNAL(btn_save_clicked()), my_main_Panel, SLOT(show_save_panel()));
    QObject::connect(my_toolbar, SIGNAL(btn_setting_clicked()), my_main_Panel, SLOT(show_setting_panel()));

    //Main_panel connection
    QObject::connect(my_main_Panel, SIGNAL(object_path(QString)), scene, SLOT(addObject(QString)));
    QObject::connect(my_main_Panel, SIGNAL(show_background_s_panel()), my_second_Panel, SLOT(show_background_world_panel()));
    QObject::connect(my_main_Panel, SIGNAL(show_camera_s_panel()), my_second_Panel, SLOT(show_camera_world_panel()));
    QObject::connect(my_main_Panel, SIGNAL(show_fog_s_panel()), my_second_Panel, SLOT(show_fog_world_panel()));

    //Second Panel Connection
    QObject::connect(my_second_Panel, SIGNAL(backgroundColorChanged(QColor)), scene, SLOT(setBackgroundColor(QColor)));

    //Scene connection
    QObject::connect(scene, SIGNAL(sceneChanged()), GL_Widget, SLOT(worldHasChanged()));

}


//Function that resize the widget child.
// Crash often
void Manager_Class::resize_widget()
{
    GL_Widget->setSize(QSize(0.7*SR_Compiler_Windows->width(), 0.7*SR_Compiler_Windows->height()));
    GL_Widget->move(0.3*SR_Compiler_Windows->width(), 0);
    my_toolbar->sizeChanged(0.05*SR_Compiler_Windows->width(), SR_Compiler_Windows->height());
    my_main_Panel->sizeChanged(0.25*SR_Compiler_Windows->width(), SR_Compiler_Windows->height());
    my_main_Panel->move(0.05*SR_Compiler_Windows->width(), 0);
    my_second_Panel->sizeChanged(0.7*SR_Compiler_Windows->width(), 0.3 * SR_Compiler_Windows->height());
    my_second_Panel->move(0.3*SR_Compiler_Windows->width(), 0.7 * SR_Compiler_Windows->height());
}


