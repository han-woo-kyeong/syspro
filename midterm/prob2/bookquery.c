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
    int query_type;
    
    struct book record; 
    
    if (argc < 2) {
        fprintf(stderr, "How to use : %s <filename>\n", argv[0]);
        exit(1);
    }
    
    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    do {
        printf("\n--bookquery--\n");
        printf("0: list of all books, 1: list of available books ) ");
        
        if (scanf("%d", &query_type) != 1) {
            printf("Input Error: Invalid input. Exiting.\n");
            while (getchar() != '\n'); 
            break; 
        }

        if (query_type != 0 && query_type != 1) {
            printf("Input Error: Please enter 0 or 1.\n");
            continue; 
        }

        lseek(fd, 0, SEEK_SET);

        printf("id %10s %12s %6s %12s %8s\n", "bookname", "author", "year", "numofborrow", "borrow"); 

        while (read(fd, (char *)&record, sizeof(record)) > 0) {
            
            int should_print = 0;
            
            if (query_type == 0) {
                should_print = 1;
            } else if (query_type == 1) { 
                if (strcmp(record.borrow, "True") == 0) {
                    should_print = 1;
                }
            }
            
            if (should_print) {
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
