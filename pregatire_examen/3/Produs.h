//
// Created by horatiu on 6/14/24.
//

#ifndef INC_3_PRODUS_H
#define INC_3_PRODUS_H
#include <string>
using namespace std;

class Produs {
private:
    int id;
    string nume;
    string tip;
    double pret;
public:
    Produs(int id, const string& nume, const string& tip, double pret): id{id},nume{nume},tip{tip},pret{pret}{};
    // getter id
    int getId() const{
        return id;
    }
    // getter nume
    string getNume()const{
        return nume;
    }
    // getter tip
    string getTip()const{
        return tip;
    }
    // getter pret
    double getPret()const{
        return pret;
    }
};

void testDomain();

#endif //INC_3_PRODUS_H
