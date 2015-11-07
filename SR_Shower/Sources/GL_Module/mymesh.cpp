#include "mymesh.h"

static double radians( double degrees ){
    return ( M_PI*degrees ) / 180;
}



myMesh::myMesh(QObject *parent) :
    QObject(parent), verticesBuffer(QGLBuffer::VertexBuffer), indicesBuffer(QGLBuffer::IndexBuffer)
{

    this->position = new QVector3D(0,0,0);
    this->center = new QVector3D(0,0,0);
    this->scale = new QVector4D(1,1,1, 1);
    this->mat = new myMaterial();
    this->visible = true;
    this->currShader = NULL;

    this->isDoubleFace = false;

    QObject::connect(&moveObject, SIGNAL(newPosition(QVector3D)), this, SLOT(setPosition(QVector3D)));
    QObject::connect(&moveObject, SIGNAL(newRotation(float,float,float)),this, SLOT(computeRotation(float,float,float)));

}


bool myMesh::read(QString filename){


    QVector<QVector3D> verticesArrayTmp;
    QVector<QVector3D> normalArrayTmp;
    QVector<QVector2D> uvsArrayTmp;
    QList<int> vInd;
    QList<int> uvInd;
    QList<int> nInd;

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"Error";return false;
    }
    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList str = line.split(' ');
        int n = str.length();
        if (str[n-1].length() == 0) n--;

        if (str.at(0) == "v"){
            verticesArrayTmp.push_back(QVector3D(str.at(1).toDouble(), str.at(2).toDouble(), str.at(3).toDouble()));

        }
        else if (str.at(0) == "vt"){
            uvsArrayTmp.push_back(QVector2D(str.at(1).toDouble(), str.at(2).toDouble()));
        }
        else if (str.at(0) == "vn"){
            normalArrayTmp.push_back(QVector3D(str.at(1).toDouble(), str.at(2).toDouble(), str.at(3).toDouble()));
        }
        else if (str.at(0) == "f"){
            for (int j = 1; j < n; j++)
            {

                QStringList i = str.at(j).split('/',QString::KeepEmptyParts );
                vInd.append(i.at(0).toInt() - 1);
                uvInd.append(i.at(1).toInt() - 1);
                nInd.append(i.at(2).toInt() - 1);


            }


        }

    }
    file.close();

    verticesArray.clear();
    normalArray.clear();
    uvsArray.clear();
    indices.clear();
    for (int i = 0 ; i < vInd.size(); i++){
        int index = -1;
        index = getSimilarVertexIndex(verticesArrayTmp.at(vInd[i]),normalArrayTmp.at(nInd[i]), uvsArrayTmp.at(uvInd[i]), verticesArray, normalArray, uvsArray);
        if (index >-1){
            indices.push_back(index);
        }
        else {
            verticesArray.push_back(verticesArrayTmp.at(vInd[i]));
            normalArray.push_back(normalArrayTmp.at(nInd[i]));
            uvsArray.push_back(uvsArrayTmp.at(uvInd[i]));
            indices.push_back(verticesArray.size() - 1 );
        }
   }


    verticesBuffer.create();
    verticesBuffer.bind();
    verticesBuffer.allocate(verticesArray.constData(), verticesArray.size() * sizeof(QVector3D) );
    verticesBuffer.release();

    uvsBuffer.create();
    uvsBuffer.bind();
    uvsBuffer.allocate(uvsArray.constData(), uvsArray.size() * sizeof(QVector2D));
    uvsBuffer.release();

    normalBuffer.create();
    normalBuffer.bind();
    normalBuffer.allocate(normalArray.constData(), normalArray.size() * sizeof(QVector3D));
    normalBuffer.release();

    indicesBuffer.create();
    indicesBuffer.bind();
    indicesBuffer.allocate(indices.constData(), indices.size() * sizeof(GLuint) );
    indicesBuffer.release();

    qDebug() << filename << " read succefully";

    return true;
}

