#include <QApplication>


#include "./GUI/DisciplinaGui.h"
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
    a.setApplicationName("Contract De Studii GUI");
    DisciplinaGui gui{service};
    gui.show();
    return QApplication::exec();
}
