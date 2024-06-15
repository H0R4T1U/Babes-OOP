#include <QApplication>
#include <QPushButton>
#include "Produs.h"
#include "Repository.h"
#include "Service.h"
#include "Gui.h"

int main(int argc, char *argv[]) {
    testDomain();
    testRepository();
    testService();
    Repository repo{"../date.txt"};
    repo.load();
    Service service{repo};

    QApplication a(argc, argv);
    Gui gui{service};
    gui.show();
    return QApplication::exec();
}
