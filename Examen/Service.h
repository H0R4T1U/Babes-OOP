//
// Created by horatiu on 6/16/24.
//

#ifndef EXAMEN_SERVICE_H
#define EXAMEN_SERVICE_H


#include "Repository.h"
#include "Observer.h"

class Service: public Observable {
private:
    // Repository
    Repository& repo;
public:
    // Constructor Service
    explicit Service(Repository& repo): repo{repo}{};
    // Adauga in repo si fisier
    void add(int id, const string& denumire,const vector<string>&programatori,const string& stare);
    // valideaza date
    static bool validate(vector<Task>,int id, const string& denumire,const vector<string>&programatori,const string& stare);
    // modifca starea task-ului
    void modifyStare(const string& denumire,const string& stare);
    // gaseste pozitia task-ului cu denumirea denumire
    size_t find(const string& denumire);
    // SOrteaza dupa stare
    vector<Task> sortStare();
    // Filtreaza dupa task-uri cu programator
    vector<Task> filter(const string& programator);
    // returneaza marimea repo-ului
    size_t getSize();
    // returneaza vectorului din repo
    vector<Task> getAll();
};
// teste service
void testService();

#endif //EXAMEN_SERVICE_H
