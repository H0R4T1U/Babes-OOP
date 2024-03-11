//
// Created by h on 3/8/24.
//

#include "tests.h"

#include "../Utility/Utility.h"

void test_all() {
    test_domain();
    clear_screen();
    test_service();
    clear_screen();
}

void test_domain() {
    Medicament m = createMedicament(0,"asdf",2.5,30);
    assert(get_id(&m) == 0);
    assert(strcmp(get_nume(&m),"asdf") == 0);
    assert(get_concentratie(&m) == 2.5);
    assert(get_cantitate(&m) == 30);

    Lista l = createLista();
    assert(validator(m,&l) == 0);
    assert(get_len(&l) == 0);
    push(&l,m);
    assert(get_len(&l) == 1);
}

void test_service() {
    // test ADD
    Lista l = createLista();
    assert(get_len(&l) ==   0);
    assert(add_medicament(&l,1,"Nurofen",2.5,50));
    assert(add_medicament(&l,1,"Nurofen",2.5,30) == 0);
    assert(add_medicament(&l,2,"Nurofen",2.5,50) == 0);

    //TEST MODIFY
    assert(get_len(&l) == 1);
    assert(modify_medicament(&l,1,"Ibuprofen",3.0) == 1);
    assert(get_concentratie(&l.medicamente[0]) == 3.0);

    assert(modify_quantity(&l,1,30));
    assert(get_cantitate(&l.medicamente[0]) == 30);
    //TEST DELETE
    assert(delete_all_stock(&l,1) == 1);
    assert(get_cantitate(&l.medicamente[0]) == 0);

    //sortari
    add_medicament(&l,2,"Nurofen",3.2,50);
    add_medicament(&l,3,"Penicilina",2.5,42);
    add_medicament(&l,4,"Antibiotic",87.5,21);

    assert(strcmp(get_nume(&l.medicamente[0]),"Ibuprofen") == 0);
    sort(&l,1,0,1);
    assert(strcmp(get_nume(&l.medicamente[0]),"Antibiotic") == 0);
    assert(get_cantitate(&l.medicamente[0]) == 21);
    sort(&l,0,1,1);
    assert(get_cantitate(&l.medicamente[0]) == 0);
    sort(&l,0,1,0);
    assert(get_cantitate(&l.medicamente[0]) == 50);
    sort(&l,1,0,0);
    assert(strcmp(get_nume(&l.medicamente[0]),"Penicilina") == 0);
    //FILTRARI
    Lista filtrate = filter_cantitate(&l,25);
    assert(get_len(&filtrate) == 2);
    filtrate = filter_initiala(&l,'N');
    assert(get_len(&filtrate) == 1);
    assert(strcmp(get_nume(&filtrate.medicamente[0]),"Nurofen") == 0);
}