//
// Created by h on 3/8/24.
//

#ifndef SERVICE_H
#define SERVICE_H
#include "../Domain/lista.h"
#include "../Domain/medicament.h"
#include "../Validator/validator.h"
int add_medicament(Lista* list, int id,char* nume,float concentratie,int cantitate);
int modify_quantity(Lista *list, int id, int cantitate);
int modify_medicament(Lista* list, int id,char* nume,float concentratie );
int delete_all_stock(Lista* list,int id);
void sort(Lista *list,int (*functie)(Medicament* m1, Medicament* m2));
Lista filter_cantitate(Lista* list, int cantitate);
Lista filter_initiala(Lista* list, char initiala);
int verify_existence(Lista* list,char* nume);
int nume_cresc(Medicament* m1,Medicament* m2);
int nume_descresc(Medicament* m1,Medicament* m2);
int cantitate_crescator(Medicament* m1,Medicament* m2);
int cantitate_descrescator(Medicament* m1,Medicament* m2);
#endif //SERVICE_H
