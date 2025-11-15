#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	char c;
	FILE *fp1, *fp2;
	int option;

 	if(argc !=4) {
		fprintf(stderr, "How to use: %s option FIle1 File2\n",argv[0]);
		return 1;
	}
	option = atoi(argv[1]);

	if(option <0 || option >2) {
		fprintf(stderr, "Invalid option: %s. Use 0, 1, 2\n", argv[1]);
		return 3;
	}

	fp1 = fopen(argv[2],"r");
	if(fp1 == NULL) {
		fprintf(stderr, "File %s Open Error\n",argv[2]);
		return 2;
	}

	fp2 = fopen(argv[3], "w");
	if(fp2 == NULL) {
		fprintf(stderr, "File %s Open Error\n",argv[3]);
		return 2;
	}

	while((c = fgetc(fp1)) != EOF){
		if(option ==  1) {
			c = tolower(c);
		}else if (option == 2) {
			c= toupper(c);
		}

		fputc(c, fp2);
	}
		

	fclose(fp1);
	fclose(fp2);
	return 0;
}
