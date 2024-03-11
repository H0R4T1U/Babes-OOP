//
// Created by h on 3/10/24.
//

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
    printf("1.Sortare dupa nume\n");
    printf("2. Sosrtare dupa cantitate\n");
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
    int nume=0,cantitate=0,ordine,loop=1;
    char choice,crescator;
    print_sortare_menu();
    while(loop) {


        printf(":");

        choice = getchar();
        if(choice == '1') {
            nume = 1;
            loop = 0;
        }else if(choice == '2') {
            cantitate = 1;
            loop = 0;
        }
    }
    loop = 1;
    print_cresc_menu();
    while(loop) {

        printf(":");

        crescator = getchar();
        if(crescator == '1') {
            ordine = 1;
            loop = 0;
        }else if(crescator == '2') {
            ordine = 0;
            loop = 0;
        }
    }
    sort(lista,nume,cantitate,ordine);
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
            loop = 0;
        }else if(choice == '2') {
            char initiala;
            printf("initiala:");
            clear();
            initiala = tolower(getchar());
            Lista list = filter_initiala(lista,initiala);
            afisare_lista(&list);
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