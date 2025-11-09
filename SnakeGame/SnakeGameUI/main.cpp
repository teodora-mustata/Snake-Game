

#include <QApplication>
#include "MainWindow.h"
#include "GameFactory.h"  

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    IGameAPI* api = createGameAPI();   
    MainWindow window(api);
    window.show();

    return app.exec();
}
