#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

/*
LIBRARY MANAGMENT SYSTEM
    appearence:
---------------
Welcome!
books - to manage books
readers - to manage readers
main> smth
Managment section
add - to add
remove - to remove
back - to go back
books/readers> add
...does smth
books/readers>
-------------------
Problems:
1) Entering a lot of input makes more than 1 message happen
(books> [s*100] => N messages)

Functionality:
1) Books' functions
    - adding books
    - removing books
    - showing books
2) Readers' functions
    - include a reader
    - exclude a reader
    - show all the readers
    - select a reader to show his information

*/
enum {
    FALSE, TRUE
};

//main menu commands
#define MENU_UNDEFINED -1
#define MENU_BOOKS 1
#define MENU_READERS 2

//general menu commands
#define MENU_QUIT 0
#define MENU_GO_BACK 9

//book managmeent's menu commands
#define MENU_BOOKS_ADD 1
#define MENU_BOOKS_REMOVE 2

//reader managment's menu commands
#define MENU_READERS_ADD 1
#define MENU_READERS_REMOVE 2

//other useful constants
#define MAX_COMMAND_SIZE 100

#define MAX_BOOK_NAME_SIZE 100
#define MAX_BOOK_AUTHOR_NAME_SIZE 100

#define MAX_READER_FIRST_NAME_SIZE 50
#define MAX_READER_LAST_NAME_SIZE 50
#define MAX_READER_BOOKS_TAKEN_SIZE 10
#define MAX_STR_SIZE 100

#define MAX_LIBRARY_BOOKS_SIZE 100
#define MAX_LIBRARY_READERS_SIZE 100

#define DB_NAME "test.db"
#define BOOKS_TABLE_NAME "books"
#define READERS_TABLE_NAME "readers"

// structures

typedef struct _Book {
    char *name;
    char *author;
} Book;

typedef struct _Reader {
    char *first_name;
    char *last_name;
    int age;
    Book books_taken[MAX_READER_BOOKS_TAKEN_SIZE];
    char *_str_books_taken;
} Reader;

typedef struct _Library {
    Book books[MAX_LIBRARY_BOOKS_SIZE];
    Reader readers[MAX_LIBRARY_READERS_SIZE];
    int books_count;
    int readers_count;
} Library;

// function definitions

void show_main_menu();
void show_books_menu();
void show_readers_menu();

int get_choice();
int get_books_managment_choice();
int get_readers_managment_choice();

char* get_string(char *str, int size);

void books_managment();
void readers_managment();

void add_book();
void remove_book();
void show_book();

void add_reader();
void remove_reader();
void show_all_readers();

void get_library(Library *library);
void get_books(Library *library);
void get_readers(Library *library);

// for debug functions
void make_tables();
void add_some_data_to_tables(sqlite3 *db);

int main()
{
    int running = TRUE;
    Library library;
    library.books_count = 0;
    library.readers_count = 0;
    // get_library(&library);
    
    make_tables();
    
    show_main_menu();

    while(running == TRUE)
    {
        printf("main > ");
        int choice = get_choice();

        switch(choice)
        {
            case MENU_BOOKS:
                printf("Book managment!\n");
                books_managment();
                break;
            case MENU_READERS:
                printf("Reader managment\n");
                readers_managment();
                break;
            case MENU_QUIT:
                running = FALSE;
                printf("Bye!\n");
                break;
            case MENU_UNDEFINED:
                printf("This command is not available!\n");
                break;
            default:
                printf("How did you get here?\n");
                break;
        }
    }

    return 0;
}

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
                "BOOKS TEXT);";

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
                "INSERT INTO readers (FIRST_NAME, LAST_NAME, BOOKS) VALUES ('Sa','Ka','1');"\
            "INSERT INTO readers (FIRST_NAME, LAST_NAME, BOOKS) VALUES ('Se','Kan','1,2');";
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

void get_library(Library *library)
{
    get_books(library);
    get_readers(library);
}
//SELECT * FROM TableName;

