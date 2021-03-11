#ifndef DB_INTERACTIONS_H
#define DB_INTERACTIONS_H

#include "definitions.h"
#include <sqlite3.h>

// for debug functions
void make_tables();
void add_some_data_to_tables(sqlite3 *db);

void get_books(Library *library);
void get_readers(Library *library);

#endif