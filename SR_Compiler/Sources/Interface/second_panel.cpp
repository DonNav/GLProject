#include "second_panel.h"

Second_Panel::Second_Panel(QWidget *parent) :
    QWidget(parent)
{
    Pal = QPalette(palette());
    // set black background
    Pal.setColor(QPalette::Background, QColor(0,0,0,255));
    this->setPalette(Pal);

    //###################################################################################################
    //World Panel
    //Background configuration
    world_background_second_panel = new QWidget(this);
    world_background_second_panel->resize(parent->width(), parent->height());
    world_background_second_panel->setPalette(Pal);
    world_background_second_panel->move(0,0);
    world_background_second_panel->show();

    QGridLayout * world_background_layout = new QGridLayout();
    world_background_second_panel->setLayout(world_background_layout);

    QLabel * Background_Color_Label = new QLabel(world_background_second_panel);
    Background_Color_Label->setText("Background Color:");
    world_background_layout->addWidget(Background_Color_Label,0,0,1,2);

    QLabel * Background_Color_R_Label = new QLabel(world_background_second_panel);
    Background_Color_R_Label->setText("R:");
    world_background_layout->addWidget(Background_Color_R_Label,1,0,1,1);
    QSlider * R_Color_Slider = new QSlider(Qt::Horizontal, world_background_second_panel);
    R_Color_Slider->setMinimum(0);
    R_Color_Slider->setMaximum(255);
    R_Color_Slider->setValue(76);
    world_background_layout->addWidget(R_Color_Slider,1,1,1,1);
    R_Color_SpinBox = new QSpinBox(world_background_second_panel);
    R_Color_SpinBox->setValue(76);
    R_Color_SpinBox->setMaximum(255);
    R_Color_SpinBox->setMinimum(0);
    world_background_layout->addWidget(R_Color_SpinBox,1,2,1,1);
    QObject::connect(R_Color_Slider, SIGNAL(valueChanged(int)), R_Color_SpinBox, SLOT(setValue(int)));
    QObject::connect(R_Color_SpinBox, SIGNAL(valueChanged(int)), R_Color_Slider, SLOT(setValue(int)));
    QObject::connect(R_Color_SpinBox, SIGNAL(valueChanged(int)), this, SLOT(colorChanged(int)));



    QLabel * Background_Color_G_Label = new QLabel(world_background_second_panel);
    Background_Color_G_Label->setText("G:");
    world_background_layout->addWidget(Background_Color_G_Label,2,0,1,1);
    QSlider * G_Color_Slider = new QSlider(Qt::Horizontal, world_background_second_panel);
    G_Color_Slider->setMinimum(0);
    G_Color_Slider->setMaximum(255);
    G_Color_Slider->setValue(76);
    world_background_layout->addWidget(G_Color_Slider,2,1,1,1);
    G_Color_SpinBox = new QSpinBox(world_background_second_panel);
    G_Color_SpinBox->setValue(76);
    G_Color_SpinBox->setMaximum(255);
    G_Color_SpinBox->setMinimum(0);
    world_background_layout->addWidget(G_Color_SpinBox,2,2,1,1);
    QObject::connect(G_Color_Slider, SIGNAL(valueChanged(int)), G_Color_SpinBox, SLOT(setValue(int)));
    QObject::connect(G_Color_SpinBox, SIGNAL(valueChanged(int)), G_Color_Slider, SLOT(setValue(int)));
    QObject::connect(G_Color_SpinBox, SIGNAL(valueChanged(int)), this, SLOT(colorChanged(int)));


    QLabel * Background_Color_B_Label = new QLabel(world_background_second_panel);
    Background_Color_B_Label->setText("B:");
    world_background_layout->addWidget(Background_Color_B_Label,3,0,1,1);
    QSlider * B_Color_Slider = new QSlider(Qt::Horizontal, world_background_second_panel);
    B_Color_Slider->setMinimum(0);
    B_Color_Slider->setMaximum(255);
    B_Color_Slider->setValue(76);
    world_background_layout->addWidget(B_Color_Slider,3,1,1,1);
    B_Color_SpinBox = new QSpinBox(world_background_second_panel);
    B_Color_SpinBox->setValue(76);
    B_Color_SpinBox->setMaximum(255);
    B_Color_SpinBox->setMinimum(0);
    world_background_layout->addWidget(B_Color_SpinBox,3,2,1,1);
    QObject::connect(B_Color_Slider, SIGNAL(valueChanged(int)), B_Color_SpinBox, SLOT(setValue(int)));
    QObject::connect(B_Color_SpinBox, SIGNAL(valueChanged(int)), B_Color_Slider, SLOT(setValue(int)));
    QObject::connect(B_Color_SpinBox, SIGNAL(valueChanged(int)), this, SLOT(colorChanged(int)));

    QLabel * Background_Color_A_Label = new QLabel(world_background_second_panel);
    Background_Color_A_Label->setText("Alpha:");
    world_background_layout->addWidget(Background_Color_A_Label,4,0,1,1);
    QSlider * A_Color_Slider = new QSlider(Qt::Horizontal, world_background_second_panel);
    A_Color_Slider->setMinimum(0);
    A_Color_Slider->setMaximum(255);
    A_Color_Slider->setValue(255);
    world_background_layout->addWidget(A_Color_Slider,4,1,1,1);
    A_Color_SpinBox = new QSpinBox(world_background_second_panel);
    A_Color_SpinBox->setValue(255);
    A_Color_SpinBox->setMaximum(255);
    A_Color_SpinBox->setMinimum(0);
    world_background_layout->addWidget(A_Color_SpinBox,4,2,1,1);
    QObject::connect(A_Color_Slider, SIGNAL(valueChanged(int)), A_Color_SpinBox, SLOT(setValue(int)));
    QObject::connect(A_Color_SpinBox, SIGNAL(valueChanged(int)), A_Color_Slider, SLOT(setValue(int)));
    QObject::connect(A_Color_SpinBox, SIGNAL(valueChanged(int)), this, SLOT(colorChanged(int)));


    //Camera configuration
    world_camera_second_panel = new QWidget(this);
    world_camera_second_panel->resize(parent->width(), parent->height());
    world_camera_second_panel->setPalette(Pal);
    world_camera_second_panel->move(0,0);
    world_camera_second_panel->hide();

    //Fog configuration
    world_fog_second_panel = new QWidget(this);
    world_fog_second_panel->resize(parent->width(), parent->height());
    world_fog_second_panel->setPalette(Pal);
    world_fog_second_panel->move(0,0);
    world_fog_second_panel->hide();

    //###################################################################################################
    //Object panel
    object_second_panel = new QWidget(this);
    object_second_panel->resize(parent->width(), parent->height());
    object_second_panel->setPalette(Pal);
    object_second_panel->move(0,0);
    object_second_panel->hide();

    //###################################################################################################
    light_second_panel = new QWidget(this);
    light_second_panel->resize(parent->width(), parent->height());
    light_second_panel->setPalette(Pal);
    light_second_panel->move(0,0);
    light_second_panel->hide();

    //###################################################################################################
    save_second_panel = new QWidget(this);
    save_second_panel->resize(parent->width(), parent->height());
    save_second_panel->setPalette(Pal);
    save_second_panel->move(0,0);
    save_second_panel->hide();

    //###################################################################################################
    setting_second_panel = new QWidget(this);
    setting_second_panel->resize(parent->width(), parent->height());
    setting_second_panel->setPalette(Pal);
    setting_second_panel->move(0,0);
    setting_second_panel->hide();
}

