#include <QApplication>
#include "Melodie.h"
#include "Repository.h"
#include "Service.h"
#include "Gui.h"

int main(int argc, char *argv[]) {
    // teste
    testDomain();
    testRepository();
    testService();

    QApplication a(argc, argv);
    // initializam program
    Repository repo{"../date.txt"};
    repo.load();
    Service service{repo};
    Gui gui{service};
    // afisam gui
    gui.show();
    return QApplication::exec();
}


