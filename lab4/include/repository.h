#pragma once
#include "entity.h"

// elementele sunt de tip void*
typedef void* ElemType;

// pointer la functia care sterge un element
typedef void(*DestroyFct) (ElemType);

// pointer la functia care copiaza un element
typedef ElemType(*CopyFct) (ElemType);

// List de cheltuieli
typedef struct {
        ElemType* elems;
        int lg, cap;
        DestroyFct dfnc;
} List;

/*
* Creeaza o List vida
*/
List* creeazaVid(DestroyFct f);

/*
* Distruge List
* eliberam zona de memorie alocata listei de cheltuieli
* ElemTypeList* l - pointer catre List de cheltuieli
*/
void destroyList(List* l);

// getter pentru un element din List
ElemType get(List* l, int poz);

// setter pentru un element din List
ElemType modifica(List* l, int poz, ElemType p);

// returneaza lungimea listei
int lungime(List* l);

/*
* Adauga unei cheltuieli in vector
* ElemTypeList* l - pointer catre List de cheltuieli
* Cheltuieli c - cheltuiala pe care o adaugam in vector
*/
void adauga(List* l, ElemType el);

// stergem un element din List
ElemType sterge(List* l, int poz);

// facem o copie shallow listei
List* copyList(List* l, CopyFct cf);


int findIndex(List *list, const char *firstName, const char *lastName);
ElemType removeLast(List* l);
