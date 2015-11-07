#include "Manager.h"
//##################################################################
Manager_Class::Manager_Class(QStringList Commands)
{
    qmlRegisterType<QML_ImageProvider>("CustomComponents", 1, 0, "SharedImage");

    this->isValid = true;
    Parameters_Class *Settings = new Parameters_Class(Commands);

    GL_Widget = new GLWidget();
    GL_Widget->makeCurrent();

     scene = new Scene_Root_Class(0);
     GL_Widget->setScene(scene);


    QRect Desktop = QApplication::desktop()->screenGeometry(-1);
    QSize View(qMin(1024, Desktop.width()), qMin(768, Desktop.height()));
    GL_Widget->setSize(QSize(Settings->value("width",  View.width()), Settings->value("height",  View.height())));
    GL_Widget->setMode("normal");
    GL_Widget->setShow(true);


    QML_Widget = new QML_Widget_Class();
    QML_Widget->setSize(QSize(Settings->value("width",  View.width()), Settings->value("height",  View.height())));
    QML_Widget->show();

    QString ObjectQML = QString("ImageProvider");
    ImageProvider = QML_Widget->rootObject()->findChild<QML_ImageProvider*>(ObjectQML.toLatin1().data());

    QObject::connect(this->GL_Widget, SIGNAL(finished(QImage)), this->ImageProvider, SLOT(updateImage(QImage)));

    QML_Widget->rootContext()->setContextProperty("GL_Manager",this->GL_Widget);
    QML_Widget->rootContext()->setContextProperty("Scene_Manager",this->scene);


}



