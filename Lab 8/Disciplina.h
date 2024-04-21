//
// Created by h on 3/28/24.
//

#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include <string>
#include <iostream>
using namespace std;

class Disciplina {
    // Denumirea disciplinei
    std::string  denumire;
    // numarul de ore
    int ore;
    // Tipul disciplinei
    std::string tip;
    // profesorul disciplinei
    std::string profesor;
public:
    Disciplina(const string& d, int ore, const string& t, const string& p) : denumire{ d }, ore{ ore }, tip{ t }, profesor{ p } {};
    // constructor unui obiect de tip masina fara argumente
    Disciplina() :denumire{ "" }, ore{ 0 }, tip{ "" }, profesor{ "" } {};
    const string& getDenumire() const {
        return denumire;
    }
    string getTip() const {
        return tip;
    }
    string getProfesor() const {
        return profesor;
    }
    int getOre() const {
        return ore;
    }
    void setOre(int new_ore) {
        this->ore = new_ore;
    }
    void setDenumire(const string& new_denumire) {
        this->denumire = new_denumire;
    }
    void setTip(const string& new_tip) {
        this->tip = new_tip;
    }
    void setProfesor(const string& new_profesor) {
        this->profesor = new_profesor;
    }

    Disciplina(const Disciplina& ot) : denumire{ ot.denumire }, ore{ ot.ore }, tip{ ot.tip }, profesor{ ot.profesor } {
        cout << "";
    }
    // operator assignment
        // copiaza Disciplina din disciplina in this
    Disciplina& operator=(const Disciplina& dis)
    {
        denumire = dis.getDenumire();
        ore = dis.getOre();
        tip = dis.getTip();
        profesor = dis.getProfesor();
        return *this;
    }

    // move constructor
    // se apeleaza cand construim o masina noua dintr-un r-value (ex la return)
    Disciplina(Disciplina&& source) noexcept
    {
        denumire = source.getDenumire();
        ore = source.getOre();
        tip = source.getTip();
        profesor = source.getProfesor();
    }
};

void testDomain();

#endif //DISCIPLINA_H
