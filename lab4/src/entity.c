#include "entity.h"

#include <stdlib.h>
#include <string.h>

Participant *createParticipant(const char *firstName, const char *lastName,
                               int score) {
    Participant *participant =  malloc(sizeof(Participant));

    participant->firstName = (char *) malloc((strlen(firstName) + 1));
    strcpy(participant->firstName, firstName);

    participant->lastName = (char *) malloc((strlen(lastName) + 1));
    strcpy(participant->lastName, lastName);

    participant->score = score;

    return participant;
}

void destroyParticipant(Participant *participant) {
    free(participant->firstName);
    free(participant->lastName);
    free(participant);
}

char *getFirstName(Participant *participant) {
    return participant->firstName;
}

char *getLastName(Participant *participant) {
    return participant->lastName;
}

int getScore(Participant *participant) {
    return participant->score;
}

void setScore(Participant *participant, int newScore) {
    participant->score = newScore;
}
Participant* copyParticipant(Participant* c)
{
    return createParticipant(c->firstName, c->lastName, c->score);
}