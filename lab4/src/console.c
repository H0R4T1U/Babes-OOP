#include "console.h"

#include <stdio.h>
#include <stdlib.h>

void printMenu() {
    printf("\nOPTION MENU:\n");
    printf("Enter 0 to Exit\n");
    printf("Enter 1 to Add\n");
    printf("Enter 2 to Delete\n");
    printf("Enter 3 to Update\n");
    printf("Enter 4 to Filter by score\n");
    printf("Enter 5 to Sort by score\n");
    printf("Enter 6 to Sort by name\n");
    printf("Enter 7 to Show this menu.\n");
    printf("Enter 8 to Filter by initial\n");
    printf("Enter 9 to Print the list\n");
    printf("Enter 10 to Undo\n");
}

void uiPrintList(List *list) {
    for (int i = 0; i < list->lg; ++i) {
        Participant *participant = list->elems[i];
        printf("%s %s: %d\n", getFirstName(participant), getLastName(participant),
               getScore(participant));
    }
}

void uiPrintParticipants(Manager *manager) {
    if ( manager->participanti->lg == 0) {
        printf("There are no participants.\n");
        return;
    }

    printf("The participants are:\n");
    uiPrintList(manager->participanti);
}

void uiAddParticipant(Manager *manager) {
    char firstName[50], lastName[50];
    int score;

    printf("\nEnter the first name: ");
    scanf("%s", firstName);

    printf("Enter the last name: ");
    scanf("%s", lastName);

    printf("Enter the score: ");
    scanf("%d", &score);

    int found = managerAddParticipant(manager, firstName, lastName, score);

    found ? printf("The participant was added.\n")
          : printf("The participant is not valid.\n");
}

void uiDeleteParticipant(Manager *manager) {
    char firstName[50], lastName[50];

    printf("\nEnter the first name: ");
    scanf("%s", firstName);

    printf("Enter the last name: ");
    scanf("%s", lastName);

    int found = managerDeleteParticipant(manager, firstName, lastName);

    found ? printf("The participant was Deleted.\n")
          : printf("The participant doesn't exist.\n");
}

void uiUpdateParticipant(Manager *manager) {
    char firstName[50], lastName[50];
    int newScore;

    printf("\nEnter the first name: ");
    scanf("%s", firstName);

    printf("Enter the last name: ");
    scanf("%s", lastName);

    printf("Enter the new score: ");
    scanf("%d", &newScore);

    int found = managerUpdateParticipant(manager, firstName, lastName, newScore);

    found ? printf("The participant was added.\n")
          : printf("The participant is not valid or doesn't exist.\n");
}

void uiFilterParticipantsByScore(Manager *manager) {
    int minScore;

    printf("Enter the min score you what to filter by: ");
    scanf("%d", &minScore);

    List *filteredList = managerFilterParticipantsByScore(manager->participanti, minScore);

    if ( lungime(filteredList) == 0) {
        printf("There are no elements that fit the description.\n");
    }

    uiPrintList(filteredList);

    managerFreeList(filteredList);
}
void uiFilterParticipantsByInitial(Manager *manager) {
    char initial = 0;

    printf("Enter the initial  you what to filter by: ");
    scanf("%1s",&initial);

    List *filteredList = managerFilterParticipantsByInitial(manager->participanti, initial);

    if ( lungime(filteredList) == 0) {
        printf("There are no elements that fit the description.\n");
    }

    uiPrintList(filteredList);

    managerFreeList(filteredList);
    getchar();
}

void uiSortParticipantsByScore(Manager *manager) {
    int reversed;
    printf("Enter 1 for reversed: ");
    scanf("%d", &reversed);
    int method;
    printf("Enter 1 for bubble sort:");
    scanf("%d",&method);

    List *sortedList;
    if(method == 1) {
        if (reversed == 1) {
            sortedList = managerBubbleSortParticipants(manager->participanti, byScore,1);
        } else {
            sortedList = managerBubbleSortParticipants(manager->participanti, byScore,0);
        }
    }else {
        if (reversed == 1) {
            sortedList = managerSortParticipants(manager->participanti, byScore,1);
        } else {
            sortedList = managerSortParticipants(manager->participanti, byScore,0);
        }
    }

    if (sortedList->lg == 0) {
        printf("The list is empty.\n");
    }

    uiPrintList(sortedList);

    managerFreeList(sortedList);
}

void uiSortParticipantsByName(Manager *manager) {
    int reversed;
    printf("Enter 1 for reversed: ");
    scanf("%d", &reversed);
    int method;
    printf("Enter 1 for bubble sort:");
    scanf("%d",&method);

    List *sortedList;
    if(method == 1) {
        if (reversed == 1) {
            sortedList = managerBubbleSortParticipants(manager->participanti, byName,1);
        } else {
            sortedList = managerBubbleSortParticipants(manager->participanti, byName,0);
        }
    }else {
        if (reversed == 1) {
            sortedList = managerSortParticipants(manager->participanti, byName,1);
        } else {
            sortedList = managerSortParticipants(manager->participanti, byName,0);
        }
    }
    if (sortedList->lg  == 0) {
        printf("The list is empty.\n");
    }

    uiPrintList(sortedList);

    managerFreeList(sortedList);
}

void consoleRun() {
    Manager *manager = managerInnit((void (*)(ElemType)) destroyParticipant, (void (*)(ElemType)) destroyList);
    printMenu();
    while (1) {
        int option;
        printf("\n>>> ");
        int rez;
        rez = scanf("%d", &option);
        while (rez == 0) {
            // Clear input buffer
            while (getchar() != '\n') {
                continue;
            }

            printf("Invalid input. Please enter an integer.\n");
            printf(">>> ");
            rez = scanf("%d", &option);
        }

        switch (option) {
            case 7:
                printMenu();
                break;
            case 0:
                printf("Exiting the app...\n");
                managerDestroyList(manager);
                return;
            case 9:

                uiPrintParticipants(manager);
                break;
            case 1:

                uiAddParticipant(manager);
                break;
            case 2:

                uiDeleteParticipant(manager);
                break;
            case 3:
                uiUpdateParticipant(manager);
                break;
            case 4:

                uiFilterParticipantsByScore(manager);
                break;
            case 5:

                uiSortParticipantsByScore(manager);
                break;
            case 6:

                uiSortParticipantsByName(manager);
                break;
            case 8:
                uiFilterParticipantsByInitial(manager);
                break;
            case 10:
                undo(manager);
                break;
            default:
                printf("The command is not yet implemented.\n");
                break;
        }
    }
}