#ifndef QML_Image_Header
#define QML_Image_Header

#include <iostream>

#include <QGraphicsObject>
#include <QDeclarativeItem>
#include <QPainter>
#include <QImage>

class QML_ImageProvider: public QDeclarativeItem
{ Q_OBJECT

public:
    explicit QML_ImageProvider(QDeclarativeItem *parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void updateImage(QImage SharedImage);

private:
    QImage StoredImage;

};
QML_DECLARE_TYPE(QML_ImageProvider)

#endif
