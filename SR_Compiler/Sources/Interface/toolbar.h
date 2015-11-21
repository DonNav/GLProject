#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QToolButton>

class Toolbar : public QWidget
{
    Q_OBJECT
    public:
        explicit Toolbar(QWidget *parent = 0);

    public slots:
        void sizeChanged(int width, int height);
        void btn_world_click(){emit this->btn_world_clicked();}
        void btn_object_click(){emit this->btn_object_clicked();}
        void btn_light_click(){emit this->btn_light_clicked();}
        void btn_save_click(){emit this->btn_save_clicked();}
        void btn_setting_click(){emit this->btn_setting_clicked();}
        void btn_quit_click(){emit this->btn_quit_clicked();}

    signals:
        void btn_world_clicked();
        void btn_object_clicked();
        void btn_light_clicked();
        void btn_save_clicked();
        void btn_setting_clicked();
        void btn_quit_clicked();

    private:

        QToolButton * button_world;
        QToolButton * button_object;
        QToolButton * button_light;
        QToolButton * button_save;
        QToolButton * button_setting;
        QToolButton * button_quit;
        QPalette Pal;
};

#endif // TOOLBAR_H
