#ifndef PERSONDATA_H
#define PERSONDATA_H
#include "sqlite/sqlite3.h"

// Deklaracja struktury
typedef struct {
    int id;
    const char *name;
    int age;
} PersonData;

int callback(void *NotUsed, int liczbaKolumn, char **wartosciWKolumnieDlaAktualnegoWiersza, char **nazwyKolumn);
int selectDatabase(int rc, sqlite3 *db, char *error_message);
int insertPersonData(sqlite3 *db, const PersonData *person);
int deletePersonData(sqlite3 *db, int id);
int createTable(int rc, sqlite3 *db, char *error_message);
int checkIfIsAbleToOpen(int rc, sqlite3 *db);

#endif // PERSONDATA_H
