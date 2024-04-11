//
// Created by h on 3/8/24.
//

#include "Service.h"

\

/// 
/// @param list Lista de medicamente
/// @param id id medicament
/// @param nume nume medicament 
/// @param concentratie concentratie medicament
/// @param cantitate cantitate medicament
/// @return 0 sau 1 in functie daca medicamentul a fost adaugat in lista
int add_medicament(Lista* list,int id, char* nume, float concentratie,int cantitate) {
    Medicament m = createMedicament(id,nume,concentratie,cantitate);
    if(validator(m,list) == 1) {
        push(list,m);
        return 1;
    }else {
        return 0;
    }
}

/// 
/// @param list lista de medicamente
/// @param id id ul medicamentului care sa fie modificat
/// @param cantitate noua cantitate
/// @return 1 sau 0 in functie de succesul functiei
int modify_quantity(Lista* list, int id, int cantitate){
   int len = get_len(list);
    for(int i =0 ; i< len;i++) {
        if(get_id(&list->medicamente[i]) == id) {
            set_cantitate(&list->medicamente[i],cantitate);
            return 1;
        }
    }
    return 0;
}

/// 
/// @param list lista de medicamente
/// @param id id care sa fie modificat
/// @param nume numele noiu
/// @param concentratie concentratia noua
/// @return 1 sau 0 in functie de succesul functiei
int modify_medicament(Lista* list, int id,char* nume, float concentratie) {
    int len = get_len(list);
    for(int i = 0 ; i <= len;i++) {
        if(get_id(&list->medicamente[i]) == id) {
            set_nume(&list->medicamente[i],nume);
            set_concentratie(&list->medicamente[i],concentratie);
            return 1;
        }
    }
    return 0;

}

/// 
/// @param list lista de medicamente
/// @param id id de la care sa fie sters tot stockul
/// @return 1 sau 0 in functie de succesul functiei
int delete_all_stock(Lista* list,int id) {
    int len = get_len(list);
    for(int i = 0 ; i<len;i++) {
        if(get_id(&list->medicamente[i])==id) {
            set_cantitate(&list->medicamente[i],0);
            return 1;
        }

    }
    return 0;
}

/// 
/// @param list lista de medicamente
/// @param nume flag:daca este  setat sorteaza dupa nume
/// @param cantitate flag: daca este setat sorteaza dupa cantitate
/// @param crescator flag; daca este setat sorteaza crescator
void sort(Lista* list, int nume, int cantitate,int crescator) {
    
    int len = get_len(list);
    if(cantitate) {
        for(int k = 0; k<= len; k++ ) {
            for(int i = 0; i< len-1;i++) {
                if(crescator) {
                    if(get_cantitate(&list->medicamente[i]) > get_cantitate(&list->medicamente[i+1])) {
                        listswap(list,i,i+1);
                    }
                }else {
                    if(get_cantitate(&list->medicamente[i]) < get_cantitate(&list->medicamente[i+1])) {
                        listswap(list,i,i+1);
                    }
                }
            }

        }
    }
    if(nume) {
        for(int k = 0 ;k <= len; k++) {
            for(int i = 0; i < len-1;i++) {
                if(crescator) {
                    if(strcmp(get_nume(&list->medicamente[i]), get_nume(&list->medicamente[i+1])) >0) {
                        listswap(list,i,i+1);
                    }
                }else {
                    if(strcmp(get_nume(&list->medicamente[i]), get_nume(&list->medicamente[i+1])) < 0) {
                        listswap(list,i,i+1);
                    }
                }
            }
        }

    }
}

/// Filtreaza medicamente dupa o cantitate data
/// @param list lista de medicamente
/// @param cantitate de filtrat
/// @return o lista de medicamente filtrata
Lista filter_cantitate(Lista* list, int cantitate) {
    Medicament * meds = get_medicamente(list);
    Lista filtrate = createLista();
    int len = get_len(list);
    for(int i = 0 ; i<len;i++) {
        if(get_cantitate(&meds[i]) <= cantitate) {
            push(&filtrate,meds[i]);
        }
    }
    return filtrate;
}

/// FIltreaza medicamente dupa initiala
/// @param list
/// @param initiala
/// @return
Lista filter_initiala(Lista* list, char initiala) {
    Medicament * meds = get_medicamente(list);
    Lista filtrate = createLista();
    int len = get_len(list);
    for(int i = 0 ; i<len;i++) {
        if(get_nume(&meds[i])[0] == initiala) {
            push(&filtrate,meds[i]);
        }
    }
    return filtrate;
}

/// Verifica daca exista medicamentul cu nume dat
/// @param list lista de medicamente
/// @param nume nume dupa care se cauta
/// @return id-ul medicamentului cu numele
int verify_existence(Lista* list,char* nume) {
    int len = get_len(list);
    for(int i = 0 ; i<len;i++) {
        if(strcmp(get_nume(&list->medicamente[i]),nume) == 0) {
            return get_id(&list->medicamente[i]);
        }
    }
    return -1;

}