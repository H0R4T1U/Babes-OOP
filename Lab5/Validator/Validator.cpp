//
// Created by h on 3/28/24.
//

#include "Validator.h"


void Validator::validate(const Disciplina& d) {
    vector<string> msgs;
    if(d.getOre() < 0) msgs.emplace_back("PRET NEGATIV!");
    if(d.getTip().empty()) msgs.emplace_back("TIP INVALID");
    if(d.getDenumire().empty()) msgs.emplace_back("DENUMIRE INVALIDA!");
    if(d.getProfesor().empty() ) msgs.emplace_back("PROFESOR INVALID!");
    if(!msgs.empty()) {
        string msg;
        for(const auto & i : msgs) {
            msg += i + " ";
        }
        throw std::invalid_argument( msg);
    }
}

