#include <stdio.h>
#include "sqlite/sqlite3.h"

int main() {
    sqlite3 *db; //Deklaruje wskaźnik do struktury reprezentującej bazę danych SQLite.
    int rc = sqlite3_open("my_database.db", &db); //  Otwiera bazę danych o nazwie "my_database.db".
    // Funkcja sqlite3_open zwraca kod wyniku (rc), który informuje o powodzeniu lub błędzie otwarcia bazy danych.

    if (rc) {
        printf("Nie można otworzyć bazy danych: %s\n", sqlite3_errmsg(db));
        return 1;
    } else {
        printf("Baza danych otwarta poprawnie\n");
    }

    sqlite3_close(db); // Zamyka bazę danych.
    printf("Baza danych zamknięta\n");
    return 0;
}
