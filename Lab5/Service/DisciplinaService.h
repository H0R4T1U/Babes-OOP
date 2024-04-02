//
// Created by h on 3/28/24.
//

#ifndef DISCIPLINASERVICE_H
#define DISCIPLINASERVICE_H
#include "../Repository/Repo.h"
#include "../Validator/Validator.h"


class DisciplinaService {
    Repo& rep;
    Validator& val;

public:
    DisciplinaService(Repo& r,Validator v)  noexcept:rep{r}, val{ v }{};
    DisciplinaService(const DisciplinaService& dS) = delete;
    [[nodiscard]] vector<Disciplina> getDisciplineList()const;
    void addDisciplina(const string& denumire,int ore, const string& tip, const string& profesor);
    void modifyDisciplina(const string& denumire,const string& new_denumire,int ore, const string& tip, const string& profesor);
    void deleteDisciplina(const string& denumire);
    [[nodiscard]] Disciplina findDisciplina(const string& denumire) const;
    [[nodiscard]] size_t listSize() const;
};


void testService();

#endif //DISCIPLINASERVICE_H
