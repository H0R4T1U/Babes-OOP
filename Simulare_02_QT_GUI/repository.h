//
// Created by horatiu on 5/19/24.
//

#ifndef SIMULARE_02_REPOSITORY_H
#define SIMULARE_02_REPOSITORY_H


#include <vector>
#include "Produs.h"
#include <fstream>

class Repository {
private:
    std::vector<Produs> repo = {};
public:
    void loadFromFile(const std::string& fileName){
        std::ifstream fin(fileName);
        while(!fin.eof()){
            std::string nume;
            std::string firma;
            float pret;
            fin>>nume>>firma>>pret;
            repo.emplace_back(nume,firma,pret);
        }
        fin.close();
    }
    std::vector<Produs> getLista(){
        return repo;
    }

};

void testRepository();
#endif //SIMULARE_02_REPOSITORY_H
