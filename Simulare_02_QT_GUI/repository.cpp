//
// Created by horatiu on 5/19/24.
//

#include <cassert>
#include "repository.h"


void testRepository(){
    Repository repo{};
    repo.loadFromFile("../test.txt");
    assert(repo.getLista().size() == 1);
    assert(repo.getLista()[0].getNume() == "Nestle");
}