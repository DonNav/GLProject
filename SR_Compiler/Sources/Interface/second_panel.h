#ifndef SECOND_PANEL_H
#define SECOND_PANEL_H

#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QGridLayout>
#include <QSpinBox>
#include <QDebug>

class Second_Panel : public QWidget
{
    Q_OBJECT
public:
    explicit Second_Panel(QWidget *parent = 0);

signals:
    void backgroundColorChanged(QColor);

public slots:
    void show_background_world_panel();
    void colorChanged(int value);
    void show_fog_world_panel();
    void show_camera_world_panel();

    void show_object_panel();
    void show_light_panel();
    void show_save_panel();
    void show_setting_panel();
    void sizeChanged(int w, int h);

    void hide_all();

private:
    QPalette Pal;
    QWidget * world_background_second_panel;
    QSpinBox * R_Color_SpinBox;
    QSpinBox * G_Color_SpinBox;
    QSpinBox * B_Color_SpinBox;
    QSpinBox * A_Color_SpinBox;

    QWidget * world_camera_second_panel;
    QWidget * world_fog_second_panel;

    QWidget * object_second_panel;

    QWidget * light_second_panel;

    QWidget * save_second_panel;

    QWidget * setting_second_panel;


};

#endif // SECOND_PANEL_H
