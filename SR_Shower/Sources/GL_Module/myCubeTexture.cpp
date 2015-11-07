#include "myCubeTexture.h"


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

MyCubeTexture::MyCubeTexture(QObject *parent) :
    QObject(parent)
{
    this->isTexture = false;
}

void MyCubeTexture::setImage(QString directory){

    glEnable(GL_TEXTURE_CUBE_MAP);
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);

    QString location;
    GLenum type;
    QImage image;
    for (int i =0; i < 6; i++){
        if (i==0){
            location = directory+"/posY.png";
            type = GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
        }
        else if (i==1){
            location = directory+"/posX.png";
            type = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
        }
        else if (i==2){
            location = directory+"/posZ.png";
            type = GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
        }
        else if (i==3){
            location = directory+"/negY.png";
            type = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
        }
        else if (i==4){
            location = directory+"/negX.png";
            type = GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
        }
        else if (i==5){
            location = directory+"/negZ.png";
            type = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
        }
        else return;

        if(!image.load(location)){
            qWarning("Error loading image ");
            this->isTexture = false;
            return;
        }
        int tx_w = qt_next_power_of_two(image.width());
        int tx_h = qt_next_power_of_two(image.height());
        image = image.scaled(tx_w, tx_h);


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

        glTexImage2D(type, 0, internalFormat, image.width(), image.height(), 0, externalFormat, pixel_type, constRef.bits());
    }



    this->isTexture = true;
}
