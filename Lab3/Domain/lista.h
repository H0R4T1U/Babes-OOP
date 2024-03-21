//
// Created by h on 3/8/24.
//

#ifndef LISTA_H
#define LISTA_H
#include "medicament.h"
#include <stdlib.h>

typedef struct {
    Medicament* medicamente;
    int len;
}Lista;

int get_len(Lista* lista);
void set_len(Lista* lista,int len);
Medicament* get_medicamente(Lista* lista);
void push(Lista* lista,Medicament medicament);
void pop(Lista* lista,int id);
void listswap(Lista* list,int index1,int index2);
Lista createLista();
int destructor(Lista* list);
#endif //LISTA_H
