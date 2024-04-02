//
// Created by h on 3/28/24.
//

#include "Disciplina.h"

#include <cassert>

void testDomain() {
    // crearea unui obiect de tip Car
    Disciplina testDomain{ "ASC",99,"Teama","Vancea" };
    assert(testDomain.getDenumire() == "ASC");
    assert(testDomain.getOre() == 99);
    assert(testDomain.getTip() == "Teama");
    assert(testDomain.getProfesor() == "Vancea");
}