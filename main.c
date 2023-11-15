#include <stdio.h>
#include "sqlite/sqlite3.h"
#include "databaseFunctions.h"

int main() {
    sqlite3 *db; //Deklaruje wskaźnik do struktury reprezentującej bazę danych SQLite.
    char *error_message = 0;  // Deklaruje wskaźnik na komunikat o błędzie SQLite
    int rc = sqlite3_open("my_database.db", &db); //  Otwiera bazę danych o nazwie "my_database.db".
    // Funkcja sqlite3_open zwraca kod wyniku (rc), który informuje o powodzeniu lub błędzie otwarcia bazy danych.

    checkIfIsAbleToOpen(rc, db);

    createTable(rc, db, error_message);

    PersonData person1 = {0, "Bartek Klenczi", 15};
    PersonData person2 = {1, "Klenczi Bartek", 16};

    //insertPersonData(db, &person1);
    //insertPersonData(db, &person2);


    int idToDelete = 1;

    // Usuń dane z tabeli na podstawie wartości id
    //deletePersonData(db, idToDelete);

    person1.name = "bartosz Klenczi";
    //updatePersonData(db, &person1);

    selectDatabase(rc, db, error_message);

    sqlite3_close(db); // Zamyka bazę danych.
    printf("Baza danych zamknięta\n");
    return 0;
}
