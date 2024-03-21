//
// Created by h on 3/10/24.
//
#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"


#include <ctype.h>
#include <stdio.h>

void print_main_menu() {
    printf("Meniu Principal\n");
    printf("1. Adauga Medicament\n");
    printf("2. Modifica Medicament\n");
    printf("3. Sterge stoc Medicament\n");
    printf("4. Afisare Medicamente Sortate\n");
    printf("5. Filtreaza Medicamente\n");
    printf("q. Iesire\n");

}
void print_sortare_menu() {
    printf("Meniu Sortari\n");
    printf("1.Sortare dupa nume crescator\n");
    printf("2.Sortare dupa nume Descrescator\n");
    printf("3. Sosrtare dupa cantitate Crescator\n");
    printf("4. Sosrtare dupa cantitate Descrescator\n");
}

void print_cresc_menu() {
    printf("Meniu Sortari\n");
    printf("1.Sortare crescatoare\n");
    printf("2. Sosrtare descrscatoare\n");
}
void print_filtrare_menu() {
    printf("Meniu Filtrari\n");
    printf("1. Filtrare dupa cantitate\n");
    printf("2. FIltrare dupa Initiala\n");
}

///  UI ADAUGARE MEDICAMENT
/// @param lista LISTA DE MEDICAMENTE
void adauga_medicament_ui(Lista* lista) {
    int id,cantitate;
    char nume[50];
    float concentratie;
    printf("id:");
    if(scanf("%d",&id) != 1) {
        printf("Inalid Input!\n");
        return;
    }
    clear();
    printf("nume:");
    scanf("%s",nume);
    getchar();
    modify_string(nume);
    int exist = verify_existence(lista,nume);
    if(exist == -1) {
        printf("concentratie:");
        if(scanf("%f",&concentratie) != 1) {
            printf("Inalid Input!\n");
            return;
        }
        printf("Cantitate:");
        if(scanf("%d",&cantitate) != 1) {
            printf("Inalid Input!\n");
            return;
        }
        if(add_medicament(lista,id,nume,concentratie,cantitate)) {
            printf("Medicament Adaugat cu succes!\n");
        }else {
            printf("Medicamentul nu a fost adaugat!\n");
        }
    }else {
        printf("Medicamentul exista deja!\nModificati cantitatea:");
        if(scanf("%d",&cantitate) != 1) {
            printf("Inalid Input!\n");
            return;
        }
        modify_quantity(lista,exist,cantitate);

    }

}

/// UI MODIFICARE MEDICAMENT
/// @param lista de medicamente
void modifica_medicament_ui(Lista* lista) {
    int id;
    char nume[50];
    float concentratie;
    printf("id:");
    if(scanf("%d",&id) != 1) {
        printf("INVALID INPUT\n");
        return;
    }
    clear();
    printf("nume:");
    scanf("%s",nume);
    getchar();
    modify_string(nume);
    printf("concentratie:");
    if(scanf("%f",&concentratie)!=1) {
        printf("INVALID INPUT\n");
        return;
    }
    if(modify_medicament(lista,id,nume,concentratie)) {
        printf("Medicament Modificat cu succes!\n");
    }else {
        printf("Medicamentu nu a putut fi modificat!\n");
    }
}

/// UI STERGERE MEDICAMENT
/// @param lista lista de medicamente
void sterge_medicament_ui(Lista* lista) {
    int id;
    printf("Id:");
    if(scanf("%d",&id)!=1) {
        printf("INVALID INPUT\n");
        return;
    }
    if(delete_all_stock(lista,id)) {
        printf("Stocul Medicamentului a fost Eliminat cu succes!\n");
    }else {
        printf("Stocul Medicamentului nu a fost eliminat!\n");
    }
}

/// Afiseaza lista de medicamente furnizata
/// @param lista lista de medicamente
void afisare_lista(Lista* lista) {
    Medicament* meds = get_medicamente(lista);
    int len = get_len(lista);

    for(int i =0 ; i<len;i++) {
        int id = get_id(&meds[i]);
        char* nume = get_nume(&meds[i]);
        float concentratie = get_concentratie(&meds[i]);
        int cantitate = get_cantitate(&meds[i]);
        printf("%d %s %.2f%% %d\n",id,nume,concentratie,cantitate);
    }
}

/// UI AFISARI CU SORTARI
/// @param lista lista de medicamente
void afisare_medicament_ui(Lista* lista) {
    int loop=1;
    char choice;
    print_sortare_menu();
    while(loop) {

        printf(":");

        choice = getchar();
        if(choice == '1') {
            sort(lista,nume_cresc);
            loop = 0;
        }else if(choice == '2') {
            sort(lista,nume_descresc);
            loop = 0;
        }else if(choice == '3') {
            sort(lista,cantitate_crescator);
            loop = 0;
        }else if(choice == '4') {
            sort(lista,cantitate_descrescator);
            loop = 0;
        }
    }
    afisare_lista(lista);

}

/// UI FILTRARE MEDICAMENT CU AFISARE
/// @param lista lista de medicamente
void filtreaza_medicament_ui(Lista* lista) {
    char choice;
    int loop=1;
    print_filtrare_menu();
    while(loop) {
        choice = getchar();
        if(choice == '1') {
            int cantitate;
            printf("Cantitate:");
            scanf("%d",&cantitate);
            Lista list = filter_cantitate(lista,cantitate);
            afisare_lista(&list);
            destructor(&list);
            loop = 0;
        }else if(choice == '2') {
            char initiala;
            printf("initiala:");
            clear();
            initiala = tolower(getchar());
            Lista list = filter_initiala(lista,initiala);
            afisare_lista(&list);
            destructor(&list);
            loop = 0;
        }
    }
}

/// Meniu Principal
/// @param lista de medicamente
/// @return 0 la inchidere
int main_menu(Lista* lista) {
    char choice;
    print_main_menu();
    while(1) {
        choice = getchar();
        if(choice == '1') {
            adauga_medicament_ui(lista);
            print_main_menu();
        }else if(choice == '2') {
            modifica_medicament_ui(lista);
            print_main_menu();
        }else if(choice == '3') {
            sterge_medicament_ui(lista);
            print_main_menu();
        }else if(choice == '4') {
            afisare_medicament_ui(lista);
            print_main_menu();
        }else if(choice == '5') {
            filtreaza_medicament_ui(lista);
            print_main_menu();
        }else if(choice == 'q') {
            return 0;
        }
    }
}