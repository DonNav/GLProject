#include "main_panel.h"

Main_Panel::Main_Panel(QWidget *parent) :
    QWidget(parent)
{
    Pal = QPalette(palette());
    // set black background
    Pal.setColor(QPalette::Background, QColor(0,0,0,255));
    this->setPalette(Pal);

    world_main_panel = new QWidget(this);
    world_main_panel->resize(parent->width(), parent->height());
    world_main_panel->setPalette(Pal);
    world_main_panel->move(0,0);
    world_main_panel->show();

    object_main_panel = new QWidget(this);
    object_main_panel->resize(parent->width(), parent->height());
    object_main_panel->setPalette(Pal);
    object_main_panel->move(0,0);
    object_main_panel->hide();

    object_list = new QListWidget(object_main_panel);
    object_list->resize(parent->width(), parent->height() * 0.9);
    object_list->move(0,0);

    int button_size = qMin(parent->width(), (int) (parent->height() * 0.1));
    add_object = new QToolButton(object_main_panel);
    add_object->resize(button_size, button_size);
    add_object->move(0,parent->height() * 0.9);
    add_object->setIcon(QIcon("://Graphics/Standard/Images/add.png"));
    QObject::connect(add_object, SIGNAL(clicked()), this, SLOT(add_new_object()));


    light_main_panel = new QWidget(this);
    light_main_panel->resize(parent->width(), parent->height());
    light_main_panel->setPalette(Pal);
    light_main_panel->move(0,0);
    light_main_panel->hide();


    save_main_panel = new QWidget(this);
    save_main_panel->resize(parent->width(), parent->height());
    save_main_panel->setPalette(Pal);
    save_main_panel->move(0,0);
    save_main_panel->hide();

    setting_main_panel = new QWidget(this);
    setting_main_panel->resize(parent->width(), parent->height());
    setting_main_panel->setPalette(Pal);
    setting_main_panel->move(0,0);
    setting_main_panel->hide();
}

void Main_Panel::show_world_panel(){
    object_main_panel->hide();
    light_main_panel->hide();
    save_main_panel->hide();
    setting_main_panel->hide();
    world_main_panel->show();
}

void Main_Panel::show_object_panel(){
    world_main_panel->hide();
    light_main_panel->hide();
    save_main_panel->hide();
    setting_main_panel->hide();
    object_main_panel->show();
}

void Main_Panel::show_light_panel(){
    world_main_panel->hide();
    save_main_panel->hide();
    setting_main_panel->hide();
    object_main_panel->hide();
    light_main_panel->show();
}

void Main_Panel::show_save_panel(){
    world_main_panel->hide();
    object_main_panel->hide();
    light_main_panel->hide();
    setting_main_panel->hide();
    save_main_panel->show();

}

void Main_Panel::show_setting_panel(){
    world_main_panel->hide();
    object_main_panel->hide();
    light_main_panel->hide();
    save_main_panel->hide();
    setting_main_panel->show();

}


void Main_Panel::sizeChanged(int w, int h){
    this->resize(w, h);
    world_main_panel->resize(w,h);
    object_main_panel->resize(w,h);
    save_main_panel->resize(w,h);
    setting_main_panel->resize(w,h);
    light_main_panel->resize(w,h);


}

void Main_Panel::add_new_object(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File Object"), "./", tr("Files Object (*.obj *.dna *.sre *.far"));
    emit object_path(fileName);
}
