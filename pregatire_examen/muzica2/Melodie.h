//
// Created by horatiu on 6/15/24.
//

#ifndef MUZICA2_MELODIE_H
#define MUZICA2_MELODIE_H
#include <string>
using namespace std;

class Melodie {
private:
    // parametri id, artist, titlu, tip
    int id;
    string artist;
    string titlu;
    string tip;

public:
    // constructor melodie
    Melodie(int id, const string& name,const string& artist, const string& tip): id{id},titlu{name},artist{artist},tip{tip}{};
    // destructor melodie
    ~Melodie() = default;
    // getter id
    const int getId()const{
        return id;
    }
    // getter titlu
    const string& getTitlu() const{
        return titlu;
    }
    // getter artist
    const string& getArtist()const{
        return artist;
    }
    // getter tip
    const string& getTip()const{
        return tip;
    }

};
// teste domain
void testDomain();


#endif //MUZICA2_MELODIE_H
