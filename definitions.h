#ifndef DEFINITIONS_H
#define DEFINITIONS_H

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
#define MAX_READER_BOOKS_TAKEN_COUNT 4
#define MAX_STR_SIZE 100

#define MAX_LIBRARY_BOOKS_SIZE 100
#define MAX_LIBRARY_READERS_SIZE 100

#define DB_NAME "test.db"
#define BOOKS_TABLE_NAME "books"
#define READERS_TABLE_NAME "readers"

// structures

typedef struct _Book {
    int id;
    char *name;
    char *author;
} Book;

typedef struct _Reader {
    int id;
    char *first_name;
    char *last_name;
    int age;
    char *_str_books_taken;
    int count_books_taken;
} Reader;

typedef struct _Library {
    Book books[MAX_LIBRARY_BOOKS_SIZE];
    Reader readers[MAX_LIBRARY_READERS_SIZE];
    int books_count;
    int readers_count;
} Library;

#endif