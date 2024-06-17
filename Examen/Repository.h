//
// Created by horatiu on 6/16/24.
//

#ifndef EXAMEN_REPOSITORY_H
#define EXAMEN_REPOSITORY_H
#include "Task.h"
#include <vector>
using namespace std;

class Repository {
private:
    // vector cu task-uri
    vector<Task> repo;
    // fisier de deschis
    string fileName;
public:
    // Constructor Repository
    explicit Repository(const string& nume): fileName{nume}{};
    // Getter Size
    size_t getSize();
    // Getter Vector Task-uri
    vector<Task> getAll();
    // Load from file
    void load();
    // Save to file
    void save();
    // Addauga la repo
    void add(Task& t1);
    // modifica starea elem din repo
    void modify(size_t pos, const string& stare);

};
// testeaza repository
void testRepository();
#endif //EXAMEN_REPOSITORY_H
