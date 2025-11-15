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

int main(int argc, char *argv[]){
    int fd;
    char search_bookname[10]; 
    int found = 0;
    
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
        found = 0; 
        
        printf("\ninput name of book ) ");
        
        if (scanf("%9s", search_bookname) != 1) {
            printf("Input Error: Invalid input. Exiting.\n");
            while (getchar() != '\n'); 
            break; 
        }

        lseek(fd, 0, SEEK_SET);

        while (read(fd, (char *)&record, sizeof(record)) > 0) {
            
            if (strcmp(record.bookname, search_bookname) == 0) {

				if (found == 0) {
					printf("id %10s %12s %6s %12s %8s\n", "bookname", "author", "year", "numofborrow", "borrow");
				}
                
                found = 1;
                
                printf("%2d %10s %12s %6d %12d %8s\n",
                       record.id,
                       record.bookname,
                       record.author,
                       record.year,
                       record.numofborrow, 
                       record.borrow);
                       
                break; 
            }
        }
        
        if (found == 0) {
            printf("not found book name : '%s'\n", search_bookname);
        }
        
        while (getchar() != '\n');
        
    } while(1); 

    close(fd);
    exit(0);
}
