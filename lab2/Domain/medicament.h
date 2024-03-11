//
// Created by h on 3/8/24.
//

#ifndef MEDICAMENT_H
#define MEDICAMENT_H
typedef struct {
    int id;
    char nume[50];
    float concentratie;
    int cantitate;
}Medicament;

int get_id(Medicament* m);
char* get_nume(Medicament* m);
float get_concentratie(Medicament* m);
int get_cantitate(Medicament* m);

void set_nume(Medicament* m, char* nume);
void set_concentratie(Medicament* m, float concentratie);
void set_cantitate(Medicament* m, int cantitate);
Medicament createMedicament(int id, char* nume,float concentratie,int cantitate);

#endif //MEDICAMENT_H
