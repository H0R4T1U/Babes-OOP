//
// Created by horatiu on 6/16/24.
//

#include <cassert>
#include "Task.h"

void testDomain() {
    Task t{1,"asdf",{"asdf1","asdf2"},"open"};
    assert(t.getId() == 1);
    assert(t.getDescriere() == "asdf");
    assert(t.getProgramatori().at(0) == "asdf1");
    assert(t.getStare() == "open");
}