bool myMesh::readFar(QString filename){

    verticesArray.clear();
    normalArray.clear();
    uvsArray.clear();
    indices.clear();

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"Error";return false;
    }
    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList str = line.split(' ');
        int n = str.length();
        if (str[n-1].length() == 0) n--;

        if (str.at(0) == "v"){
            verticesArray.push_back(QVector3D(str.at(1).toDouble(), str.at(2).toDouble(), str.at(3).toDouble()));

        }
        else if (str.at(0) == "u"){
            uvsArray.push_back(QVector2D(str.at(1).toDouble(), str.at(2).toDouble()));
        }
        else if (str.at(0) == "n"){
            normalArray.push_back(QVector3D(str.at(1).toDouble(), str.at(2).toDouble(), str.at(3).toDouble()));
        }
        else if (str.at(0) == "i"){
            indices.push_back(str.at(1).toInt());
        }
    }
    file.close();


    verticesBuffer.create();
    verticesBuffer.bind();
    verticesBuffer.allocate(verticesArray.constData(), verticesArray.size() * sizeof(QVector3D) );
    verticesBuffer.release();

    uvsBuffer.create();
    uvsBuffer.bind();
    uvsBuffer.allocate(uvsArray.constData(), uvsArray.size() * sizeof(QVector2D));
    uvsBuffer.release();

    normalBuffer.create();
    normalBuffer.bind();
    normalBuffer.allocate(normalArray.constData(), normalArray.size() * sizeof(QVector3D));
    normalBuffer.release();

    indicesBuffer.create();
    indicesBuffer.bind();
    indicesBuffer.allocate(indices.constData(), indices.size() * sizeof(GLuint) );
    indicesBuffer.release();

    qDebug() << filename << " read succefully";

    return true;

}

int myMesh::getSimilarVertexIndex(QVector3D vertIn, QVector3D normalIn, QVector2D uvIn, QVector<QVector3D> vArray, QVector<QVector3D> nArray, QVector<QVector2D> uvArray ){
    // Algorithm of Lame linear search
    for (int i = 0; i < vArray.size(); i++){
        if ( is_near(vertIn.x(), vArray[i].x()) &&
             is_near(vertIn.y(), vArray[i].y()) &&
             is_near(vertIn.z(), vArray[i].z()) &&
             is_near(uvIn.x(), uvArray[i].x()) &&
             is_near(uvIn.y(), uvArray[i].y()) &&
             is_near(normalIn.x(), nArray[i].x()) &&
             is_near(normalIn.y(), nArray[i].y()) &&
             is_near(normalIn.z(), nArray[i].z())
             ){
            return i;
        }
    }

    return -1;
}



bool myMesh::is_near(float v1, float v2){
    return qAbs(v1-v2)<0.001f;
}


void myMesh::addShader(QString vertfile, QString fragFile, int quality){
    ShaderGL* newShad  = new ShaderGL(vertfile, fragFile);
    newShad->init();
    shadersHash.insert(quality, newShad);
}


void myMesh::initShader(){
    currShader->init();
}



void myMesh::setCurrShader(int quality){
    if (NULL != currShader)
        currShader->release();
    if(shadersHash.contains(quality)){
        currShader = shadersHash.value(quality);
    }
}


// Getter and Setter
void myMesh::setPosition(double x, double y, double z){
    this->position->setX(x);
    this->position->setY(y);
    this->position->setZ(z);

}

void myMesh::setPosition(QVector3D position){
    this->position->setX(position.x());
    this->position->setY(position.y());
    this->position->setZ( position.z());

}

QVector3D *myMesh::getPosition(){
    return this->position;
}

void myMesh::setScale(double x, double y, double z, double w){
    this->scale->setX(this->scale->x()* x);
    this->scale->setY(this->scale->y()* y);
    this->scale->setZ(this->scale->z()* z);
    this->scale->setW(this->scale->w()* w);
    QVector<QVector3D> verticesArrayTmp;
    foreach(QVector3D v , verticesArray){
        QVector3D vtmp;
        vtmp.setX(v.x() * x);
        vtmp.setY(v.y() * y);
        vtmp.setZ(v.z() * z);
        verticesArrayTmp.push_back(vtmp);
    }
    verticesArray = verticesArrayTmp;

    verticesBuffer.create();
    verticesBuffer.bind();
    verticesBuffer.allocate(verticesArray.constData(), verticesArray.size() * sizeof(QVector3D) );
    verticesBuffer.release();


}


