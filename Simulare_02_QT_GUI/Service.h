//
// Created by horatiu on 5/19/24.
//

#ifndef SIMULARE_02_SERVICE_H
#define SIMULARE_02_SERVICE_H


#include "repository.h"

class Service {
private:
    Repository repo;
public:
    //constructor service
    Service(Repository repo): repo{repo}{};
    ~Service() = default;
    // Returneaza lista de produse
    std::vector<Produs> serviceGetLista(){
        return repo.getLista();
    }
    // Filtreaza dupa nume
    std::vector<Produs> filterByName(const std::string& nume){
        std::vector<Produs> filtered;
        for(auto& t : serviceGetLista()){
            if(t.getNume() == nume){
                filtered.emplace_back(t);
            }
        }
        return filtered;}
    // Filtreaza dupa pret
    std::vector<Produs> filterByPret(const float pret){
        std::vector<Produs> filtered;
        for(auto& t : serviceGetLista()){
            if(t.getPret() <= pret){
                filtered.emplace_back(t);
            }
        }
        return filtered;}
};

void testService();
#endif //SIMULARE_02_SERVICE_H
