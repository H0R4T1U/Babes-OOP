#pragma once

#include "service.h"

/*
Prints the main menu.
*/
void printMenu();

/*
Prints a list given as input.
Params: list - a list of participants
*/
void uiPrintList(List *list);

/*
Prints all participants.
Params: list - a list of participants
*/
void uiPrintParticipants(Manager *manager);

/*
Handles adding a participant through the user interface.
Params: list - a list of participants
*/
void uiAddParticipant(Manager *manager);

/*
Handles deleting a participant through the user interface.
Params: list - a list of participants
*/
void uiDeleteParticipant(Manager *manager);

/*
Handles updating a participant's score through the user interface.
Params: list - a list of participants
*/
void uiUpdateParticipant(Manager *manager);

/*
Handles filtering the participants by score through the user interface.
Params: list - a list of participants
*/
void uiFilterParticipantsByScore(Manager *manager);
/*
Handles filtering the participants by initial through the user interface.
Params: list - a list of participants
*/
void uiFilterParticipantsByInitial(Manager* manager);
/*
Handles sorting the participants by score through the user interface.
Params: list - a list of participants
*/
void uiSortParticipantsByScore(Manager *manager);

/*
Runs the console user interface.
*/
void consoleRun();
