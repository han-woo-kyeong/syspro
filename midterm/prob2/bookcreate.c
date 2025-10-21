#include <stdio.h>
#include "db.dat"
int main(inta argc, char *argv[]) {
	struct db rec;
	FILE *fp;

	if(argc != 2) {
		fprintf(stderr, "How to use: %s Filename\n",argv[0]);
		exit(1);
	}
	fp = fopen(argv[1],"wb");
	printf("%-9s %-7s %-4s %-4d %-4s %-4s\n", "id", "bookname", "author", "year","numofborrow","borrow");
	while(scanf("%d %s %s %d %d %s", &rec.id, rec.bookname, rec.author, &rec.year, &rec.numofborrow, rec.borrow) == 6)
		fwrite(&rec, sizeof(rec), 1, fp);

	fclose(fp);
	exit(0);
}
