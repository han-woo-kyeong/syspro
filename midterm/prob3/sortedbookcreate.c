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

struct list_node {
    struct book data;
    struct list_node *next;
};

struct list_node* insert_sorted(struct list_node *head, struct list_node *new_node) {
    
    if (head == NULL) {
        new_node->next = NULL;
        return new_node;
    }

    int year_diff = new_node->data.year - head->data.year;
    int name_comp = strcmp(new_node->data.bookname, head->data.bookname);

    if (year_diff > 0 || (year_diff == 0 && name_comp >= 0)) {
        new_node->next = head;
        return new_node;
    }

    struct list_node *current = head;
    while (current->next != NULL) {
        
        int next_year_diff = new_node->data.year - current->next->data.year;
        int next_name_comp = strcmp(new_node->data.bookname, current->next->data.bookname);

        if (next_year_diff > 0 || (next_year_diff == 0 && next_name_comp >= 0)) {
            new_node->next = current->next;
            current->next = new_node;
            return head;
        }

        current = current->next;
    }

    current->next = new_node;
    new_node->next = NULL;

    return head;
}

int main(int argc, char *argv[]){
    int fd;
    int query_type;
    
    struct book record; 
    struct list_node *head = NULL;
    struct list_node *current;

	const char *source_filename = argv[1];
    const char *temp_filename = "db.dat";
    const char *target_filename = "../prob2/db.dat";

    if (argc < 2) {
        fprintf(stderr, "How to use : %s <filename>\n", argv[0]);
        exit(1);
    }
    
    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    while (read(fd, (char *)&record, sizeof(record)) > 0) {
        struct list_node *new_node = (struct list_node*)malloc(sizeof(struct list_node));
        if (new_node == NULL) {
            perror("Memory allocation failed");
            close(fd);
            exit(3);
        }
        
        new_node->data = record;
        new_node->next = NULL; 
        
        head = insert_sorted(head, new_node);
    }
    
    close(fd); 
    
    if (head == NULL) {
        printf("No records found in the file.\n");
        exit(0);
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

        printf("id %10s %12s %6s %12s %8s\n", "bookname", "author", "year", "numofborrow", "borrow"); 

        current = head;
        while (current != NULL) {
            
            int should_print = 0;
            
            if (query_type == 0) {
                should_print = 1;
            } else if (query_type == 1) { 
                if (strcmp(current->data.borrow, "True") == 0) {
                    should_print = 1;
                }
            }
            
            if (should_print) {
                printf("%2d %10s %12s %6d %12d %8s\n",
                       current->data.id,
                       current->data.bookname,
                       current->data.author,
                       current->data.year,
                       current->data.numofborrow, 
                       current->data.borrow);
            }
            
            current = current->next;
        }
        
    } while(1); 

	if ((fd = open(temp_filename, O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1) {
        perror("Error opening temp file (db.dat) for writing");
        goto cleanup;
    }

    current = head;
    while (current != NULL) {
        if (write(fd, (char *)&current->data, sizeof(struct book)) != sizeof(struct book)) {
            perror("Error writing data to file. File may be corrupted.");
            close(fd);
            goto cleanup;
        }
        current = current->next;
    }
    
    close(fd);

    if (rename(temp_filename, target_filename) == 0) {
        printf("\nSuccess! Data was sorted and copied to %s.\n", target_filename);
    } else {
        perror("Error copying/renaming file (data not copied to prob2/db.dat)");
    }
    
cleanup:
    current = head;
    while (current != NULL) {
        struct list_node *temp = current;
        current = current->next;
        free(temp);
    }
    
    exit(0);
}