QVector4D *myMesh::getScale(){
    return this->scale;
}

QVector4D myMesh::getQtScale(){
    QVector4D s;
    s.setX(scale->x());
    s.setY(scale->y());
    s.setZ(scale->z());
    s.setW(scale->w());
    return s;
}

//This function is use to draw the object in OpenGL. It's been called by the root objet or the GLWidget

int myMesh::drawObject(CameraGL *camera, LightGL* lightList, QMatrix4x4 projection, QMatrix4x4 view, QMatrix4x4 model,  QVector3D position){
    if (this->visible){ // we draw it onlu if he is still visible
            QGLFunctions glFuncs(QGLContext::currentContext());


            this->currShader->bind();
         //   lightShader(lightList);

            this->currShader->setUniformValue("uCameraPosition", camera->getQtPositionEye());

            // For the material settings
            if(NULL != this->mat){
                this->currShader->setUniformValue("uEmissive", this->mat->getQtEmission());
                this->currShader->setUniformValue("uAmbient", this->mat->getQtAmbient());
                this->currShader->setUniformValue("uDiffuse", this->mat->getQtDiffuse());
                this->currShader->setUniformValue("uSpecular", this->mat->getQtSpecular());
                this->currShader->setUniformValue("uGloss", this->mat->getGloss());
            }
                model.translate(this->getPosition()->x() + position.x(),  this->getPosition()->y() + position.y() , this->getPosition()->z() + position.z());
                currShader->setUniformValue("projection", projection );
                currShader->setUniformValue("model", model );
                currShader->setUniformValue("view", view );
                currShader->setUniformValue("inversedView", view.inverted());

                verticesBuffer.bind();
                verticesBuffer.size();
                currShader->setAttributeBuffer("aPosition", GL_FLOAT, 0, 3);
                verticesBuffer.release();

                uvsBuffer.bind();
                currShader->setAttributeBuffer("aTexture", GL_FLOAT, 0, 2);
                uvsBuffer.release();

                normalBuffer.bind();
                currShader->setAttributeBuffer("aNormal", GL_FLOAT, 0, 3);
                normalBuffer.release();

                indicesBuffer.bind();
                currShader->enableAttributeArray("aPosition");
                currShader->enableAttributeArray("aTexture");
                currShader->enableAttributeArray("aNormal");
                glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT,  0);
                currShader->disableAttributeArray("aPosition");
                currShader->disableAttributeArray("aTexture");
                currShader->disableAttributeArray("aNormal");
                indicesBuffer.release();


            this->currShader->release();
        return 1;
    }
    return -1;
}


// This is sue to provide light information to GLSL
void myMesh::lightShader(LightGL *light){
    QVector4D light_position;

    QVector4D LightPositionLocale;
    LightPositionLocale.setX(light->getQtPosition().x() - this->getPosition()->x());
    LightPositionLocale.setY(light->getQtPosition().y() - this->getPosition()->y());
    LightPositionLocale.setZ(light->getQtPosition().z() - this->getPosition()->z());
    light_position = LightPositionLocale;

    this->currShader->setUniformValue("light_position_array", light_position);
    this->currShader->setUniformValue("light_ambient_array",  light->getQtAmbient());
    this->currShader->setUniformValue("light_diffuse_array", light->getQtDiffuse());
    this->currShader->setUniformValue("light_specular_array", light->getQtSpecular());
    this->currShader->setUniformValue("light_constantAttenuation_array", light->getConstantAttenuation());
    this->currShader->setUniformValue("light_linearAttenuation_array", light->getLinearAttenuation());
    this->currShader->setUniformValue("light_quadraticAttenuation_array", light->getQuadraticAttenuation());
    this->currShader->setUniformValue("light_spotDirection_array", light->getQtDirection());

}

