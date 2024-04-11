
#include "Domain/lista.h"
#include "Tests/tests.h"
#include "Ui/Menu.h"

/*
 *Cerinte generale

Creati o aplicatie modulara in C.
Se cere interfata utilizator de tip consola.
Datele introduse de utilizator trebuie validate.
Folositi athitectura stratificata.
Folositi dezvoltare dirijata de teste (Test Driven Development)
Fiecare metoda din aplicatie trebuie specificat si testat.
Implementati vector dinamic pentru lucru cu liste:
    - in prima saptamana puteti folosi reprezentarea cu un struct ( un vector static si lungime in el)
    - pana in saptamana 2 trebuie folosit alocare dinamica (sa acomodeze oricate elemente)
Timp de lucru 2 saptamani.


2 Gestiune farmacie

Administratorul unei facatie care permite gestiunea stocului din farmacie.
Fiecare medicament din stoc are un cod unic, un nume,concentratie, cantitate disponibila in stoc.
Creati o aplicatie care permite:
 a) Adaugare de noi medicamente. Daca medicamentul este deja in stoc trebuie actualizat cantitatea
 b) Actualizare medicamente (modificare nume, concentratie pentru un medicament din stoc)
 c) Stergerea intregului zstoc dintr-un medicament dat
 d) Vizualizare medicamente din stoc, ordonat dupa nume, cantitate (crescator/descrescator)
 e) Vizualizare lista de medicamente filtrate dupa un criteriu. Medicamente unde stocul disponibil este
mai mic decat o valoare data; medicamente cu numele incepand cu o litera data.
*/

int main() {
    test_all();
    Lista list = createLista();
    //main_menu(&list);
    return 0;
}