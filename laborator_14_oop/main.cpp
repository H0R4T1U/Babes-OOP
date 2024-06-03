#include <QApplication>


#include "./GUI/disciplinaGui.h"
#include "./GUI/contracteRdonlyGui.h"
#include "./GUI/cosCRUDGui.h"

#include "Domain/Disciplina.h"
#include "Domain/disciplinaValidator.h"
#include "Repository/Repo.h"
#include "Service/DisciplinaService.h"

int main(int argc, char* argv[]) {
    testValidate();
    testDomain();
    testRepo();
    testService();

    Repo repo;
    Repo contractRepo;
    DisciplinaService service{ repo,contractRepo };
    populateDisciplinaList(service);
    QApplication a(argc, argv);
    QApplication::setApplicationName("Contract De Studii GUI");
    disciplinaGui gui{service};
    gui.show();
    return QApplication::exec();
}
