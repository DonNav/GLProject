#ifndef MAIN_PANEL_H
#define MAIN_PANEL_H

#include <QWidget>
#include <QToolButton>
#include <QListWidget>
#include <QFileDialog>

class Main_Panel : public QWidget
{
    Q_OBJECT
public:
    explicit Main_Panel(QWidget *parent = 0);

signals:
    void object_path(QString path);
public slots:
    void show_world_panel();
    void show_object_panel();
    void show_light_panel();
    void show_save_panel();
    void show_setting_panel();
    void sizeChanged(int w, int h);
    void add_new_object();

private:

    QPalette Pal;
    QWidget * world_main_panel;

    QWidget * object_main_panel;
    QToolButton * add_object;
    QListWidget * object_list;

    QWidget * light_main_panel;

    QWidget * save_main_panel;

    QWidget * setting_main_panel;

};

#endif // MAIN_PANEL_H
