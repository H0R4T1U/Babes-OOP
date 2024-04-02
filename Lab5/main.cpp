//
// Created by h on 3/28/24.
//

#include "Service/DisciplinaService.h"
#include "Ui/Console.h"
int main() {
    testDomain();
    testRepo();
    testService();
    Repo repo;
    Validator val;
    DisciplinaService service{ repo,val };
    DisciplinaConsole console{ service };
    console.start();
    return 0;
}
