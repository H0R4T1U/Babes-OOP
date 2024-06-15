#include <QApplication>
#include <QPushButton>
#include "Tractor.h"
#include "Repository.h"
#include "Service.h"
#include "Gui.h"

int main(int argc, char *argv[]) {
    testDomain();
    testRepo();
    testService();

    Repository repo{"../repo.txt"};
    repo.load();
    Service service{repo};
    QApplication a(argc, argv);
    Gui gui{service};
    gui.show();
    return QApplication::exec();
}
