#include "main_windows.h"

Main_Windows::Main_Windows(QWidget *parent) : QWidget(parent)
{

}

void Main_Windows::resizeEvent(QResizeEvent *re ){
    emit sizeChange();
}

