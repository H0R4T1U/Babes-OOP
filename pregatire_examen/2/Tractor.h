//
// Created by horatiu on 6/14/24.
//

#ifndef INC_2_TRACTOR_H
#define INC_2_TRACTOR_H
#include <string>

using namespace std;

class Tractor {
private:
    int id;
    string denumire;
    string tip;
    int roti;
public:
    // COnstructor tractor
    Tractor(int id, const string& denumire, const string& tip, int roti): id{id},denumire{denumire},tip{tip},roti{roti}{};
    // Getter ID
    int getId()const{
        return id;
    }
    // Getter Denumire
    string getDenumire()const{
        return denumire;
    }
    // Getter TIP
    string getTip()const{
        return tip;
    }
    // Getter Roti
    int getRoti()const{
        return roti;
    }

};
// Teste pt domain
void testDomain();

#endif //INC_2_TRACTOR_H
