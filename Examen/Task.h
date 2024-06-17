//
// Created by horatiu on 6/16/24.
//

#ifndef EXAMEN_TASK_H
#define EXAMEN_TASK_H
#include <vector>
#include <string>
using namespace std;

// Clasa task
class Task {
private:
    // ID
    int id;
    // denumire
    string descriere;
    // lista programatori
    vector<string> programatori;
    // stare
    string stare;
public:
    // Constructor Task
    Task(int id, const string& descriere,const vector<string>& programatori,const string& stare):id{id},descriere{descriere},programatori{programatori},stare{stare}{};
    // Getter ID
    int getId()const{
        return id;
    }
    // getter Descriere
    string getDescriere()const{
        return descriere;
    }
    // Getter Programatori
    vector<string>& getProgramatori(){
        return programatori;
    };
    // Getter Stare
    string getStare()const{
        return stare;
    };

};

void testDomain();

#endif //EXAMEN_TASK_H
