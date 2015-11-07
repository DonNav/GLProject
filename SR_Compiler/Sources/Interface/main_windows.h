#ifndef MAIN_WINDOWS_H
#define MAIN_WINDOWS_H

#include <QWidget>

class Main_Windows : public QWidget
{
    Q_OBJECT
public:
    explicit Main_Windows(QWidget *parent = 0);

protected:
       void resizeEvent ( QResizeEvent *re );
signals:
       void sizeChange();

};

#endif // MAIN_WINDOWS_H