// Compute the Mesh rotation for angle X along X axis, angle Y along Y axis, angle Z along Z axis, with each angle in degree
void myMesh::computeRotation(float angleX, float angleY, float angleZ)
       {
    QVector<QVector3D> verticesArrayTmp;
    QVector3D vertTmp;
         foreach (QVector3D vert , verticesArray){

                // X rotation
               double a = 0, b = 0, c = 0,
                       x = vert.x(), y = vert.y(), z = vert.z(),
                       u = 1, v = 0, w = 0;
               double cosTheta = qCos(radians(angleX)), sinTheta = qSin(radians(angleX));


               vertTmp.setX((a * (v * v + w * w) - u * (b * v + c * w - u * x - v * y - w * z)) * (1 - cosTheta) + x * cosTheta + (-c * v + b * w - w * y + v * z) * sinTheta);
               vertTmp.setY( (b * (u * u + w * w) - v * (a * u + c * w - u * x - v * y - w * z)) * (1 - cosTheta) + y * cosTheta + (c * u - a * w + w * x - u * z) * sinTheta);
               vertTmp.setZ((c * (u * u + v * v) - w * (a * u + b * v - u * x - v * y - w * z)) * (1 - cosTheta) + z * cosTheta + (-b * u + a * v - v * x + u * y) * sinTheta);

                // Y Rotation
                x = vertTmp.x(), y = vertTmp.y(), z = vertTmp.z(),                u = 0; v = 1; w = 0;
               cosTheta = qCos(radians(angleY));
               sinTheta = qSin(radians(angleY));

               vertTmp.setX((a * (v * v + w * w) - u * (b * v + c * w - u * x - v * y - w * z)) * (1 - cosTheta) + x * cosTheta + (-c * v + b * w - w * y + v * z) * sinTheta);
               vertTmp.setY( (b * (u * u + w * w) - v * (a * u + c * w - u * x - v * y - w * z)) * (1 - cosTheta) + y * cosTheta + (c * u - a * w + w * x - u * z) * sinTheta);
               vertTmp.setZ((c * (u * u + v * v) - w * (a * u + b * v - u * x - v * y - w * z)) * (1 - cosTheta) + z * cosTheta + (-b * u + a * v - v * x + u * y) * sinTheta);

                //Z Rotation
               x = vertTmp.x(), y = vertTmp.y(), z = vertTmp.z(),
               u = 0; v = 0; w = 1;
              cosTheta = qCos(radians(angleZ));
              sinTheta = qSin(radians(angleZ));

              vertTmp.setX((a * (v * v + w * w) - u * (b * v + c * w - u * x - v * y - w * z)) * (1 - cosTheta) + x * cosTheta + (-c * v + b * w - w * y + v * z) * sinTheta);
              vertTmp.setY( (b * (u * u + w * w) - v * (a * u + c * w - u * x - v * y - w * z)) * (1 - cosTheta) + y * cosTheta + (c * u - a * w + w * x - u * z) * sinTheta);
              vertTmp.setZ((c * (u * u + v * v) - w * (a * u + b * v - u * x - v * y - w * z)) * (1 - cosTheta) + z * cosTheta + (-b * u + a * v - v * x + u * y) * sinTheta);
              verticesArrayTmp.push_back(vertTmp);
         }

         QVector<QVector3D> normalArrayTmp;
         QVector3D normalTemp;
         foreach (QVector3D vert , normalArray){

                // X rotation
               double a = 0, b = 0, c = 0,
                       x = vert.x(), y = vert.y(), z = vert.z(),
                       u = 1, v = 0, w = 0;
               double cosTheta = qCos(radians(angleX)), sinTheta = qSin(radians(angleX));


               normalTemp.setX((a * (v * v + w * w) - u * (b * v + c * w - u * x - v * y - w * z)) * (1 - cosTheta) + x * cosTheta + (-c * v + b * w - w * y + v * z) * sinTheta);
               normalTemp.setY( (b * (u * u + w * w) - v * (a * u + c * w - u * x - v * y - w * z)) * (1 - cosTheta) + y * cosTheta + (c * u - a * w + w * x - u * z) * sinTheta);
               normalTemp.setZ((c * (u * u + v * v) - w * (a * u + b * v - u * x - v * y - w * z)) * (1 - cosTheta) + z * cosTheta + (-b * u + a * v - v * x + u * y) * sinTheta);

                // Y Rotation
                x = normalTemp.x(), y = normalTemp.y(), z = normalTemp.z(),                u = 0; v = 1; w = 0;
               cosTheta = qCos(radians(angleY));
               sinTheta = qSin(radians(angleY));

               normalTemp.setX((a * (v * v + w * w) - u * (b * v + c * w - u * x - v * y - w * z)) * (1 - cosTheta) + x * cosTheta + (-c * v + b * w - w * y + v * z) * sinTheta);
               normalTemp.setY( (b * (u * u + w * w) - v * (a * u + c * w - u * x - v * y - w * z)) * (1 - cosTheta) + y * cosTheta + (c * u - a * w + w * x - u * z) * sinTheta);
               normalTemp.setZ((c * (u * u + v * v) - w * (a * u + b * v - u * x - v * y - w * z)) * (1 - cosTheta) + z * cosTheta + (-b * u + a * v - v * x + u * y) * sinTheta);

                //Z Rotation
               x = normalTemp.x(), y = normalTemp.y(), z = normalTemp.z(),
               u = 0; v = 0; w = 1;
              cosTheta = qCos(radians(angleZ));
              sinTheta = qSin(radians(angleZ));

              normalTemp.setX((a * (v * v + w * w) - u * (b * v + c * w - u * x - v * y - w * z)) * (1 - cosTheta) + x * cosTheta + (-c * v + b * w - w * y + v * z) * sinTheta);
              normalTemp.setY( (b * (u * u + w * w) - v * (a * u + c * w - u * x - v * y - w * z)) * (1 - cosTheta) + y * cosTheta + (c * u - a * w + w * x - u * z) * sinTheta);
              normalTemp.setZ((c * (u * u + v * v) - w * (a * u + b * v - u * x - v * y - w * z)) * (1 - cosTheta) + z * cosTheta + (-b * u + a * v - v * x + u * y) * sinTheta);
              normalArrayTmp.push_back(normalTemp);
        }

         verticesArray = verticesArrayTmp;
         normalArray = normalArrayTmp;


         verticesBuffer.create();
         verticesBuffer.bind();
         verticesBuffer.allocate(verticesArray.constData(), verticesArray.size() * sizeof(QVector3D) );
         verticesBuffer.release();

         normalBuffer.create();
         normalBuffer.bind();
         normalBuffer.allocate(normalArray.constData(), normalArray.size() * sizeof(QVector3D) );
         normalBuffer.release();
}

void myMesh::moveObjectTo(QVector3D position, int time){

    this->moveObject.MoveObjectTo(QVector3D(this->getPosition()->x(), this->getPosition()->y(), this->getPosition()->z()),position, time, Function::Linear);
}

void myMesh::rotateObjectTo(double angleX, double angleY, double angleZ, int time){

    this->moveObject.RotateObjectTo(angleX, angleY, angleZ, time, Function::Linear);
}

QString myMesh::exportFar(){

        QString str;
        foreach (QVector3D v, verticesArray) {
            str += "v " + QString::number(v.x()) + " " +  QString::number(v.y()) + " " +  QString::number(v.z());
        }
        foreach (QVector2D v, uvsArray) {
            str += "u "+ QString::number(v.x()) + " " + QString::number(v.y());
        }
        foreach (QVector3D v, normalArray) {
            str += "n "+ QString::number(v.x()) + " " + QString::number(v.y()) + " " + QString::number(v.z());
        }
        foreach (int i, indices) {
            str += "i "+ QString::number(i);
        }
}
