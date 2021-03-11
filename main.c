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
#include "main.h"
#include "db_interactions.h"

int main()
{
    int running = TRUE;
    Library library;
    library.books_count = 0;
    library.readers_count = 0;
    // init_library(&library);
    
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

void init_library(Library *library)
{
    get_books(library);
    get_readers(library);
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
