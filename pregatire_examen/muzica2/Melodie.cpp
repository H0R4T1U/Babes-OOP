//
// Created by horatiu on 6/15/24.
//

#include <cassert>
#include "Melodie.h"

void testDomain() {
    Melodie m {1,"a","a","rock"};
    assert(m.getId() == 1);
    assert(m.getArtist() == "a");
    assert(m.getTitlu() == "a");
    assert(m.getTip() == "rock");
}
