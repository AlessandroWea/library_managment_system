#include "db_interactions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void make_tables()
{
    sqlite3 *db;
    char *err_msg = 0;
    int rc;
    char *sql = "DROP TABLE IF EXISTS books;" \
                "DROP TABLE IF EXISTS readers;"\
                \
                "CREATE TABLE books(" \
                "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
                "NAME TEXT NOT NULL," \
                "AUTHOR TEXT NOT NULL);" \
                \
                "CREATE TABLE readers("\
                "ID INTEGER PRIMARY KEY AUTOINCREMENT,"\
                "FIRST_NAME TEXT NOT NULL,"\
                "LAST_NAME TEXT NOT NULL,"\
                "AGE INTEGER NOT NULL,"\
                "BOOKS_TAKEN TEXT,"\
                "COUNT_BOOKS_TAKEN INTEGER NOT NULL);";

    if( (rc = sqlite3_open(DB_NAME,&db) ) )
    {
        fprintf(stderr,"DEBUG: Cannot open database: %s\n",sqlite3_errmsg(db));
        exit(1);
    }
    else
    {
        fprintf(stdout,"DEBUG: Opened database successfully!\n");
    }

    rc = sqlite3_exec(db,sql,0,0,&err_msg);

    if( rc != SQLITE_OK)
    {
        fprintf(stderr,"DEBUG: SQL Error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    else
    {
        fprintf(stdout, "DEBUG: Table created successfully!\n");
    }
    
    add_some_data_to_tables(db);

    sqlite3_close(db);
}

void add_some_data_to_tables(sqlite3 *db)
{
    char *sql = "INSERT INTO books (NAME,AUTHOR) VALUES ('first','Sasha Ge');"\
                "INSERT INTO books (NAME,AUTHOR) VALUES ('second','Sasha Ge');"\
                "INSERT INTO readers (FIRST_NAME, LAST_NAME, AGE, BOOKS_TAKEN, COUNT_BOOKS_TAKEN) VALUES ('Sa','Ka',22,'1',1);"\
            "INSERT INTO readers (FIRST_NAME, LAST_NAME, BOOKS) VALUES ('Se','Kan',23,'1,2',2);";
    char *err_msg = 0;

    int rc = sqlite3_exec(db,sql,0,0,&err_msg);

    if( rc != SQLITE_OK)
    {
        fprintf(stderr,"DEBUG: SQL Error: %s\n",err_msg);
        sqlite3_free(err_msg);
    }
    else
    {
        fprintf(stdout,"DEBUG: Records created successfully!\n");
    }
}

int get_books(Library *library)
{
    sqlite3 *db;
    char *err_msg = 0;
    sqlite3_stmt *stmt;
    char sql[50] = "SELECT * FROM ";
    strcpy(sql,BOOKS_TABLE_NAME);
    strcpy(sql, ";");

    int rc = sqlite3_open(DB_NAME,&db);

    if( rc != SQLITE_OK)
    {
        fprintf(stderr,"DEBUG: Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,0);

    if( rc != SQLITE_OK)
    {
        fprintf(stderr,"DEBUG: Failed to execute statement: %s\n",sqlite3_errmsg(db));
        return 1;
    }

    int step = sqlite3_step(stmt);
    char tmp_name[MAX_BOOK_NAME_SIZE];
    char tmp_author[MAX_BOOK_AUTHOR_NAME_SIZE];

    while( step == SQLITE_ROW )
    {
        //debug
        fprintf(stdout,"DEBUG: book name: %s\n",sqlite3_column_text(stmt,1));
        fprintf(stdout,"DEBUG:: book author: %s\n",sqlite3_column_text(stmt,2));

        strcpy(tmp_name, sqlite3_column_text(stmt,1));
        strcpy(tmp_author, sqlite3_column_text(stmt,2));
        library->books[library->books_count].id = sqlite3_column_int(stmt,0);

        library->books[library->books_count].name = (char*) malloc(sizeof(char)*strlen(tmp_name)+1);
        library->books[library->books_count].author = (char*) malloc(sizeof(char)*strlen(tmp_author)+1);

        strcpy(library->books[library->books_count].name, tmp_name);
        strcpy(library->books[library->books_count].author, tmp_author);

        library->books_count++;

        step = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

int get_readers(Library *library)
{
    sqlite3 *db;
    char *err_msg;
    sqlite3_stmt *stmt;
    char sql[50] = "SELECT * FROM ";
    strcpy(sql,READERS_TABLE_NAME);
    strcpy(sql, ";");

    int rc = sqlite3_open(DB_NAME,&db);

    if( rc != SQLITE_OK)
    {
        fprintf(stderr,"DEBUG: Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,0);

    if( rc != SQLITE_OK)
    {
        fprintf(stderr,"DEBUG: failed to execute statement: %s\n",sqlite3_errmsg(db));
        return 1;
    }

    int step = sqlite3_step(stmt);
    char tmp_first_name[MAX_READER_FIRST_NAME_SIZE];
    char tmp_last_name[MAX_READER_LAST_NAME_SIZE];
    char tmp_books_taken[MAX_READER_BOOKS_TAKEN_SIZE];

    // while(step == SQLITE_ROW)
    // {

    // }

    return 0;
}