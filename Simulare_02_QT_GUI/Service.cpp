//
// Created by horatiu on 5/19/24.
//

#include "Service.h"
#include <cassert>
void testService(){
    Repository repo;
    repo.loadFromFile("../test.txt");
    Service serv{repo};
    assert(serv.serviceGetLista().size() == 1);
    assert(serv.filterByPret(300).size() == 1);
    assert(serv.filterByPret(100).empty());
    assert(serv.filterByName("Nestle").size() == 1);
    assert(serv.filterByName("asdf").empty());
}