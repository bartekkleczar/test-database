cmake_minimum_required(VERSION 3.26)
project(test_baza_danych C)

set(CMAKE_C_STANDARD 23)

set(SQLITE_SRC_DIR ${CMAKE_SOURCE_DIR}/sqlite)

add_library(sqlite3 STATIC ${SQLITE_SRC_DIR}/sqlite3.c)
target_include_directories(sqlite3 PUBLIC ${SQLITE_SRC_DIR}/sqlite)

add_executable(test_baza_danych main.c
        databaseFunctions.h
        PersonData.h)
target_link_libraries(test_baza_danych PRIVATE sqlite3)
