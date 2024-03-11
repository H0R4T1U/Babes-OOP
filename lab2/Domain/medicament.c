//
// Created by h on 3/8/24.
//

#include "medicament.h"
#include <string.h>

/// Getter id
/// @param m medicament
/// @return id medicament
int get_id(Medicament* m ) {
    return m->id;
}
/// Getter nume
/// @param m medicament
/// @return nume medicament
char* get_nume(Medicament* m) {
    return m->nume;
}
/// Getter concentratie
/// @param m medicament
/// @return concentratie medicament
float get_concentratie(Medicament* m) {
    return m->concentratie;
}
/// Getter cantitate
/// @param m medicament
/// @return cantitate medicament
int get_cantitate(Medicament* m ) {
    return m->cantitate;
}

/// Setter nume
/// @param m medicament
/// @param nume nume nou
void set_nume(Medicament* m,char* nume) {
    strncpy(m->nume,nume,50);
}

/// Setter concentratie
/// @param m medicament
/// @param concentratie concentratie noua
void set_concentratie(Medicament*m, float concentratie){
    m->concentratie = concentratie;
}

/// Setter cantitate
/// @param m medicament
/// @param cantitate cantitate noua
void set_cantitate(Medicament* m, int cantitate) {
    m->cantitate = cantitate;
}

/// Creaza medicament
/// @param id  id medicament
/// @param nume nume medicament
/// @param concentratie concentratie medicament
/// @param cantitate cantitate medicament
/// @return medicament creat
Medicament createMedicament(int id, char* nume,float concentratie,int cantitate){
    Medicament m;
    m.id = id;
    set_nume(&m,nume);
    set_concentratie(&m,concentratie);
    set_cantitate(&m, cantitate);

    return m;
}