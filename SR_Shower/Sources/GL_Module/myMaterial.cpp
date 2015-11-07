#include "myMaterial.h"

myMaterial::myMaterial(QObject *parent) :
    QObject(parent)
{
    this->ambient = new QVector4D(0.0,0.0,0.0,1.0);
    this->diffuse = new QVector4D(0.0,0.0,0.0,1.0);
    this->diffuseSecond = new QVector4D(0.0,0.0,0.0,1.0);
    this->emission = new QVector4D(0.0,0.0,0.0,1.0);
    this->specular = new QVector4D(1.0,1.0,1.0,1.0);

    this->reflectivity = 0;
    this->refraction = 1.0;
    this->gloss = 0;

    this->texture = new MyTexture();
    this->bumpMap = new MyTexture();
    this->cubeTexture = new MyCubeTexture();
    this->reflexionTexture = new MyCubeTexture();
    this->textureScaling = new QVector2D(1,1);
}

void myMaterial::readMlt(QString filename){
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"Error reading Mlt file";return;
    }
    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList str = line.split(' ');
        int n = str.length();
        if (str[n-1].length() == 0) n--;

        if (str.at(0) == "Ka"){
            this->setAmbient(str.at(1).toDouble(), str.at(2).toDouble(), str.at(3).toDouble(),1.0);
        }
        else if (str.at(0) == "Kd"){
            this->setDiffuse(str.at(1).toDouble(), str.at(2).toDouble(), str.at(3).toDouble(),1.0);
        }
        else if (str.at(0) == "Ks"){
            this->setSpecular(str.at(1).toDouble(), str.at(2).toDouble(), str.at(3).toDouble(),1.0);
        }
        else if (str.at(0) == "d" || str.at(0) == "Tr"){
            this->ambient->setW(str.at(1).toDouble());
        }
        else if (str.at(0) == "Ns"){
            this->setGloss(str.at(1).toDouble());
        }

    }
    file.close();
}
