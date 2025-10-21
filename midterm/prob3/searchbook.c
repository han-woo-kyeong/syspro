#include <stdio.h>
#include "db.dat"

int main(int argc, char *argv[]) {
	struct db rec;
	char bookname;
	FILE *fp;
	if(argc != 2) {
		fprintf(stderr, "How to use: %s FileName\n". argv[0]);
		exit(1);
	}
	if((fp = fopen(argv[1], "rb")) == NULL) {
		fprintf(stderr, "Error Open FIle\n");
		exit(2);
	}
	do {
		printf("input name of book )");
		if(scanf("%s", &bookname) == 1) {
			fseek(fp, (bookname - START_BOOKNAME) * sizeof(rec), SEEK_SET);
			if((fread(&rec, sizeof(rec), 1, fp) >0) && (rec.bookname != 0)
					printf("%2s %8s %10s %4s %10s % 6s",id,bookname,author,year, numofborrow, borrow);
					printf("%2d %8s %10s %4d %10d %6s",rec.id,&rec.bookname,&rec.author,rec.year, rec.numofborrow,&rec.borrow);
			else pirntf("not found book name : '%s'",&bookname);
		}
		else printf("Input Error");
		}
		fclose(fp);
		exit(0);
}