void get_books(Library *library)
{
    sqlite3 *db;
    char *err_msg = 0;
    sqlite3_stmt *stmt;
    char sql[50] = "SELECT * FROM ";
    strcpy(sql,BOOKS_TABLE_NAME);

    int rc = sqlite3_open(DB_NAME,&db);

    if( rc != SQLITE_OK)
    {
        fprintf(stderr,"DEBUG: Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,0);

    if( rc != SQLITE_OK)
    {
        fprintf(stderr,"DEBUG: Failed to execute statement: %s\n",sqlite3_errmsg(db));
        return;
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
        
        library->books[library->books_count].name = (char*) malloc(sizeof(char)*strlen(tmp_name)+1);
        library->books[library->books_count].author = (char*) malloc(sizeof(char)*strlen(tmp_author)+1);

        strcpy(library->books[library->books_count].name, tmp_name);
        strcpy(library->books[library->books_count].author, tmp_author);

        library->books_count++;

        step = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void get_readers(Library *library)
{
    sqlite3 *db;
    char *err_msg;
    sqlite3_stmt *stmt;
    char sql[50] = "SELECT * FROM ";
    strcpy(sql,READERS_TABLE_NAME);

    int rc = sqlite3_open(DB_NAME,&db);

    if( rc != SQLITE_OK)
    {
        fprintf(stderr,"DEBUG: Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,0);

    if( rc != SQLITE_OK)
    {
        fprintf(stderr,"DEBUG: failed to execute statement: %s\n",sqlite3_errmgs(db));
        return;
    }

    int step = sqlite3_step(stmt);
    char tmp_first_name[MAX_READER_FIRST_NAME_SIZE];
    char tmp_last_name[MAX_READER_LAST_NAME_SIZE];
    char tmp_books[MAX_READER_BOOKS_TAKEN_SIZE];
    
}

void books_managment()
{
    int in_this = TRUE;
    show_books_menu();

    while(in_this)
    {
        printf("books> ");
        int choice = get_books_managment_choice();

        switch(choice)
        {
            case MENU_BOOKS_ADD:
                printf("Adding a book...\n");
                add_book();
                break;
            case MENU_BOOKS_REMOVE:
                printf("Removing a book...\n");
                remove_book();
                break;
            case MENU_GO_BACK:
                in_this = FALSE;
                break;
            case MENU_UNDEFINED:
                printf("This command is not defined!\n");
                break;
            default:
                printf("How did you get here?\n");
                break;
        }
    }
}

void add_book()
{
    
}

void remove_book()
{

}

void show_all_books()
{

}

void readers_managment()
{
    int in_this = TRUE;
    show_readers_menu();

    while(in_this)
    {
        printf("readers> ");
        int choice = get_readers_managment_choice();

        switch(choice)
        {
            case MENU_READERS_ADD:
                printf("Adding a reader...\n");
                break;
            case MENU_READERS_REMOVE:
                printf("Removing a reader...\n");
                break;
            case MENU_GO_BACK:
                in_this = FALSE;
                break;
            case MENU_UNDEFINED:
                printf("This command is not defined!\n");
                break;
            default:
                printf("How did you get here?\n");
                break;
        }
    }

}

void show_main_menu()
{
    printf("Welcome to LMS!\n");
    printf("books - to manage books\n");
    printf("readers - to manage readers\n");
    printf("quit - to quit\n");
}

void show_books_menu()
{
    printf("--- Books managment menu! ---\n");
    printf("add - to add a new book!\n");
    printf("remove - to remove a book!\n");
    printf("back - to go back to the main menu\n");
}

void show_readers_menu()
{
    printf("--- Readers managment menu! ---\n");
    printf("add - to include a reader!\n");
    printf("remove - to exclude a reader\n");
    printf("back - to go back to the main menu\n");
}

int get_choice()
{
    char choice_input[MAX_COMMAND_SIZE];
    int ret_val = MENU_UNDEFINED;

    get_string(choice_input,MAX_COMMAND_SIZE);

    if(!strcmp(choice_input,"books"))
    {
        ret_val = MENU_BOOKS;
    } else if(!strcmp(choice_input,"readers"))
    {
        ret_val = MENU_READERS;
    } else if(!strcmp(choice_input,"quit"))
    {
        ret_val = MENU_QUIT;
    }

    return ret_val;
}

char* get_string(char *str, int size)
{
    char *ret = fgets(str,size,stdin);
    char *find;

    if( (find = index(str,'\n')) != NULL)
    {
        *find = '\0';
    }

    return ret;
}

int get_books_managment_choice()
{
    char choice_input[MAX_COMMAND_SIZE];
    int ret_val = MENU_UNDEFINED;

    get_string(choice_input,MAX_COMMAND_SIZE);

    if(!strcmp(choice_input,"add"))
    {
        ret_val = MENU_BOOKS_ADD;
    } else if(!strcmp(choice_input,"remove"))
    {
        ret_val = MENU_BOOKS_REMOVE;
    } else if(!strcmp(choice_input,"back"))
    {
        ret_val = MENU_GO_BACK;
    }

    return ret_val;
}

int get_readers_managment_choice()
{
    char choice_input[MAX_COMMAND_SIZE];
    int ret_val = MENU_UNDEFINED;

    get_string(choice_input,MAX_COMMAND_SIZE);

    if(!strcmp(choice_input,"add"))
    {
        ret_val = MENU_READERS_ADD;
    } else if(!strcmp(choice_input,"remove"))
    {
        ret_val = MENU_READERS_REMOVE;
    } else if(!strcmp(choice_input,"back"))
    {
        ret_val = MENU_GO_BACK;
    }

    return ret_val;

}
