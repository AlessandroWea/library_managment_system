#include <stdio.h>

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