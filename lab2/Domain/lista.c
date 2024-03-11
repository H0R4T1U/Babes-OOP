//
// Created by h on 3/8/24.
//

#include "lista.h"

///
/// @param lista lista de medicamente
/// @return returneaza len
int get_len(Lista* lista) {
    return lista->len;
}

///
/// @param lista lista de medicamente
/// @param len lungimea noua a listei
void set_len(Lista* lista,int len){
    lista->len = len;
}

///
/// @param lista lista de medicamente
/// @return array de medicamente
Medicament* get_medicamente(Lista* lista) {
    return lista->medicamente;
}

/// Adauga medicament in listsa
/// @param lista lista de medicamente
/// @param medicament medicament nou
void push(Lista* lista,Medicament medicament) {
    lista->medicamente[get_len(lista)] = medicament;
    lista->len += 1;
}

/// Sterge medicamentul cu id-ul furnizat
/// @param lista lista de medicamente
/// @param id id ul medicamentului care sa fie sters
void pop(Lista* lista, int id) {

    int len = get_len(lista);
    for(int i = 0 ; i < len; i++) {
        if(lista->medicamente[i].id == id) {
            for(int j = i+1;j<len;j++) {
                lista->medicamente[j-1] = lista->medicamente[j];
            }
            lista->len -=1;
            return;
        }
    }
}

/// Creaza o lista
/// @return Returneaza lista
Lista createLista() {
    {
        Lista list;
        set_len(&list, 0);
        return list;
    }
}

/// Interschimba 2 elemente
/// @param list lista de medicamente
/// @param index1 index medicament 1
/// @param index2 index medicament 2
void listswap(Lista* list,int index1,int index2) {
    Medicament med = list->medicamente[index1];
    list->medicamente[index1] = list->medicamente[index2];
    list->medicamente[index2] = med;
}