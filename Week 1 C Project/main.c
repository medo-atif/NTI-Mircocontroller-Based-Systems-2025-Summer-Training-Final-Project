#include <stdio.h>
#include <stdint.h>
#include "structs.h"
#include "MyLib.h"

uint8_t loops_index = 0;
uint8_t loops_index2 = 0;

int main() {

    uint8_t choice = 0;  
    Book_t books[100] = {0};

    do{
        printf("+----------------------+\n"
                "| 1. Add Book          |\n| 2. Display All Books |\n| 3. "
                "Search Book       |\n| 4. Delete Book       |\n| 5. "
                "Update Status     |\n| 6. Exit              |"
                "\n+----------------------+"
                "\nEnter Your selection: ");
        scanf("%d", &choice);
        printf("--------------------------------------\n");
        
        switch (choice) {
            case AddBook: {
                Add_Book(books);
                break;
            }
            case DisplayAllBooks: {
                Display_All_Books(books);
                break;
            }
            case SearchBook:
                search_by_ID(books);
                break;
            case DeleteBook: 
                Delete_Books(books);
                break;
            case UpdateStatus:
                Update_Status(books);
                break;
        }
    } while (choice != Exist);

    return 0;
}
