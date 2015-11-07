#include "Parameters.h"
// ####################################################################################################################
Parameters_Class::Parameters_Class(QStringList Commands)
{   Settings = Commands;  }
// ####################################################################################################################
bool Parameters_Class::value(QString Keyword , bool Fallback  )
{
    if (this->isSet(Keyword, true)) return Parameter.toBool();
    else
    {
        std::cout << " Builtin is [" << Fallback << "]." \
                  << " Set it using --"<<  Keyword.toLatin1().data()<< " keyword." \
                  << std::endl;
        return Fallback;
    }
}
// ####################################################################################################################
QString Parameters_Class::value(QString Keyword , QString Fallback  )
{
    if (this->isSet(Keyword)) return Parameter.toString();
    else
    {
        std::cout << " Builtin is [" << Fallback.toLatin1().data() << "]." \
                  << " Set it using --"<<  Keyword.toLatin1().data()<< " keyword." \
                  << std::endl;
        return Fallback;
    }
}
// ####################################################################################################################
int Parameters_Class::value(QString Keyword , int Fallback )
{
    if (this->isSet(Keyword)) return Parameter.toInt();
    else
    {
        std::cout << " Builtin is [" << Fallback << "]." \
                  << " Set it using --"<<  Keyword.toLatin1().data()<< " keyword." \
                  << std::endl;
        return Fallback;
    }
}
// ####################################################################################################################
double Parameters_Class::value(QString Keyword , double Fallback)
{
    if (this->isSet(Keyword)) return Parameter.toDouble();
    else
    {
        std::cout << " Builtin is [" << Fallback << "]." \
                  << " Set it using --"<<  Keyword.toLatin1().data()<< " keyword." \
                  << std::endl;
        return Fallback;
    }
}
// ####################################################################################################################
bool Parameters_Class::isSet(QString Keyword, bool Type)
{
    int Index = Settings.indexOf("--"+Keyword);// Searching for Keyword ?
    if  (Index == -1) // Keyword is not found
    {
        std::cout << "{" << Keyword.toLatin1().data() << "} is not set.";
        return false;
    }
    else // Keyword is provided
    {
        if (Type) return true;

        int Nb = Settings.count();
        if (Index == (Nb-1))
        {
            std::cout << "{" << Keyword.toLatin1().data() << "} should be followed by a value.";
            return false;
        }

        QString Value = Settings.at(Index+1);
        if (Value.indexOf("--")!= -1 ) // Next is Keyword ==> Should be a value
        {
            std::cout << "{" << Keyword.toLatin1().data() << "} should be followed by a value.";
            return false;
        }
        Parameter = QVariant(Value);
        return true;
    }
}
// ####################################################################################################################
