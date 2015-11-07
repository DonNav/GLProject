#include "myTexture.h"


static int qt_next_power_of_two(int v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    ++v;
    return v;
}

static inline void qgl_byteSwapImage(QImage &img, GLenum pixel_type)
{
    const int width = img.width();
    const int height = img.height();

    if (pixel_type == GL_UNSIGNED_BYTE && QSysInfo::ByteOrder == QSysInfo::LittleEndian)
    {
        for (int i = 0; i < height; ++i) {
            uint *p = (uint *) img.scanLine(i);
            for (int x = 0; x < width; ++x)
                p[x] = ((p[x] << 16) & 0xff0000) | ((p[x] >> 16) & 0xff) | (p[x] & 0xff00ff00);
        }
    } else {
        for (int i = 0; i < height; ++i) {
            uint *p = (uint *) img.scanLine(i);
            for (int x = 0; x < width; ++x)
                p[x] = (p[x] << 8) | ((p[x] >> 24) & 0xff);
        }
    }
}


MyTexture::MyTexture(QObject *parent) :
    QObject(parent)
{
    this->isTexture = false;
}

void MyTexture::setImage(QString filename){
    this->isTexture = true;
    if(!image.load(filename)){
        qWarning("Error loading image");this->isTexture = false;
        this->isTexture = false;
        return;
    }

    glEnable(GL_TEXTURE_2D);

    int tx_w = qt_next_power_of_two(image.width());
    int tx_h = qt_next_power_of_two(image.height());
    image = image.scaled(tx_w, tx_h);


    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    QImage::Format target_format = image.format();
     GLenum externalFormat;
     GLuint internalFormat = 3;
     GLuint pixel_type;

     externalFormat = GL_RGBA;
     pixel_type = GL_UNSIGNED_BYTE;


     switch (target_format) {
     case QImage::Format_ARGB32:
             image = image.convertToFormat(target_format = QImage::Format_ARGB32);
         break;
     case QImage::Format_RGB16:
         pixel_type = GL_UNSIGNED_SHORT_5_6_5;
         externalFormat = GL_RGB;
         internalFormat = GL_RGB;
         break;
     case QImage::Format_RGB32:
         break;
     default:
             image = image.convertToFormat(QImage::Format_RGB32);
     }

     if (externalFormat == GL_RGBA) {
         // The only case where we end up with a depth different from
         // 32 in the switch above is for the RGB16 case, where we set
         // the format to GL_RGB
         Q_ASSERT(image.depth() == 32);
         qgl_byteSwapImage(image, pixel_type);
     }
 #ifdef QT_OPENGL_ES
     // OpenGL/ES requires that the internal and external formats be
     // identical.
     internalFormat = externalFormat;
 #endif

     const QImage &constRef = image; // to avoid detach in bits()...

     glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, image.width(), image.height(), 0, externalFormat,
                  pixel_type, constRef.bits());


}

void MyTexture::setImage(QImage imageTmp){
    this->isTexture = true;
    image = imageTmp;

    glEnable(GL_TEXTURE_2D);

    int tx_w = qt_next_power_of_two(image.width());
    int tx_h = qt_next_power_of_two(image.height());
    image = image.scaled(tx_w, tx_h);

    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    QImage::Format target_format = image.format();
     GLenum externalFormat;
     GLuint internalFormat = 3;
     GLuint pixel_type;

     externalFormat = GL_RGBA;
     pixel_type = GL_UNSIGNED_BYTE;


     switch (target_format) {
     case QImage::Format_ARGB32:
             image = image.convertToFormat(target_format = QImage::Format_ARGB32);
         break;
     case QImage::Format_RGB16:
         pixel_type = GL_UNSIGNED_SHORT_5_6_5;
         externalFormat = GL_RGB;
         internalFormat = GL_RGB;
         break;
     case QImage::Format_RGB32:
         break;
     default:
             image = image.convertToFormat(QImage::Format_RGB32);
     }

     if (externalFormat == GL_RGBA) {
         // The only case where we end up with a depth different from
         // 32 in the switch above is for the RGB16 case, where we set
         // the format to GL_RGB
         Q_ASSERT(image.depth() == 32);
         qgl_byteSwapImage(image, pixel_type);
     }
 #ifdef QT_OPENGL_ES
     // OpenGL/ES requires that the internal and external formats be
     // identical.
     internalFormat = externalFormat;
 #endif

     const QImage &constRef = image; // to avoid detach in bits()...

     glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, image.width(), image.height(), 0, externalFormat,
                  pixel_type, constRef.bits());

}

GLuint MyTexture::getTexture(){
   return texture;
}

