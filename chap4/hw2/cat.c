#include <stdio.h>
#include <string.h>

#define MAXLINE 80

int main(int argc, char *argv[])
{
    FILE *fp;
    int line = 0;
    char buffer[MAXLINE];
    int numbering = 0;
    int start = 1;

    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        numbering = 1;
        start = 2;
    }

    if (argc < start) {
        fprintf(stderr, "Error: %s [-n] file1 file2 ...\n", argv[0]);
        exit(1);
    }

    for (int i = start; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            fprintf(stderr, "Error Open File\n", argv[i]);
            continue;
        }

        line = 0;
        while (fgets(buffer, MAXLINE, fp) != NULL) {
            line++;
            printf("%3d ",line, buffer);
        }
        fclose(fp);
    }

    return 0;
}

