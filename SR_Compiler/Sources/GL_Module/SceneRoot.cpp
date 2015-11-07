#include "SceneRoot.h"

Scene_Root_Class::Scene_Root_Class(QObject *parent) :
    QObject(parent)
{

        camera = new CameraGL();
        camera->setDistance(16.0);
        camera->setFOV(32.0);
        camera->setXRotation(5);


        fog = NULL;
        backgroundColor = new QVector4D(0.3,0.3,0.3,1.0);


       // Lights
        light = new LightGL();
        light->setPosition(0.0,10,5.0,1);
        light->setAmbient(1.0,1.0,1.0, 1.0);
        light->setDiffuse(1.0,1.0,1.0, 1.0);
        light->setSpecular(1.0,1.0,1.0, 1.0);
        light->setConstantAttenuation(0.00f);
        light->setLinearAttenuation(0.055f);
        light->setQuadraticAttenuation(0.009f);
        light->setPointLight(true);


        mSkyBox = NULL;


        mMaterial = new myMaterial();
        mMaterial->setAmbient(0.0,0.0,0.0,1.0);
        mMaterial->setDiffuse(0.0015,0.0015,0.0015,1.0);
        mMaterial->setSpecular(0.605,0.608,0.605,1.0);
        mMaterial->setGloss(50);
}


int Scene_Root_Class::draw(CameraGL* camera, QMatrix4x4 projection, QMatrix4x4 view, QMatrix4x4 model){
    int s = 0;

    foreach( myMesh* mesh, objectList)
        s += mesh->drawObject(camera, light, projection   , view  , model , QVector3D(0,0,0));

/*    foreach( Root_Object* root, rootList)
        s += root->draw(camera, light, projection   , view  , model);
*/
    return s;
}



void  Scene_Root_Class::reset(){
    rootList.clear();
    objectList.clear();
}

void  Scene_Root_Class::addObject(QString path){
    myMesh* mNewMesh = new myMesh();
    if (path.contains(".obj",Qt::CaseSensitive))
        mNewMesh->read(path);
    else if(path.contains(".far",Qt::CaseSensitive))
        mNewMesh->readFar(path);
    else if(path.contains(".dna",Qt::CaseSensitive))
        mNewMesh->readFar(path);
    else
        return;
    mNewMesh->addShader("://Graphics/Standard/Shaders/PerPixelLighting/ppL.vert","://Graphics/Standard/Shaders/PerPixelLighting/ppL.frag",0);
    mNewMesh->setCurrShader(0);
    mNewMesh->mat = mMaterial;
    objectList.append(mNewMesh);
}

void  Scene_Root_Class::export3d(QString path){

    QString filename = path +".dna";
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
         foreach( myMesh* mesh, objectList)
             stream << mesh->exportFar() << endl;
    }
}



