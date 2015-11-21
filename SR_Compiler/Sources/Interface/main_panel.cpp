#include "main_panel.h"

Main_Panel::Main_Panel(QWidget *parent) :
    QWidget(parent)
{
    Pal = QPalette(palette());
    // set black background
    Pal.setColor(QPalette::Background, QColor(0,0,0,255));
    this->setPalette(Pal);
    this->resize(parent->width(), parent->height());

    world_main_panel = new QWidget(this);
    world_main_panel->resize(this->width(), this->height());
    world_main_panel->setPalette(Pal);
    world_main_panel->move(0,0);

    world_list = new QListWidget(world_main_panel);
    world_list->resize(world_main_panel->width(), world_main_panel->height());
    world_list->move(0,0);

    QListWidgetItem * bk_world = new QListWidgetItem("Background", world_list);
    bk_world->setSelected(true);
    QListWidgetItem * fog_world = new QListWidgetItem("Fog", world_list);
    QListWidgetItem * camera_world = new QListWidgetItem("Camera", world_list);
    world_list->sortItems();
    QObject::connect(world_list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(world_item_changed(QListWidgetItem*)));

    world_main_panel->show();


    object_main_panel = new QWidget(this);
    object_main_panel->resize(this->width(), this->height());
    object_main_panel->setPalette(Pal);
    object_main_panel->move(0,0);
    object_main_panel->hide();

    object_list = new QListWidget(object_main_panel);
    object_list->resize(object_main_panel->width(), object_main_panel->height() * 0.9);
    object_list->move(0,0);

    int button_size = qMin(object_main_panel->width(), (int) (object_main_panel->height() * 0.1));
    add_object = new QToolButton(object_main_panel);
    add_object->resize(button_size, button_size);
    add_object->move(0,parent->height() * 0.9);
    add_object->setIcon(QIcon("://Graphics/Standard/Images/add.png"));
    QObject::connect(add_object, SIGNAL(clicked()), this, SLOT(add_new_object()));


    light_main_panel = new QWidget(this);
    light_main_panel->resize(this->width(), this->height());
    light_main_panel->setPalette(Pal);
    light_main_panel->move(0,0);
    light_main_panel->hide();


    save_main_panel = new QWidget(this);
    save_main_panel->resize(this->width(), this->height());
    save_main_panel->setPalette(Pal);
    save_main_panel->move(0,0);
    save_main_panel->hide();

    setting_main_panel = new QWidget(this);
    setting_main_panel->resize(this->width(), this->height());
    setting_main_panel->setPalette(Pal);
    setting_main_panel->move(0,0);
    setting_main_panel->hide();
}

void Main_Panel::hide_all(){
    object_main_panel->hide();
    light_main_panel->hide();
    save_main_panel->hide();
    setting_main_panel->hide();
    world_main_panel->hide();
}

void Main_Panel::show_world_panel(){
    this->hide_all();
    world_main_panel->show();
}

void Main_Panel::show_object_panel(){
    this->hide_all();
    object_main_panel->show();
}

void Main_Panel::show_light_panel(){
    this->hide_all();
    light_main_panel->show();
}

void Main_Panel::show_save_panel(){
    this->hide_all();
    save_main_panel->show();

}

void Main_Panel::show_setting_panel(){
    this->hide_all();
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
    QString name = fileName.split('/').last().split('.')[0];
    QListWidgetItem * object = new QListWidgetItem(name, object_list);
    object->setSelected(true);
    object_list->sortItems();
    emit object_path(fileName);
}

void Main_Panel::world_item_changed(QListWidgetItem* my_item){
    if (my_item->text().contains("Background")){
        emit show_background_s_panel();
    }
    else if (my_item->text().contains("Fog")){
        emit show_fog_s_panel();
    }
    else if (my_item->text().contains("Camera")){
        emit show_camera_s_panel();
    }

}
