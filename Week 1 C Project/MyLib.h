#ifndef MYLIB_H
#define MYLIB_H

#include "structs.h"

void Add_Book(Book_t *Array);
void Display_All_Books(Book_t *Array);
void search_by_ID(Book_t *Array);
uint8_t count_digits (uint16_t ID);
void Delete_Books(Book_t *Array);
void Update_Status(Book_t *Array);

#endif