#include "tests.h"

#include "entity.h"
#include "repository.h"
#include "service.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

void entityTests() {
    const char *firstName = "John";
    const char *lastName = "Snow";
    const int score = 99;

    Participant *participant = createParticipant(firstName, lastName, score);

    assert(strcmp(getFirstName(participant), firstName) == 0);
    assert(strcmp(getLastName(participant), lastName) == 0);
    assert(getScore(participant) == score);
    setScore(participant, 120);
    assert(getScore(participant) == 120);
    destroyParticipant(participant);
}

void repoTests() {
    const char *p1FirstName = "The";
    const char *p1LastName = "Rock";
    const int p1Score = 99;

    const char *p2FirstName = "George";
    const char *p2LastName = "Bush";
    const int p2Score = 80;

    const char *badName = "Nobody";

    Participant *p1 = createParticipant(p1FirstName, p1LastName, p1Score);
    Participant *p2 = createParticipant(p2FirstName, p2LastName, p2Score);

    List *myList = creeazaVid((DestroyFct) destroyParticipant);

    // Add
    adauga(myList, p1);
    adauga(myList, p2);

    assert(lungime(myList) == 2);

    assert(strcmp(getFirstName(myList->elems[0]), p1FirstName) == 0);
    assert(strcmp(getLastName(myList->elems[0]), p1LastName) == 0);
    assert(getScore(myList->elems[0]) == p1Score);

    assert(strcmp(getFirstName(myList->elems[1]), p2FirstName) == 0);
    assert(strcmp(getLastName(myList->elems[1]), p2LastName) == 0);
    assert(getScore(myList->elems[1]) == p2Score);

    // Find
    int index = findIndex(myList, p2FirstName, p2LastName);
    assert(index == 1);

    int badIndex = findIndex(myList, badName, p2LastName);
    assert(badIndex == -1);

    // Delete
    sterge(myList, 0);
    assert(lungime(myList) == 1);

    assert(strcmp(getFirstName(myList->elems[0]), p2FirstName) == 0);
    assert(strcmp(getLastName(myList->elems[0]), p2LastName) == 0);
    assert(getScore(myList->elems[0]) == p2Score);



    // Update
    const int newScore = 99;
    Participant* p = createParticipant(p2FirstName,p2LastName,newScore);
    modifica(myList, 0,p);

    assert(strcmp(getFirstName(myList->elems[0]), p2FirstName) == 0);
    assert(strcmp(getLastName(myList->elems[0]), p2LastName) == 0);
    assert(getScore(myList->elems[0]) == newScore);

    modifica(myList, 0,p);
    assert(lungime(myList) == 1);
    assert(strcmp(getFirstName(myList->elems[0]), p2FirstName) == 0);
    assert(strcmp(getLastName(myList->elems[0]), p2LastName) == 0);
    assert(getScore(myList->elems[0]) == newScore);
    destroyParticipant(p1);
    destroyParticipant(p2);
    destroyList(myList);
}

