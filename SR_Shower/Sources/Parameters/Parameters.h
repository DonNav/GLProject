#ifndef Parameters_Header
#define Parameters_Header

#include <iostream>
#include <QObject>
#include <QVariant>
#include <QStringList>

class Parameters_Class : public QObject
{
    Q_OBJECT

public:
    explicit Parameters_Class(QStringList Commands = QStringList());

    bool value(QString Keyword , bool Fallback);
    int value(QString Keyword , int Fallback);
    double value(QString Keyword , double Fallback);
    QString value(QString Keyword , QString Fallback);
    QString value(QString Keyword , char* Fallback){ return value(Keyword , (QString) Fallback);}
private:
    bool isSet(QString Keyword, bool Type = false);
    QStringList Settings;
    QVariant Parameter;
 };

#endif
