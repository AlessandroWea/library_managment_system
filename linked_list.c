#include "linked_list.h"

#define TEST

#ifdef TEST

#include "definitions.h"

int main()
{
    List *book_list;
    Book book;
    book.name = "Alice in Wonderland";
    book.author = "IdontRemember";
    book.id = 1;

    list_init(book_list, BOOKS_LIST);

    list_push_back(book_list, &book);

    list_free(book_list);
}
#endif

void list_init(List *list, LIST_TYPE type)
{
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->type = type;
}

void list_push_back(List *list, void *data)
{
    
}

void list_free(List *list)
{
    // free memory
}
