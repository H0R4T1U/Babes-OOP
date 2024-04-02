//
// Created by h on 3/28/24.
//

#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include <string>
#include <iostream>
using namespace std;

class Disciplina {
    std::string  denumire;
    int ore;
    std::string tip;
    std::string profesor;
public:
    Disciplina(const string& denumire, int ore , const string& tip, const string& profesor ) {
        this->denumire = denumire;
        this->ore = ore;
        this->tip = tip;
        this->profesor = profesor;
    }
    [[nodiscard]] const string&  getDenumire() const {
        return denumire;
    }
    [[nodiscard]] string getTip() const {
        return tip;
    }
    [[nodiscard]] string getProfesor() const {
        return profesor;
    }
    [[nodiscard]] int getOre() const {
        return ore;
    }
    void setOre(int ore) {
        this->ore = ore;
    }
    void setDenumire(const string& denumire) {
        this->denumire = denumire;
    }
    void setTip(const string& tip) {
        this->tip = tip;
    }
    void setProfesor(const string& profesor) {
        this->profesor = profesor;
    }


};

void testDomain();

#endif //DISCIPLINA_H
