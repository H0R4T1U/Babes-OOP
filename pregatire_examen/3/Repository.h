//
// Created by horatiu on 6/14/24.
//

#ifndef INC_3_REPOSITORY_H
#define INC_3_REPOSITORY_H
#include <vector>
#include <string>
#include "Produs.h"

using namespace std;


class Repository {
private:
    vector<Produs> repo;
    string fileName;
public:
    explicit Repository(const string& fileName): fileName{fileName}{};
    void load();
    void save();
    void add(Produs&);
    size_t size();
    vector<Produs> getAll();
    __int64_t find(const string& denumire);
};
void testRepository();

#endif //INC_3_REPOSITORY_H
