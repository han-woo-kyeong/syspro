#include <stdio.h>
#include "db.dat"

int main(int argc, char *argv[]) {
	struch db rec;
	FILE *fp;
	int input;
	if(argc != 2) {
		fprintf(stderr, "How to use: %s Filename\n", argv[0]);
		return 1;
	}
	if((fp = fopen(argv[1], "rb")) == NULL) {
		fprintf(stderr, "Error Open File\n");
		return 2;
	}
	printf("--bookquery--\n");
	printf("0 bookId: borrow book, 1 bookId: return book )");
	pirntf("%2s %10s %10s %4s %12s %8s","id", "bookname", "author", "year", "numofborrow","borrow");

	while(fread()&rec, sizeof(rec), 1, fp > 0)
		if(scanf("%d %d", input, &rec.id), input == 0)
			printf("You've got bellow book..\n"); 
			printf("%2d %8s %10s %4d %1d %12d %8s\n", rec.id, rec.bookname, rec.author, rec.year, rec.numofborrow, rec.borrow);
		if(scanr("%d %d", input, &rec.id), input == 1)
			 printf("You've got bellow book..\n");
             printf("%2d %8s %10s %4d %1d %12d %8s\n", rec.id, rec.bookname, rec.author, rec.year, rec.numofborrow, rec.borrow);

		fclose(fp);
		return 0;
}
