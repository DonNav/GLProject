#-------------------------------------------------
#
# Project created by QtCreator 2012-10-29T10:06:23
#
#-------------------------------------------------
# authors: Donatien Naves <donatien.naves@gmail.com>

QT+= \
            gui\
            declarative \
            core \
            opengl\

TARGET = SR_Shower
INSTALLS += target

CONFIG	+= console link_pkgconfig
CONFIG	-= app_bundle

TEMPLATE = app

android {
folder_01.source = Graphics/Standard/QML
folder_01.target = ./
DEPLOYMENTFOLDERS = folder_01

folder_03.source = Graphics/Standard/Images
folder_03.target = ./
DEPLOYMENTFOLDERS += folder_03
}


# Remove all QDebug prints
#DEFINES += QT_NO_DEBUG_OUTPUT
#DEFINES += QT_NO_DEBUG

SOURCES += \
    Launcher.cpp \
    Manager.cpp \
    GL_Module/utilMoveObjectClass.cpp \
    GL_Module/shadergl.cpp \
    GL_Module/SceneRoot.cpp \
    GL_Module/RootObject.cpp \
    GL_Module/myTexture.cpp \
    GL_Module/mymesh.cpp \
    GL_Module/myMaterial.cpp \
    GL_Module/myfog.cpp \
    GL_Module/myCubeTexture.cpp \
    GL_Module/lightGL.cpp \
    GL_Module/GlWidget.cpp \
    GL_Module/cameraGL.cpp \
    Parameters/Parameters.cpp \
    QML/QML_ImageProvider.cpp \
    QML/QML_Widget.cpp


HEADERS  += \
    Manager.h \
    GL_Module/Gl_Module.h \
    GL_Module/utilMoveObjectClass.h \
    GL_Module/shadergl.h \
    GL_Module/SceneRoot.h \
    GL_Module/RootObject.h \
    GL_Module/myTexture.h \
    GL_Module/mymesh.h \
    GL_Module/myMaterial.h \
    GL_Module/myfog.h \
    GL_Module/myCubeTexture.h \
    GL_Module/lightGL.h \
    GL_Module/GlWidget.h \
    GL_Module/cameraGL.h \
    Parameters/Parameters.h \
    QML/QML_ImageProvider.h \
    QML/QML_Widget.h

MOC_DIR = .moc
OBJECTS_DIR = .obj

RESOURCES += \
    ressources.qrc

folder_01.source = Graphics
folder_01.target = Graphics
DEPLOYMENTFOLDERS += folder_01

OTHER_FILES += \
    Graphics/Standard/QML/MainQML.qml \
    QML/Dialogs/qmldir \
    Graphics/Standard/QML/Dialogs/DefaultColorDialog.qml \
    Graphics/Standard/QML/Dialogs/DefaultFileDialog.qml \
    Graphics/Standard/QML/Dialogs/DefaultFontDialog.qml \
    Graphics/Standard/QML/Dialogs/DefaultMessageDialog.qml \
    Graphics/Standard/QML/Dialogs/WidgetColorDialog.qml \
    Graphics/Standard/QML/Dialogs/WidgetFileDialog.qml \
    Graphics/Standard/QML/Dialogs/WidgetFontDialog.qml \
    Graphics/Standard/QML/Dialogs/WidgetMessageDialog.qml \
    Graphics/Standard/QML/Dialogs/qml/Button.qml \
    Graphics/Standard/QML/Dialogs/qml/CheckBox.qml \
    Graphics/Standard/QML/Dialogs/qml/ColorSlider.qml \
    Graphics/Standard/QML/Dialogs/qml/DefaultWindowDecoration.qml \
    Graphics/Standard/QML/Dialogs/qml/EdgeFade.qml \
    Graphics/Standard/QML/Dialogs/qml/TextField.qml



