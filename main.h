#ifndef MAIN_H
#define MAIN_H

#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function definitions

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

void init_library(Library *library);

#endif