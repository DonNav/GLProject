#include "GlWidget.h"

static double radians( double degrees ){
    return ( M_PI*degrees ) / 180;
}

static double degree( double radians ){
    return ( 180*radians ) / M_PI;
}


GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent), tRender(new QBasicTimer)
{
    this->setWindowFlags(Qt::FramelessWindowHint);// Set Windows to Borderless

    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_NoSystemBackground);
    setAutoBufferSwap(false);

    #ifndef Q_WS_QWS
        setMinimumSize(300, 250);
    #endif

    camera = new CameraGL();
    this->scene = NULL;

    this->m_render_offscreen = NULL;

    this->render_shader = NULL;

    this->tFPS = new QTime();

    count = 0;
    hasChanged = true;
}

void GLWidget::setScene(Scene_Root_Class* sc) {
    this->scene = sc;
    this->camera = scene->camera;
 }

void GLWidget::initializeGL() {
    initializeGLFunctions();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);
    glDepthFunc(GL_LEQUAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    tFPS->start();
    tRender->start(32, this); // 16 is for 60FPS, 32 for 30FPS

}


void GLWidget::timerEvent(QTimerEvent *e){
    Q_UNUSED(e);
    updateGL();
}

void GLWidget::paintGL() {
    QPainter painter;
    painter.begin(this);

    painter.beginNativePainting();
    if (this->scene != NULL){
               direct_render();

    }
    painter.endNativePainting();


    painter.setPen(Qt::white);

    int fps = tFPS->restart();

    if(NULL != this->camera){
        this->camera->setYRotation(this->camera->getYRot() + (float)fps/60.0);
    }

    painter.drawText(20, 40, QString::number(1000/fps) + " fps");

    painter.end();

   swapBuffers();


}


void GLWidget::direct_render(){
    if (hasChanged){
        render_OffScreen();
        hasChanged = false;
    }
    renderGL();
}

void GLWidget::render_OffScreen(){
    if ( NULL == m_render_offscreen) {
        m_render_offscreen =  new QGLFramebufferObject(this->Width, this->Height,QGLFramebufferObject::Depth, GL_TEXTURE_2D);
    }
    if (!m_render_offscreen->isValid()) qDebug() << "fbo m_render_offscreen  isn't valid";
    if (!m_render_offscreen->bind()) qDebug() << "fbo m_render_offscreen is not bind";

    if (NULL!= scene &&  NULL!=this->scene->getBacgroundColor()){
        glClearColor(this->scene->getBacgroundColor()->x(), this->scene->getBacgroundColor()->y(), this->scene->getBacgroundColor()->z(), this->scene->getBacgroundColor()->w() );
    }
    else
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    QMatrix4x4 projection;
    projection.perspective(camera->getFOV(), 1.0 * width() / height(), camera->getNearPlane(), camera->getFarPlane());

    QMatrix4x4 model;
    model.rotate(camera->getXRot() , 1.0, 0.0, 0.0);
    model.rotate(camera->getYRot() , 0.0,-1.0, 0.0);

    QMatrix4x4 view;
    view.translate(0.0, 0.0, -camera->getDistance());

    if (NULL != this->scene){
         scene->draw(camera, projection   , view  , model);
     }



    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glFlush();

    m_render_offscreen->release();

}


void GLWidget::renderGL(){
    if (NULL != this->scene){
        if (NULL == render_shader){
            this->render_shader = new ShaderGL("://Graphics/Standard/Shaders/RenduShader/rendu.vert","://Graphics/Standard/Shaders/RenduShader/rendu.frag");
            this->render_shader->init();
        }

        if (NULL!=this->scene->getBacgroundColor()){
            glClearColor(this->scene->getBacgroundColor()->x(), this->scene->getBacgroundColor()->y(), this->scene->getBacgroundColor()->z(), this->scene->getBacgroundColor()->w() );
        }
        else
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);

        this->render_shader->bind();
        if (NULL != m_render_offscreen){
            glActiveTexture(GL_TEXTURE9);
            glBindTexture(GL_TEXTURE_2D, this->m_render_offscreen->texture());
            this->render_shader->setUniformValue("sample_Texture", 9);
        }

        GLfloat afVertices[] = {
            1,1, 0,
             -1,1, 0,
             -1,-1, 0,

            -1,-1, 0,
            1, -1, 0,
             1,1, 0

        };

        GLfloat afTexCoord[] = {
            1,1,
            0,1,
            0,0,



            0,0,
            1,0,
            1,1

          };

        GLfloat afNormals[] = {

            0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0
        };


        render_shader->setAttributeArray("aTexture", afTexCoord, 2);
        render_shader->setAttributeArray("aPosition", afVertices, 3);
        render_shader->setAttributeArray("aNormal", afNormals, 3);

        render_shader->enableAttributeArray("aPosition");
        render_shader->enableAttributeArray("aTexture");
        render_shader->enableAttributeArray("aNormal");
        glDrawArrays(GL_TRIANGLES, 0, 6);
        render_shader->disableAttributeArray("aPosition");
        render_shader->disableAttributeArray("aTexture");
        render_shader->disableAttributeArray("aNormal");

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);

        glFlush();

        this->render_shader->release();

    }



}

void GLWidget::resizeGL(int width, int height)
{
    if(height == 0)
        height = 1;
    Width = width; Height = height;
    this->setMinimumSize(Width, Height);


    if (NULL != m_render_offscreen) m_render_offscreen = new QGLFramebufferObject(this->Width, this->Height,QGLFramebufferObject::Depth, GL_TEXTURE_2D);

}



void GLWidget::mousePressEvent(QMouseEvent *event) {
    lastPos = event->pos();
}
void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    camera->setXRotation(camera->getXRot() + dy);
    camera->setYRotation(camera->getYRot() + dx);
    this->worldHasChanged();
    lastPos = event->pos();

}

void GLWidget::keyPressEvent(QKeyEvent *event){
   if(event->key() == Qt::Key_Escape)
        close();
}
void GLWidget::wheelEvent ( QWheelEvent * event ){
    this->camera->zooming(event->delta()/60);
    this->worldHasChanged();

}


// ######################################################################
void GLWidget::setSize(QSize Widget_Size)
{
    Width = Widget_Size.width();
    Height = Widget_Size.height();
    this->resize(Width, Height);
    this->setFixedSize(Width, Height);
    this->resizeGL(Width, Height);
    this->worldHasChanged();
}
// ######################################################################
void GLWidget::setPosition(QPoint Widget_Position)
{
    Stored_Position = Widget_Position;
    this->move(Widget_Position);
}
// ######################################################################
void GLWidget::setMode(QString Widget_Mode)
{
    Stored_Mode = Widget_Mode;
}
// ######################################################################
void GLWidget::setShow(bool Widget_Status)
{
    if (Widget_Status == false)
    {
        this->hide();
        return;
    }
    this->show();
}
// ######################################################################
