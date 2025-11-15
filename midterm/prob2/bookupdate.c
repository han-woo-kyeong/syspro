#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h> 

struct book {
	int id;
	char bookname[10];
	char author[10];
	int year;
	int numofborrow;
	char borrow[6];
};

#define START_ID 1 

int main(int argc, char *argv[]){
    int fd;
    int operation_type; 
    int book_id;
    
    struct book record; 
    
    if (argc < 2) {
        fprintf(stderr, "How to use : %s <filename>\n", argv[0]);
        exit(1);
    }
    
    if ((fd = open(argv[1], O_RDWR)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    do {
        printf("\n--bookupdate--\n");
        printf("0 bookID: borrow book, 1 bookID: return book ) ");
        
        if (scanf("%d %d", &operation_type, &book_id) != 2) {
            printf("Input Error: Invalid input format. Please try again.\n");
            while (getchar() != '\n');
            continue;
        }

        if (operation_type != 0 && operation_type != 1) {
             printf("Input Error: Operation type must be 0 (borrow) or 1 (return).\n");
             continue;
        }

        if (lseek(fd, (long)(book_id - START_ID) * sizeof(record), SEEK_SET) == -1) {
            fprintf(stderr, "Error: lseek failed for Book ID %d.\n", book_id);
            continue;
        }

        if (read(fd, (char *)&record, sizeof(record)) <= 0) {
            fprintf(stderr, "Error: Could not read record for Book ID %d. (Does not exist)\n", book_id);
            continue;
        }
        
        if (operation_type == 0) {
            if (strcmp(record.borrow, "False") != 0) { 
                printf("You cannot borrow below book since it has been booked.\n");
                printf("id %10s %12s %6s %12s %8s\n", "bookname", "author", "year", "numofborrow", "borrow"); 
                printf("%2d %10s %12s %6d %12d %8s\n",
                       record.id,
                       record.bookname,
                       record.author,
                       record.year,
                       record.numofborrow, 
                       record.borrow);
            } else {
                printf("You've got bellow book..\n");
                
                strncpy(record.borrow, "True", 6); 
                record.numofborrow++;
                
                lseek(fd, (long)-sizeof(record), SEEK_CUR); 
                
                if (write(fd, (char *)&record, sizeof(record)) != sizeof(record)) {
                    perror("write error");
                    continue; 
                }
                
                printf("id %10s %12s %6s %12s %8s\n", "bookname", "author", "year", "numofborrow", "borrow");
                printf("%2d %10s %12s %6d %12d %8s\n",
                       record.id,
                       record.bookname,
                       record.author,
                       record.year,
                       record.numofborrow, 
                       record.borrow);
            }
        } 
        
        else if (operation_type == 1) {
            if (strcmp(record.borrow, "True") != 0) {
                 printf("This book is already returned or was never borrowed.\n");
                 printf("id %10s %12s %6s %12s %8s\n", "bookname", "author", "year", "numofborrow", "borrow");
                 printf("%2d %10s %12s %6d %12d %8s\n",
                        record.id,
                        record.bookname,
                        record.author,
                        record.year,
                        record.numofborrow, 
                        record.borrow);
            } else {
                printf("You've returned bellow book..\n");
                
                strncpy(record.borrow, "False", 6);
                
                lseek(fd, (long)-sizeof(record), SEEK_CUR); 
                
                if (write(fd, (char *)&record, sizeof(record)) != sizeof(record)) {
                    perror("write error");
                    continue;
                }
                
                printf("id %10s %12s %6s %12s %8s\n", "bookname", "author", "year", "numofborrow", "borrow");
                printf("%2d %10s %12s %6d %12d %8s\n",
                       record.id,
                       record.bookname,
                       record.author,
                       record.year,
                       record.numofborrow, 
                       record.borrow);
            }
        }
    
    } while(1);

    close(fd);
    exit(0);
}
