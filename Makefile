CC=gcc

LIBS=-lsqlite3

all:
	$(CC) main.c menus.c db_interactions.c $(LIBS)
