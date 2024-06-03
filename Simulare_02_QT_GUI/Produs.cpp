//
// Created by horatiu on 5/19/24.
//

#include "Produs.h"
#include <cassert>

void testDomain(){
    Produs p{"asdf","asdf",120.00};
    assert(p.getPret() == 120.00);
    assert(p.getNume() == "asdf");
    assert(p.getFirma() == "asdf");
}