void serviceTests() {
    const char *p1FirstName = "The";
    const char *p1LastName = "Rock";
    const int p1Score = 99;

    const char *p2FirstName = "George";
    const char *p2LastName = "Bush";
    const int p2Score = 80;

    const char *badName = "Nom32";

    Manager* manager = managerInnit((void (*)(ElemType)) destroyParticipant, (void (*)(ElemType)) destroyList);
    assert(undo(manager) == 1);
    // Add
    assert(managerAddParticipant(manager, p1FirstName, p1LastName, p1Score) == 1);
    assert(managerAddParticipant(manager, p2FirstName, p2LastName, p2Score) == 1);
    assert(manager->participanti->lg == 2);

    assert(managerAddParticipant(manager, badName, p2LastName, p2Score) == 0);
    assert(managerAddParticipant(manager, p2FirstName, badName, p2Score) == 0);
    assert(managerAddParticipant(manager, p2FirstName, p2LastName, 120) == 0);
    assert(managerAddParticipant(manager, p2FirstName, p2LastName, p2Score) == 0);
    assert(manager->participanti->lg == 2);

    assert(managerDeleteParticipant(manager, p1FirstName, p1LastName) == 1);

    assert(manager->participanti->lg == 1);

    assert(managerDeleteParticipant(manager, p2FirstName, badName) == 0);
    assert(managerDeleteParticipant(manager, badName,"231" ) == 0);
    assert(managerDeleteParticipant(manager, "123", badName) == 0);
    assert(manager->participanti->lg == 1);

    const int newScore = 99;
    assert(managerUpdateParticipant(manager, p2FirstName, p2LastName, newScore) == 1);
    assert(manager->participanti->lg == 1);
    assert(getScore(manager->participanti->elems[0]) == newScore);

    assert(managerUpdateParticipant(manager, p2FirstName, badName, p2Score) == 0);
    assert(managerUpdateParticipant(manager, p2FirstName, p2LastName, 150) == 0);
    assert(manager->participanti->lg == 1);
    assert(getScore(manager->participanti->elems[0]) == newScore);

    assert(managerDeleteParticipant(manager, p2FirstName, p2LastName) ==1);

    assert(managerAddParticipant(manager, p1FirstName, p1LastName, p1Score) == 1);
    assert(managerAddParticipant(manager, p2FirstName, p2LastName, p2Score )== 1);

    int minScore = 90;
    List *filteredList = managerFilterParticipantsByScore(manager->participanti, minScore);
    assert(lungime(filteredList) == 1);

    managerFreeList(filteredList);

    int maxScore = 100;
    filteredList = managerFilterParticipantsByScore(manager->participanti, maxScore);
    assert(lungime(filteredList) == 0);
    destroyList(filteredList);

    char initial = 'T';
    List* filteredList1 = managerFilterParticipantsByInitial(manager->participanti, initial);
    assert(lungime(filteredList1) == 1);

    const char *p3FirstName = "AAron";
    const char *p3LastName = "Paul";
    const int p3Score = 95;
    // Add
    assert(managerAddParticipant(manager, p3FirstName, p3LastName, p3Score) == 1);





    List *sortedList = managerSortParticipants(manager->participanti, byName,0);
    assert(sortedList->lg == 3);
    assert(strcmp(getFirstName(sortedList->elems[0]), p3FirstName) == 0);
    assert(strcmp(getLastName(sortedList->elems[0]), p3LastName) == 0);
    assert(getScore(sortedList->elems[0]) == p3Score);

    assert(strcmp(getFirstName(sortedList->elems[1]), p2FirstName) == 0);
    assert(strcmp(getLastName(sortedList->elems[1]), p2LastName) == 0);
    assert(getScore(sortedList->elems[1]) == p2Score);

    assert(strcmp(getFirstName(sortedList->elems[2]), p1FirstName) == 0);
    assert(strcmp(getLastName(sortedList->elems[2]), p1LastName) == 0);
    assert(getScore(sortedList->elems[2]) == p1Score);

    destroyList(sortedList);

    List *sortedList1 = managerSortParticipants(manager->participanti, byScore,0);
    assert(sortedList1->lg == 3);
    assert(strcmp(getFirstName(sortedList1->elems[0]), p2FirstName) == 0);
    assert(strcmp(getLastName(sortedList1->elems[0]), p2LastName) == 0);
    assert(getScore(sortedList1->elems[0]) == p2Score);

    assert(strcmp(getFirstName(sortedList1->elems[1]), p3FirstName) == 0);
    assert(strcmp(getLastName(sortedList1->elems[1]), p3LastName) == 0);
    assert(getScore(sortedList1->elems[1]) == p3Score);

    assert(strcmp(getFirstName(sortedList1->elems[2]), p1FirstName) == 0);
    assert(strcmp(getLastName(sortedList1->elems[2]), p1LastName) == 0);
    assert(getScore(sortedList1->elems[2]) == p1Score);

    destroyList(sortedList1);

    List *sortedList2 = managerSortParticipants(manager->participanti, byName,1);
    assert(sortedList2->lg == 3);
    assert(strcmp(getFirstName(sortedList2->elems[0]), p1FirstName) == 0);
    assert(strcmp(getLastName(sortedList2->elems[0]), p1LastName) == 0);
    assert(getScore(sortedList2->elems[0]) == p1Score);

    assert(strcmp(getFirstName(sortedList2->elems[1]), p2FirstName) == 0);
    assert(strcmp(getLastName(sortedList2->elems[1]), p2LastName) == 0);
    assert(getScore(sortedList2->elems[1]) == p2Score);

    assert(strcmp(getFirstName(sortedList2->elems[2]), p3FirstName) == 0);
    assert(strcmp(getLastName(sortedList2->elems[2]), p3LastName) == 0);
    assert(getScore(sortedList2->elems[2]) == p3Score);

    destroyList(sortedList2);

    List *sortedList3 = managerSortParticipants(manager->participanti, byScore,1);
    assert(sortedList3->lg == 3);
    assert(strcmp(getFirstName(sortedList3->elems[0]), p1FirstName) == 0);
    assert(strcmp(getLastName(sortedList3->elems[0]), p1LastName) == 0);
    assert(getScore(sortedList3->elems[0]) == p1Score);

    assert(strcmp(getFirstName(sortedList3->elems[1]), p3FirstName) == 0);
    assert(strcmp(getLastName(sortedList3->elems[1]), p3LastName) == 0);
    assert(getScore(sortedList3->elems[1]) == p3Score);



    assert(strcmp(getFirstName(sortedList3->elems[2]), p2FirstName) == 0);
    assert(strcmp(getLastName(sortedList3->elems[2]), p2LastName) == 0);
    assert(getScore(sortedList3->elems[2]) == p2Score);

    destroyList(sortedList3);
    List *sortedList4 = managerBubbleSortParticipants(manager->participanti, byName,0);
    assert(sortedList4->lg == 3);
    assert(strcmp(getFirstName(sortedList4->elems[0]), p3FirstName) == 0);
    assert(strcmp(getLastName(sortedList4->elems[0]), p3LastName) == 0);
    assert(getScore(sortedList4->elems[0]) == p3Score);

    assert(strcmp(getFirstName(sortedList4->elems[1]), p2FirstName) == 0);
    assert(strcmp(getLastName(sortedList4->elems[1]), p2LastName) == 0);
    assert(getScore(sortedList4->elems[1]) == p2Score);

    assert(strcmp(getFirstName(sortedList4->elems[2]), p1FirstName) == 0);
    assert(strcmp(getLastName(sortedList4->elems[2]), p1LastName) == 0);
    assert(getScore(sortedList4->elems[2]) == p1Score);

    destroyList(sortedList4);

    List *sortedList5 = managerBubbleSortParticipants(manager->participanti, byScore,0);
    assert(sortedList5->lg == 3);

    assert(strcmp(getFirstName(sortedList5->elems[0]), p2FirstName) == 0);
    assert(strcmp(getLastName(sortedList5->elems[0]), p2LastName) == 0);
    assert(getScore(sortedList5->elems[0]) == p2Score);

    assert(strcmp(getFirstName(sortedList5->elems[1]), p3FirstName) == 0);
    assert(strcmp(getLastName(sortedList5->elems[1]), p3LastName) == 0);
    assert(getScore(sortedList5->elems[1]) == p3Score);

    assert(strcmp(getFirstName(sortedList5->elems[2]), p1FirstName) == 0);
    assert(strcmp(getLastName(sortedList5->elems[2]), p1LastName) == 0);
    assert(getScore(sortedList5->elems[2]) == p1Score);

    destroyList(sortedList5);

    List *sortedList6 = managerBubbleSortParticipants(manager->participanti, byName,1);
    assert(sortedList6->lg == 3);

    assert(strcmp(getFirstName(sortedList6->elems[0]), p1FirstName) == 0);
    assert(strcmp(getLastName(sortedList6->elems[0]), p1LastName) == 0);
    assert(getScore(sortedList6->elems[0]) == p1Score);

    assert(strcmp(getFirstName(sortedList6->elems[1]), p2FirstName) == 0);
    assert(strcmp(getLastName(sortedList6->elems[1]), p2LastName) == 0);
    assert(getScore(sortedList6->elems[1]) == p2Score);

    assert(strcmp(getFirstName(sortedList6->elems[2]), p3FirstName) == 0);
    assert(strcmp(getLastName(sortedList6->elems[2]), p3LastName) == 0);
    assert(getScore(sortedList6->elems[2]) == p3Score);

    destroyList(sortedList6);

    List *sortedList7 = managerBubbleSortParticipants(manager->participanti, byScore,1);
    assert(sortedList7->lg == 3);

    assert(strcmp(getFirstName(sortedList7->elems[0]), p1FirstName) == 0);
    assert(strcmp(getLastName(sortedList7->elems[0]), p1LastName) == 0);
    assert(getScore(sortedList7->elems[0]) == p1Score);

    assert(strcmp(getFirstName(sortedList7->elems[1]), p3FirstName) == 0);
    assert(strcmp(getLastName(sortedList7->elems[1]), p3LastName) == 0);
    assert(getScore(sortedList7->elems[1]) == p3Score);



    assert(strcmp(getFirstName(sortedList7->elems[2]), p2FirstName) == 0);
    assert(strcmp(getLastName(sortedList7->elems[2]), p2LastName) == 0);
    assert(getScore(sortedList7->elems[2]) == p2Score);

    destroyList(sortedList7);

    assert(lungime(manager->participanti) == 3);
    undo(manager);
    assert(lungime(manager->participanti) == 2);
    managerFreeList(filteredList1);
    managerDestroyList(manager);
}

void runTests() {
    entityTests();
    repoTests();
    serviceTests();
    printf("All tests passed.\n");
}