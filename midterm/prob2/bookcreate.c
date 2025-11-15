#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

struct book {
    int id;
    char bookname[10];
    char author[10];
    int year;
    int numofborrow;
	char borrow[6];
};

#define START_ID 1

int main(int argc, char *argv[])
{
    int fd;
    struct book record;

    if ((fd = open("db.dat", O_WRONLY|O_CREAT|O_EXCL, 0640)) == -1) {
        perror("db.dat");
        exit(2);
    }

    printf("%2s %10s %12s %6s %12s %8s\n", 
           "id", "bookname", "author","year", "numofborrow", "borrow");

    while (scanf("%d %s %s %d %d %s", 
                  &record.id, record.bookname, record.author, 
                  &record.year, &record.numofborrow, record.borrow) == 6) {

        if (lseek(fd, (record.id - START_ID) * sizeof(record), SEEK_SET) == -1) {
             perror("lseek error");
             continue;
        }

        if (write(fd, (char *)&record, sizeof(record)) != sizeof(record)) {
             perror("write error");
        }
    }

    close(fd);
    exit(0);
}
