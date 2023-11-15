#ifndef DATABASEFUNCTIONS_H
#define DATABASEFUNCTIONS_H

#include <stdio.h>
#include "PersonData.h"

// Funkcja pomocnicza do obsługi wyników zapytania SELECT
int callback(void *NotUsed, int liczbaKolumn, char **wartosciWKolumnieDlaAktualnegoWiersza, char **nazwyKolumn) {
    // Iteruje przez kolumny wyniku zapytania SELECT i wypisuje je na ekranie
    for (int i = 0; i < liczbaKolumn; i++) {
        printf("%s = %s\n", nazwyKolumn[i], wartosciWKolumnieDlaAktualnegoWiersza[i] ? wartosciWKolumnieDlaAktualnegoWiersza[i] : "NULL");
    }
    printf("\n");
    return 0;  // Zwraca 0, aby kontynuować przetwarzanie wyników zapytania SELECT
}

// Funkcja do wykonania zapytania SELECT, czyli wypisania elementów bazy danych
int selectDatabase(int rc, sqlite3 *db, char *error_message){
    // Usuwanie cache, zapobiega potencjalnemu wyświetleniu się nieistniejących już elementów
    sqlite3_db_cacheflush(db);

    // Odczytaj dane z tabeli za pomocą zapytania SELECT
    const char *select_data_sql = "SELECT * FROM Person;";
    rc = sqlite3_exec(db, select_data_sql, callback, 0, &error_message);

    if (rc != SQLITE_OK) {
    printf("Błąd podczas odczytywania danych: %s\n", error_message);
    sqlite3_free(error_message);
    return 1;
}}

// Funkcja do wstawiania danych do tabeli
int insertPersonData(sqlite3 *db, const PersonData *person) {
    const char *insert_data_sql = "INSERT INTO Person (id, name, age) VALUES (?, ?, ?);";
    sqlite3_stmt *stmt;

    // Przygotuj polecenie SQL
    int rc = sqlite3_prepare_v2(db, insert_data_sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("Błąd podczas przygotowywania zapytania SQL: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Bindowanie wartości do zapytania
    sqlite3_bind_int(stmt, 1, person->id);
    sqlite3_bind_text(stmt, 2, person->name, -1, SQLITE_STATIC); //-1 oznacza że sqlite ma samo obliczyć długość textu
    sqlite3_bind_int(stmt, 3, person->age);

    // Wykonaj zapytanie
    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE) {
        printf("Błąd podczas wstawiania danych: %s\n", sqlite3_errmsg(db));
        return 1;
    } else {
        printf("Dane wstawione poprawnie\n");
    }

    // Zwolnij zasoby
    sqlite3_finalize(stmt);

    // Usuwanie cache, zapobiega potencjalnemu wyświetleniu się nieistniejących już elementów
    sqlite3_db_cacheflush(db);

    return 0;
}

// Funkcja do usuwania danych z tabeli na podstawie wartości id
int deletePersonData(sqlite3 *db, int id) {
    const char *delete_data_sql = "DELETE FROM Person WHERE id = ?;";
    sqlite3_stmt *stmt;

    // Przygotuj polecenie SQL
    int rc = sqlite3_prepare_v2(db, delete_data_sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("Błąd podczas przygotowywania zapytania SQL: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Bindowanie wartości do zapytania
    sqlite3_bind_int(stmt, 1, id);

    // Wykonaj zapytanie
    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE) {
        printf("Błąd podczas usuwania danych: %s\n", sqlite3_errmsg(db));
        return 1;
    } else {
        printf("Dane usunięte poprawnie\n");
    }

    // Zwolnij zasoby
    sqlite3_finalize(stmt);

    // Usuwanie cache, zapobiega potencjalnemu wyświetleniu się nieistniejących już elementów
    sqlite3_db_cacheflush(db);

    return 0;
}

// Funkcja do aktualizacji danych w tabeli
int updatePersonData(sqlite3 *db, const PersonData *person) {
    const char *update_data_sql = "UPDATE Person SET name = ?, age = ? WHERE id = ?;";
    sqlite3_stmt *stmt;

    // Przygotuj polecenie SQL
    int rc = sqlite3_prepare_v2(db, update_data_sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("Błąd podczas przygotowywania zapytania SQL: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Bindowanie wartości do zapytania
    sqlite3_bind_text(stmt, 1, person->name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, person->age);
    sqlite3_bind_int(stmt, 3, person->id);

    // Wykonaj zapytanie
    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE) {
        printf("Błąd podczas aktualizacji danych: %s\n", sqlite3_errmsg(db));
        return 1;
    } else {
        printf("Dane zaktualizowane poprawnie\n");
    }

    // Zwolnij zasoby
    sqlite3_finalize(stmt);

    // Usuwanie cache, zapobiega potencjalnemu wyświetleniu się nieistniejących już elementów
    sqlite3_db_cacheflush(db);

    return 0;
}

int createTable(int rc, sqlite3 *db, char *error_message){
    // Tworzy tabelę (jeśli nie istnieje)
    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS Person (id INT, name TEXT, age INT);"; // TU SIE USTAWIA RZECZY I ICH TYPY W TABELI
    rc = sqlite3_exec(db, create_table_sql, 0, 0, &error_message);

    // Sprawdza, czy tworzenie tabeli zakończyło się sukcesem
    if (rc != SQLITE_OK) {
        printf("Błąd podczas tworzenia tabeli: %s\n", error_message);
        sqlite3_free(error_message);
        return 1;
    } else {
        printf("Tabela utworzona poprawnie\n");
    }
    return 0;
}

int checkIfIsAbleToOpen(int rc, sqlite3 *db){
    if (rc) {
        printf("Nie można otworzyć bazy danych: %s\n", sqlite3_errmsg(db));
        return 1;
    } else {
        printf("Baza danych otwarta poprawnie\n");
    }
    return 0;
}

#endif