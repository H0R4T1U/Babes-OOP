//
// Created by h on 3/8/24.
//

#include "validator.h"

#include <stdio.h>

/// Valideaza un medicament creat
/// @param medicament medicamentul de verificat
/// @param medicamente lista de medicamente
/// @return 0 sau 1 in functie daca medicamentul este valid sau nu
int validator(Medicament medicament,Lista* medicamente) {
    int err = 0;
    if(strcmp(get_nume(&medicament), "") == 0) {
        printf("Nume invalid!\n");
        err = 1;
    }
    if(get_concentratie(&medicament) > 100) {
        printf("Concentratie invalida!\n");
        err = 1;
    }
    int id_med = get_id(&medicament);
    int len = get_len(medicamente);
    Medicament* meds = get_medicamente(medicamente);
    for(int i = 0 ; i<=len;i++) {
        if(id_med == get_id(&meds[i])) {
            printf("ID-UL Exista deja!\n");
            err = 1;
        }
        if(strcmp(get_nume(&medicament),get_nume(&meds[i]))== 0) {
            printf("Medicamentul exista deja!\n");
            err = 1;
        }
    }



    if(err) {
        return 0;
    }
    return 1;
}
