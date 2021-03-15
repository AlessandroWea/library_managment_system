#ifndef LINKED_LIST
#define LINKED_LIST

typedef enum _LIST_TYPE {
    BOOKS_LIST, READERS_LIST
} LIST_TYPE;

typedef struct _Node {
    struct _Node *prev;
    struct _Node *next;
    void *data;
} Node;

typedef struct _List {
    Node *head;
    Node *tail;
    int size;
    LIST_TYPE type;
} List;

void list_init(List *list, LIST_TYPE type);
void list_push_back(List *list, void *data);
void list_push_front(List *list);
void list_pop_back(List *list);
void list_pop_front(List *list);
void list_remove(List *list);
void list_find(List *list);
void list_free(List *list);

#endif