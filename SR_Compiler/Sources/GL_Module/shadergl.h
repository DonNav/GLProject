#ifndef SHADERGL_H
#define SHADERGL_H


#include <QGLWidget>
#include <QGLShaderProgram>
#include <QtOpenGL>
#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class ShaderGL : public QGLShaderProgram
{
    Q_OBJECT
public:
    ShaderGL(QString vertexSource, QString fragmentSource);
    ShaderGL(ShaderGL const &shader);
    ~ShaderGL();
    bool init();
    ShaderGL& operator=(ShaderGL const &shader);
  //  void setUniform(QString paramName, const <T> value);
signals:
    
public slots:

private:

    QString m_vertexSource;
    QString m_fragmentSource;

    bool m_init;

    
};

#endif // SHADERGL_H
