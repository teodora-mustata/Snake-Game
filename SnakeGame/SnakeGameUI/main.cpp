#include "SnakeGameUI.h"
#include <QtWidgets/QApplication>
#include "ISubjectMap.h"
#include "IObserverMap.h"
#include "GameController.h"
#include "Map.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SnakeGameUI window;
    window.show();
    return app.exec();
    
}
