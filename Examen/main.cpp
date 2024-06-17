#include <QApplication>
#include <QPushButton>
#include "Task.h"
#include "Repository.h"
#include "Service.h"
#include "Gui.h"
#include "ferestre.h"

int main(int argc, char *argv[]) {
    // teste
    testDomain();
    testRepository();
    testService();
    // initializam repo
    Repository repo{"../date.txt"};
    // incarcam din fisier
    repo.load();
    // initializam service
    Service service{repo};
    QApplication a(argc, argv);
    // initializam gui si ferester
    Gui gui{service};
    Ferestre f1{service,"open"};
    Ferestre f2{service,"closed"};
    Ferestre f3{service,"inprogress"};
    // afisam gui si ferestre
    gui.show();
    f1.show();
    f2.show();
    f3.show();
    return QApplication::exec();
}
