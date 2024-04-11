#include "repository.h"

#include <string.h>
#include <stdlib.h>

List* creeazaVid(DestroyFct f)
{
	List* rez = malloc(sizeof(List));
	if (rez != NULL)
	{
		rez->lg = 0;
		rez->cap = 2;
		rez->elems = malloc(sizeof(ElemType) * rez->cap);
		rez->dfnc = f;
	}
	return rez;
}

void destroyList(List* l)
{
	for (int i = 0; i < lungime(l); i++) {
		l->dfnc(l->elems[i]);
	}

	free(l->elems);
	free(l);
}

ElemType get(List* l, int poz)
{
	return l->elems[poz];
}

ElemType modifica(List* l, int poz, ElemType p)
{
	ElemType rez = l->elems[poz];
	l->elems[poz] = p;
	return rez;
}

int lungime(List* l)
{
	return l->lg;
}

void ensureCapacity(List* l)
{
	if (lungime(l) < l->cap) {
		return;
	}
	ElemType* nElems = malloc(sizeof(ElemType) * (l->cap + 2));
	for (int i = 0; i < l->lg; i++) {
		nElems[i] = l->elems[i];
	}
	free(l->elems);
	l->elems = nElems;
	l->cap += 2;
}

void adauga(List* l, ElemType el)
{
	ensureCapacity(l);
	l->elems[l->lg] = el;
	l->lg++;
}

ElemType sterge(List* l, int poz)
{
	ElemType rez = l->elems[poz];
	for (int i = poz; i < l->lg; i++)
		l->elems[i] = l->elems[i + 1];
	l->lg--;
	return rez;
}

List* copyList(List* l, CopyFct cf)
{
	List* rez = creeazaVid(l->dfnc);
	for (int i = 0; i < lungime(l); i++) {
		ElemType p = get(l, i);
		adauga(rez, cf(p));
	}
	return rez;
}

int findIndex(List *list, const char *firstName, const char *lastName) {
	for (int i = 0; i < lungime(list); ++i) {
		if (strcmp(getFirstName(list->elems[i]), firstName) == 0 &&
			strcmp(getLastName(list->elems[i]), lastName) == 0)
			return i;
	}

	return -1;
}

ElemType removeLast(List* l) {
	ElemType rez = l->elems[l->lg - 1];
	l->lg -= 1;
	return rez;
}