#include "myfog.h"

myFog::myFog(QObject *parent) :
    QObject(parent)
{
    this->density = 0.0f;
    this->enabled = true;


    this->Color[0] = 0.0f;
    this->Color[1] = 0.0f;
    this->Color[2] = 0.0f;
    this->Color[3] = 0.0f;


}
