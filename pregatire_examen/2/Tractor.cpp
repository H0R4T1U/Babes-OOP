//
// Created by horatiu on 6/14/24.
//

#include <cassert>
#include "Tractor.h"

void testDomain() {
    Tractor t{1,"A","b",4};
    assert(t.getId() == 1);
    assert(t.getRoti() == 4);
    assert(t.getTip() == "b");
    assert(t.getDenumire() == "A");
}