//####################################################################
//Background Panel showing
void Second_Panel::show_background_world_panel(){
    this->hide_all();
    world_background_second_panel->show();
}
void Second_Panel::show_camera_world_panel(){
    this->hide_all();
    world_camera_second_panel->show();

}
void Second_Panel::show_fog_world_panel(){
    this->hide_all();
    world_fog_second_panel->show();
}

//####################################################################
void Second_Panel::show_object_panel(){
    this->hide_all();
    object_second_panel->show();
}

//####################################################################
void Second_Panel::show_light_panel(){
    this->hide_all();
    light_second_panel->show();
}

//####################################################################
void Second_Panel::show_save_panel(){
    this->hide_all();
    save_second_panel->show();
}

//####################################################################
void Second_Panel::show_setting_panel(){
    this->hide_all();
    setting_second_panel->show();
}

//####################################################################
void Second_Panel::hide_all(){
    world_background_second_panel->hide();
    world_fog_second_panel->hide();
    world_camera_second_panel->hide();
    object_second_panel->hide();
    light_second_panel->hide();
    save_second_panel->hide();
    setting_second_panel->hide();
}

void Second_Panel::sizeChanged(int w, int h){
    this->resize(w, h);
    world_background_second_panel->resize(w,h);
    world_fog_second_panel->resize(w,h);
    world_camera_second_panel->resize(w,h);
    object_second_panel->resize(w,h);
    save_second_panel->resize(w,h);
    setting_second_panel->resize(w,h);
    light_second_panel->resize(w,h);
}

//####################################################################
void Second_Panel::colorChanged(int value){
    emit backgroundColorChanged(QColor(R_Color_SpinBox->value(), G_Color_SpinBox->value(),B_Color_SpinBox->value(),A_Color_SpinBox->value()));
}

