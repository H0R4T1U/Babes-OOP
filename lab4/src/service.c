#include "service.h"



#include "validator.h"

#include <string.h>
#include <stdlib.h>

Manager* managerInnit(void(*f1) (ElemType), void(*f2) (ElemType)) {
    Manager* manager = malloc(sizeof(Manager));
    manager->participanti = creeazaVid(f1);
    manager->undoList = creeazaVid(f2);
    return manager;
}

void managerDestroyList(Manager *manager) {
    destroyList(manager->participanti);
    destroyList(manager->undoList);
    free(manager);
}

void managerFreeList(List *list) {
    free(list->elems);
    free(list);
}

int managerAddParticipant(Manager *manager, const char *firstName, const char *lastName,
                          int score) {
    int poz = findIndex(manager->participanti,firstName,lastName);
    if (!isValidName(firstName) || !isValidName(lastName) ||
        !isValidScore(score) || poz != -1) {
        return 0;
    }
    List* toUndo = copyList(manager->participanti, (CopyFct) copyParticipant);
    Participant *participant = createParticipant(firstName, lastName, score);
    adauga(manager->participanti, participant);
    adauga(manager->undoList,toUndo);
    return 1;
}

int managerDeleteParticipant(Manager *manager, const char *firstName, const char *lastName) {
    int poz = findIndex(manager->participanti,firstName,lastName);
    if (poz == -1) {
        return 0;
    }


    List* toUndo = copyList(manager->participanti, (CopyFct) copyParticipant);
    Participant* p;
    p = sterge(manager->participanti,poz);
    destroyParticipant(p);
    adauga(manager->undoList,toUndo);
    return 1;
}

int managerUpdateParticipant(Manager *manager, const char *firstName, const char *lastName,
                             int newScore) {
    int poz = findIndex(manager->participanti,firstName,lastName);
    if (!isValidScore(newScore) || poz == -1) {
        return 0;
    }
    Participant* p = createParticipant(firstName,lastName,newScore);


    List* toUndo = copyList(manager->participanti, (CopyFct) copyParticipant);
    p =  modifica(manager->participanti,poz,p);
    destroyParticipant(p);
    adauga(manager->undoList,toUndo);
    return 1;
}

List *managerFilterParticipantsByScore(List *list, int minScore) {
    List *output = creeazaVid((DestroyFct) destroyParticipant);

    for (int i = 0; i < lungime(list); ++i) {
        Participant* p = get(list,i);
        if (p->score >= minScore) {
            adauga(output, p);
        }
    }

    return output;
}
List *managerFilterParticipantsByInitial(List *list, char initial) {
    List *output = creeazaVid((DestroyFct) destroyParticipant);
    for (int i = 0; i < lungime(list); ++i) {
        Participant* p = get(list,i);
        if (getFirstName(p)[0] == initial) {
            adauga(output, p);
        }
    }

    return output;
}

int byScore(Participant *first, Participant *second) {
    return getScore(first) > getScore(second);
}

int byName(Participant *first, Participant *second) {
    return strcmp(getFirstName(first), getFirstName(second)) > 0;
}



List *managerSortParticipants(List *list, int (*cmp)(Participant *, Participant *),int reversed) {
    List *l = copyList(list, (CopyFct) copyParticipant);
    int i, j;
    // selection sort
    for (i = 0; i < lungime(l); i++)
        for (j = i + 1; j < lungime(l); j++)
        {
            void* p1 = get(l, i);
            void* p2 = get(l, j);
            if (reversed == 0){
                if (cmp(p1, p2)){
                    modifica(l, i, p2);
                    modifica(l, j, p1);
                }
            }
            else if(reversed == 1) {
                if (!cmp(p1, p2)){
                    modifica(l, i, p2);
                    modifica(l, j, p1);
                }
            }
        }
    return l;
}
List *managerBubbleSortParticipants(List* list, int (*cmpF)(Participant* c1, Participant* c2), int reversed){
    int b = 0;
    List *l = copyList(list, (CopyFct) copyParticipant);
    while (b == 0)
    {
        b = 1;
        for (int i = 0; i < lungime(l) - 1; i++)
        {
            void* p1 = get(l, i);
            void* p2 = get(l, i + 1);
            if (reversed == 0)
            {
                if (cmpF(p1, p2))
                {
                    modifica(l, i, p2);
                    modifica(l, i + 1, p1);
                    b = 0;
                }
            }
            if (reversed == 1) {
                if (!cmpF(p1, p2)){
                    modifica(l, i, p2);
                    modifica(l, i + 1, p1);
                    b = 0;
                }
            }
        }
    }
    return l;
}

/*
  Restore previous pet list
  return 0 on ok, 1 if there is no more available undo
*/
int undo(Manager* manager) {
    if (lungime(manager->undoList) == 0) {
        return 1;//no more undo
    }
    List* l = removeLast(manager->undoList);
    destroyList(manager->participanti);
    manager->participanti = l;
    return 0;
}