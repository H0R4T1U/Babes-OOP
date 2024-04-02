//
// Created by h on 3/28/24.
//

#ifndef VALIDATOR_H
#define VALIDATOR_H
#include <fstream>
#include <vector>

#include "../Domain/Disciplina.h"
using namespace std;
class ValidateException {

public:
    vector<string> msgs;
    explicit ValidateException(const vector<string>& errors) :msgs{ errors } {}
    //functie friend (vreau sa folosesc membru privat msg)
    friend ostream& operator<<(ostream& out, const ValidateException& ex);
};
ofstream& operator<<(ofstream& out,const ValidateException& ex);


class Validator {
public:
    static void validate(const Disciplina& d);
};



#endif //VALIDATOR_H
