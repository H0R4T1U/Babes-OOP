//
// Created by horatiu on 6/14/24.
//

#include <cassert>
#include "Produs.h"

void testDomain() {
    Produs p{1,"asdf","asdf",2.35};
    assert(p.getId() == 1);
    assert(p.getPret() == 2.35);
    assert(p.getTip() == "asdf");
    assert(p.getNume() == "asdf");

}
