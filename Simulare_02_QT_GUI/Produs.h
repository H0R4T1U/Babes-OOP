//
// Created by horatiu on 5/19/24.
//

#ifndef SIMULARE_02_PRODUS_H
#define SIMULARE_02_PRODUS_H


#include <string>

class Produs {
private:
    const std::string nume;
    const std::string firma;
    float pret;
public:
    Produs(const std::string nume,const std::string firma,const float pret): nume{nume},firma{firma},pret{pret}{};
    ~Produs() = default;
    float getPret() const{
        return pret;
    }
    std::string getNume() const{
        return nume;
    }
    std::string getFirma() const{
        return nume;
    }
};

void testDomain();

#endif //SIMULARE_02_PRODUS_H
