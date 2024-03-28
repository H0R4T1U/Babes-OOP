#pragma once

/*
It's a Participant object
Attrs: firstName - a string containing the first name of a participant
        lastName - a string containing the last name of a participant
        score - a number form 0 to 100 witch is the score of the participant
*/
typedef struct {
    char *firstName;
    char *lastName;
    int score;
} Participant;

/*
Creates a participant
Params: firstName - a string containing the first name of a participant
        lastName - a string containing the last name of a participant
        score - a number form 0 to 100 witch is the score of the participant
*/
Participant *createParticipant(const char *firstName, const char *lastName,
                               int score);

/*
Destroying a participant
Params: participant - a participant given by pointer
*/
void destroyParticipant(Participant *participant);

/*
Getter for the first name of a participant
Params: participant - a participant given by an address
*/
char *getFirstName(Participant *participant);

/*
Getter for the last name of a participant
Params: participant - a participant given by an address
*/
char *getLastName(Participant *participant);

/*
Getter for the score of a participant
Params: participant - a participant given by an address
*/
int getScore(Participant *participant);

/*
Setter for the score attribute of a participant
Params: participant - a participant given by an address
*/
void setScore(Participant *participant, int newScore);

Participant* copyParticipant(Participant* c);
