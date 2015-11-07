#include <QApplication> // Mise en place d'une application par evenenement
#include <QDir>         // Directory management

#include "Manager.h"

int main(int argc, char *argv[])
{
    // Create the Application object and event management
    QApplication Application(argc, argv);
    QDir::setCurrent(Application.applicationDirPath());

    // Creating Object for Generic Configuration and Management for the application and plateform interaction
    Manager_Class Manager(Application.arguments());
    if (!Manager.isValid)
    {
        std::cout << "Widget failed to start." << std::endl;
        return 1;
    }

    // Entering Application event catching loop
    return Application.exec();
}
