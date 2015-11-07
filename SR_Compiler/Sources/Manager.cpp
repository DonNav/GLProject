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
    my_toolbar->resize(0.05*SR_Compiler_Windows->width(), SR_Compiler_Windows->height());
    my_toolbar->setStyleSheet("background-color:#AAA; border-right: 1px solid #333;");
    my_toolbar->show();

    //Main Panel instantation
    Main_Panel = new QWidget(SR_Compiler_Windows);
    Main_Panel->resize(0.25*SR_Compiler_Windows->width(), SR_Compiler_Windows->height());
    Main_Panel->move(0.05*SR_Compiler_Windows->width(), 0);
    Main_Panel->setStyleSheet("background-color:#AAA; border-right: 1px solid #333;");
    Main_Panel->show();

    //Secondary Panel instantation
    Secondary_Panel = new QWidget(SR_Compiler_Windows);
    Secondary_Panel->resize(0.7*SR_Compiler_Windows->width(), 0.3 * SR_Compiler_Windows->height());
    Secondary_Panel->move(0.3*SR_Compiler_Windows->width(), 0.7 * SR_Compiler_Windows->height());
    Secondary_Panel->setStyleSheet("background-color:#AAA; border-top: 1px solid #333;");
    Secondary_Panel->show();

    QObject::connect(SR_Compiler_Windows, SIGNAL(sizeChange()),this, SLOT(resize_widget()));

}


//Function that resize the widget child.
// Crash often
void Manager_Class::resize_widget()
{
    GL_Widget->setSize(QSize(0.7*SR_Compiler_Windows->width(), 0.7*SR_Compiler_Windows->height()));
    GL_Widget->move(0.3*SR_Compiler_Windows->width(), 0);
    my_toolbar->resize(0.05*SR_Compiler_Windows->width(), SR_Compiler_Windows->height());
    my_toolbar->setStyleSheet("background-color:#AAA; border-right: 1px solid #333;");
    Main_Panel->resize(0.25*SR_Compiler_Windows->width(), SR_Compiler_Windows->height());
    Main_Panel->move(0.05*SR_Compiler_Windows->width(), 0);
    Secondary_Panel->resize(0.7*SR_Compiler_Windows->width(), 0.3 * SR_Compiler_Windows->height());
    Secondary_Panel->move(0.3*SR_Compiler_Windows->width(), 0.7 * SR_Compiler_Windows->height());
}


