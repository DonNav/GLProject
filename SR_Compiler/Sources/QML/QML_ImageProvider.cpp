#include "QML_ImageProvider.h"
QML_ImageProvider::QML_ImageProvider(QDeclarativeItem *parent )
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
   // StoredImage = new QImage();
    StoredImage.fill("Black");
}

void QML_ImageProvider::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (StoredImage.isNull()) return;
   // std::cout << "Image[" << StoredImage->width() << "," << StoredImage->height() << "]" << std::flush;
    painter->drawImage(QPoint(0,0), StoredImage);
}
void QML_ImageProvider::updateImage(QImage SharedImage)
{
    StoredImage = SharedImage;
    this->update();
}
