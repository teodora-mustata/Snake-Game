#include "GameInterface.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GameInterface window;
    window.show();
    return app.exec();
}
