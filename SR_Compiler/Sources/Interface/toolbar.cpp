#include "toolbar.h"

Toolbar::Toolbar(QWidget *parent) : QWidget(parent)
{
    Pal = QPalette(palette());
    // set black background
    Pal.setColor(QPalette::Background, QColor(0,0,0,255));
    this->setPalette(Pal);

    int button_size = qMin(this->width(), this->height()/5);
    button_world = new QToolButton(this);
    button_world->resize(button_size, button_size);
    button_world->move(0,0);
    button_world->setIcon(QIcon("://Graphics/Standard/Images/world.png"));
    QObject::connect(button_world, SIGNAL(clicked()),this, SLOT(btn_world_click()));

    button_object = new QToolButton(this);
    button_object->resize(button_size, button_size);
    button_object->move(0,button_size);
    button_object->setIcon(QIcon("://Graphics/Standard/Images/object.png"));
    QObject::connect(button_object, SIGNAL(clicked()),this, SLOT(btn_object_click()));

    button_light = new QToolButton(this);
    button_light->resize(button_size, button_size);
    button_light->move(0,2*button_size);
    button_light->setIcon(QIcon("://Graphics/Standard/Images/icons_light.png"));
    QObject::connect(button_light, SIGNAL(clicked()),this, SLOT(btn_light_click()));

    button_save = new QToolButton(this);
    button_save->resize(button_size, button_size);
    button_save->move(0,3*button_size);
    button_save->setIcon(QIcon("://Graphics/Standard/Images/icons_save.png"));
    QObject::connect(button_world, SIGNAL(clicked()),this, SLOT(btn_save_click()));

    button_setting = new QToolButton(this);
    button_setting->resize(button_size, button_size);
    button_setting->move(0,4*button_size);
    button_setting->setIcon(QIcon("://Graphics/Standard/Images/icons_setting.png"));
    QObject::connect(button_setting, SIGNAL(clicked()),this, SLOT(btn_setting_click()));

    button_quit = new QToolButton(this);
    button_quit->resize(button_size, button_size);
    button_quit->move(0,5*button_size);
    button_quit->setIcon(QIcon("://Graphics/Standard/Images/icons_quit.png"));
    QObject::connect(button_quit, SIGNAL(clicked()),this, SLOT(btn_quit_click()));
}

void Toolbar::sizeChanged(int width, int height){
    this->resize(width, height);
    int button_size = qMin(this->width(), this->height()/5);

    button_world->resize(button_size, button_size);
    button_world->move(0,0);

    button_object->resize(button_size, button_size);
    button_object->move(0,button_size);

    button_light->resize(button_size, button_size);
    button_light->move(0,2*button_size);

    button_save->resize(button_size, button_size);
    button_save->move(0,3*button_size);

    button_setting->resize(button_size, button_size);
    button_setting->move(0,4*button_size);

    button_quit->resize(button_size, button_size);
    button_quit->move(0,5*button_size);

    button_size = button_size / 1.5;
    button_world->setIconSize(QSize(button_size,button_size));
    button_object->setIconSize(QSize(button_size,button_size));
    button_light->setIconSize(QSize(button_size,button_size));
    button_save->setIconSize(QSize(button_size,button_size));
    button_setting->setIconSize(QSize(button_size,button_size));
    button_quit->setIconSize(QSize(button_size,button_size));

    this->setPalette(Pal);


}
