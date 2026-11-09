#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdint.h>

typedef enum {
 AddBook = 1,
 DisplayAllBooks,
 SearchBook,
 DeleteBook,
 UpdateStatus,
 Exist
} menu_option;

typedef struct 
{
    char Title[20];
    char Author[15];
    uint16_t ID;
    uint16_t Year;
    uint8_t Status;

} Book_t;

#endif