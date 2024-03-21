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
    //TEST NULL
    Medicament* a = NULL;
    assert(reallocMedicament(&a,1410065408) == 0);
    free(a);
    Medicament m = createMedicament(1,"asdf",2.5,30);
    Medicament m3 = createMedicament(2, "hfg",2, 30);
    Medicament m1 = createMedicament(1, "", 2.5, 30);
    Medicament m2 = createMedicament(1, "asdf", 200, 30);
    assert(get_id(&m) == 1);
    assert(strcmp(get_nume(&m),"asdf") == 0);
    assert(get_concentratie(&m) == 2.5);
    assert(get_cantitate(&m) == 30);

    Lista l = createLista();
    assert(get_len(&l) == 0);
    assert(get_medicamente(&l));
    assert(validator(m,&l) == 1);
    assert(validator(m1, &l) == 0);
    assert(validator(m2, &l) == 0);
    assert(validator(m3, &l) == 1);
    assert(get_len(&l) == 0);
    push(&l,m);
    assert(get_len(&l) == 1);
    push(&l,m3);
    pop(&l, 1);
    assert(get_len(&l) == 1);
    pop(&l, 7);
    assert(destructor(&l) == 1);
}

void test_service() {
    // test ADD
    Lista l = createLista();
    assert(get_len(&l) ==   0);
    assert(add_medicament(&l,1,"Nurofen",2.5,50));
    assert(add_medicament(&l,1,"Nurofen",2.5,30) == 0);
    assert(add_medicament(&l,2,"Nurofen",2.5,50) == 0);
    assert(add_medicament(&l, 2, "", 2.5, 50) == 0);
    //TEST MODIFY
    assert(get_len(&l) == 1);
    assert(modify_medicament(&l,1,"Ibuprofen",3.0) == 1);
    assert(get_concentratie(&l.medicamente[0]) == 3.0);
    assert(modify_medicament(&l, 30, "asdf", 4.2) == 0);
    assert(modify_quantity(&l,1,30));
    assert(modify_quantity(&l, 30, 30) == 0);
    assert(get_cantitate(&l.medicamente[0]) == 30);
    //TEST DELETE
    assert(delete_all_stock(&l, 30) == 0);
    assert(delete_all_stock(&l,1) == 1);
    assert(get_cantitate(&l.medicamente[0]) == 0);

    
    add_medicament(&l,2,"Nurofen",3.2,50);
    //existence
    assert(verify_existence(&l, "Nurofen") == 2);
    assert(verify_existence(&l, "Cauciuc") == -1);
    //sortari
    add_medicament(&l,3,"Penicilina",2.5,42);
    add_medicament(&l,4,"Antibiotic",87.5,21);

    assert(strcmp(get_nume(&l.medicamente[0]),"Ibuprofen") == 0);
    sort(&l,nume_cresc);
    assert(strcmp(get_nume(&l.medicamente[0]),"Antibiotic") == 0);
    assert(get_cantitate(&l.medicamente[0]) == 21);
    sort(&l,cantitate_crescator);
    assert(get_cantitate(&l.medicamente[0]) == 0);
    sort(&l,cantitate_descrescator);
    assert(get_cantitate(&l.medicamente[0]) == 50);
    sort(&l,nume_descresc);
    assert(strcmp(get_nume(&l.medicamente[0]),"Penicilina") == 0);
    //FILTRARI
    Lista filtrate = filter_cantitate(&l,25);
    assert(get_len(&filtrate) == 2);
    destructor(&filtrate);
    filtrate = filter_initiala(&l,'N');
    assert(get_len(&filtrate) == 1);
    assert(strcmp(get_nume(&filtrate.medicamente[0]),"Nurofen") == 0);
    modify_string(get_nume(&l.medicamente[0]));
    destructor(&l);
    destructor(&filtrate);
}