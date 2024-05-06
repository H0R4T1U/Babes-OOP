//
// Created by h on 3/28/24.
//

#include "DisciplinaService.h"
#include "disciplinaValidator.h"
#include "Console.h"
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
int main() {
	testValidate();
    testDomain();
    testRepo();
    testService();
    //Repo repo;
    MapRepo repo{ 0.2f };
    Repo contractRepo;
    DisciplinaService service{ repo,contractRepo };
    DisciplinaConsole console{ service };
    //console.start();
    _CrtDumpMemoryLeaks();
    return 0;
}
