#include <stdio.h>
#include <math.h>
#include "structs.h"

#define num_of_books 100

extern uint8_t loops_index;
extern uint8_t loops_index2;

void Add_Book(Book_t *Array) {
    uint16_t temp_id = 0;
    uint8_t input_ID_flag = 0;

    for (loops_index = 0; loops_index < num_of_books; loops_index++) {
        if (Array[loops_index].ID == 0) {
            printf("|| Enter Book Details \n");
            
            do{
                printf("Enter Books Id: ");
                scanf("%d", &temp_id);
                
                input_ID_flag = 0;
                if (temp_id == 0) {
                    printf("You can't use ZERO as an ID, please enter a different id\n");
                    input_ID_flag = 1;
                }
                
                for ( loops_index2 = 0; loops_index2 < num_of_books; loops_index2++) {
                    if ( temp_id == Array[loops_index2].ID && temp_id != 0) {
                        printf("This is already in use, please enter a different id\n");
                        input_ID_flag = 1;
                        break;
                    } 
                }
                Array[loops_index].ID = temp_id;
            } while(input_ID_flag == 1);
            
            while (getchar() != '\n');
            printf("Enter Books Title: ");
            fgets(Array[loops_index].Title, 20, stdin);
            printf("Enter Books Author: ");
            fgets(Array[loops_index].Author, sizeof(Array[loops_index].Author), stdin);
            printf("Enter Books Year: ");
            scanf("%d", &Array[loops_index].Year);
            printf("Enter Books Status (1 for Available/0 for Borrowed):\n>> ");
            scanf("%d", &Array[loops_index].Status);
            printf("|| The book has been added successfully \n");
            printf("--------------------------------------\n");
            
            return;
        }
    }
    printf("The Library is full, You can't add additional books");
}

void Display_All_Books(Book_t *Array) {
    int no_books_flag = 0;
    for (loops_index = 0; loops_index < num_of_books; loops_index++) {
        if ( Array[loops_index].ID != 0) {
            no_books_flag = 1;
            printf("ID: %d\n", Array[loops_index].ID);
            printf("title: %s", Array[loops_index].Title);
            printf("Author: %s", Array[loops_index].Author);
            printf("Year: %d\n", Array[loops_index].Year);
            if (Array[loops_index].Status) {
                printf("Status: Available\n");
            }else {
                printf("Status: Borrowed\n");
            }
            printf("--------------------------------------\n");
        }
    }
    if (!no_books_flag) {
        printf("|| There is no Books in the library yet.\n");
        printf("--------------------------------------\n");
    }
}

uint8_t count_digits (uint16_t ID) {
    uint8_t count = 0;
    do {
        ID = ID / 10;
        count++;
    } while (ID != 0);
    return count;
}

void search_by_ID(Book_t *Array){
    uint16_t search_value = 0;
    uint16_t ID_length = 0;
    float new_bookID = 0;
    uint8_t no_books_flag = 0;
    printf("Enter the book ID you want to search for: ");
    scanf("%d", &search_value);
    printf("--------------------------------------\n");
    uint16_t search_value_length = count_digits (search_value);
    
    for (loops_index = 0; loops_index < num_of_books; loops_index++) {
        if ( Array[loops_index].ID != 0) {
            ID_length = count_digits (Array[loops_index].ID);
            new_bookID = Array[loops_index].ID / pow(10, (ID_length - search_value_length)); // slice of ID same length as entered ID
            if ((int)new_bookID == search_value) {
                printf("ID: %d\n", Array[loops_index].ID);
                printf("Title: %s", Array[loops_index].Title);
                printf("Author: %s", Array[loops_index].Author);
                printf("Year: %d \n", Array[loops_index].Year);
                if (Array[loops_index].Status) {
                    printf("Status: Available\n");
                }else {
                    printf("Status: Borrowed\n");
                }
                no_books_flag = 1;
                printf("--------------------------------------\n");
            } 
        }
    }
    if (!no_books_flag) {
        printf("|| There is no book with this ID\n");
        printf("--------------------------------------\n");
    }
}

void Delete_Books(Book_t *Array){
    uint16_t ID = 0;
    printf("Enter the book ID you want to delete: ");
    scanf("%d", &ID);
    printf("--------------------------------------\n");
    for (loops_index = 0; loops_index < num_of_books; loops_index++) {
        if ( Array[loops_index].ID == ID && Array[loops_index].ID != 0 ) {
            Array[loops_index].ID = 0;
            printf("|| The book was succesfully deleted.\n"
                "--------------------------------------\n");
            return;
        }    
    }
    printf("|| There is no book with this ID\n");
}

void Update_Status(Book_t *Array) {
    uint16_t ID = 0;
    uint8_t confirm = 'n';
    printf("Enter the book ID you want to change its status: ");
    scanf("%d", &ID);
    printf("--------------------------------------\n");
    for (loops_index = 0; loops_index < num_of_books; loops_index++) {
        if ( Array[loops_index].ID == ID && Array[loops_index].ID != 0 ) {
            if (Array[loops_index].Status) {
                printf("This books is Available.\n");
                printf("Are you sure you want to change its status to Borrowed\n(Y/N)>> ");
                scanf(" %c", &confirm);
                if ( confirm == 'y' || confirm == 'Y') {Array[loops_index].Status = 0;}
                printf("|| The book status has been changed to Borrowed\n");
                return;
            }else {
                printf("This books is Borrowed.\n");
                printf("Are you sure you want to change its status to Available?\n(Y/N)>> ");
                scanf(" %c", &confirm);
                if ( confirm == 'y' || confirm == 'Y') {Array[loops_index].Status = 1;}
                printf("|| The book status has been changed to Available\n");
                return;
            }
        }
    }
    printf("|| There is no book with this ID\n");
}

/* I Could have implement print book details funtion; because I could 
used it in every other function, but unfortunately no time.
*/
// This code is absolutely unreadable Ik Ik, but if it works don't touch it.
