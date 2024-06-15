//
// Created by horatiu on 6/14/24.
//

#include "Validator.h"
#include "Tractor.h"
#include <stdexcept>

void validate(const vector<Tractor>& repo,int id, const string& den, const string& tip,int roti) {
    string err;
    if(tip.empty()){
        err+=("Tipul nu poate fi null!\n");
    }
    if(den.empty()){
        err+=("Denumirea nu poate fi null!\n");
    }
    if(roti%2 == 1){
        err+=("Nr de roti trebuie sa fie par!\n");
    }
    for(auto& x: repo){
        if(x.getId() == id){
            err+=("ID-ul trebuie sa fie unic!\n");
            break;
        }
    }
    if(!err.empty()){
        throw std::invalid_argument(err);
    }



}
