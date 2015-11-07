#include "shadergl.h"




ShaderGL::ShaderGL(QString vertexSource, QString fragmentSource): QGLShaderProgram() {
    this->m_vertexSource = vertexSource;
    this->m_fragmentSource = fragmentSource;
    this->m_init = 0;
}

ShaderGL::ShaderGL(ShaderGL const &shader): QGLShaderProgram(){
    this->m_vertexSource = shader.m_vertexSource;
    this->m_fragmentSource = shader.m_fragmentSource;
    this->m_init = shader.m_init;
    if (m_init) this->init();
}

ShaderGL::~ShaderGL(){
}


bool ShaderGL::init(){

    if(!this->addShaderFromSourceFile(QGLShader::Vertex, m_vertexSource)) {
        qDebug() << "error during compiling vertex source : " << m_vertexSource;
        return false;
    }

    if (!(this->addShaderFromSourceFile(QGLShader::Fragment, m_fragmentSource))){
        qDebug() << "error during compiling fragment source : " << m_fragmentSource;
        return false;
    }
    if (!this->link()){
        qDebug() << "Error during linking shaders";
        return false;
    }
//    if (!this->bind()){
//        qDebug() << "Error during the bingind...That's not usual...";
//        return false;
//    }
    return true;

}



ShaderGL& ShaderGL::operator=(ShaderGL const &shader){
    if (this != &shader){
        this->m_vertexSource = shader.m_vertexSource;
        this->m_fragmentSource = shader.m_fragmentSource;
        m_init = shader.m_init;

        init();
    }

}



