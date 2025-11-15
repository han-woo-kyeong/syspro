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

int compare_books(const void *a, const void *b) {
    const struct book *bookA = (const struct book *)a;
    const struct book *bookB = (const struct book *)b;
    
    return (bookB->numofborrow - bookA->numofborrow);
}

int main(int argc, char *argv[]){
    int fd;
    int query_type;
    int num_records = 0;
    
    struct book record; 
    struct book *all_records = NULL; 
    
    if (argc < 2) {
        fprintf(stderr, "How to use : %s <filename>\n", argv[0]);
        exit(1);
    }
    
    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    while (read(fd, (char *)&record, sizeof(record)) > 0) {
        num_records++;
        all_records = realloc(all_records, num_records * sizeof(struct book));
        if (all_records == NULL) {
            perror("Memory allocation failed");
            close(fd);
            exit(3);
        }
        memcpy(&all_records[num_records - 1], &record, sizeof(struct book));
    }
    
    close(fd); 

    if (num_records == 0) {
        printf("No records found in the file.\n");
        exit(0);
    }

    qsort(all_records, num_records, sizeof(struct book), compare_books);
    
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

        printf("id %10s %12s %6s %12s %8s\n", "bookname", "author", "year", "numofborrow", "borrow"); 

        for (int i = 0; i < num_records; i++) {
            
            int should_print = 0;
            
            if (query_type == 0) {
                should_print = 1;
            } else if (query_type == 1) { 
                if (strcmp(all_records[i].borrow, "True") == 0) {
                    should_print = 1;
                }
            }
            
            if (should_print) {
                printf("%2d %10s %12s %6d %12d %8s\n",
                       all_records[i].id,
                       all_records[i].bookname,
                       all_records[i].author,
                       all_records[i].year,
                       all_records[i].numofborrow, 
                       all_records[i].borrow);
            }
        }
        
    } while(1); 

    free(all_records);
    exit(0);
}
