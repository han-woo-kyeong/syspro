#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_LINES 10
#define MAX_LINE_LENGTH 100

char savedText[MAX_LINES][MAX_LINE_LENGTH];
int totalLines = 0;

void readFile(const char* filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("File Open Error!\n");
        exit(1);
    }

    char buf;
    int row = 0, col = 0;

    while (read(fd, &buf, 1) > 0) {
        if (buf == '\n') {
            savedText[row][col] = '\0';
            row++;
            col = 0;
        } else {
            savedText[row][col++] = buf;
        }
    }

    if (col > 0) {
        savedText[row][col] = '\0';
        row++;
    }

    totalLines = row;
    close(fd);

    printf("File read success\n");
    printf("Total Line : %d\n", totalLines);
    printf("You can choose 1 ~ %d Line\n", totalLines);
}

void printLine(int line) {
    if (line >= 0 && line < totalLines && strlen(savedText[line]) > 0) {
        printf("%s\n", savedText[line]);
    }
}

void printLineRange(int start, int end) {
    for (int i = start; i <= end; i++) {
        printLine(i);
    }
}

void processInput(char* input) {
    if (strcmp(input, "*") == 0) {
        for (int i = 0; i < totalLines; i++) {
            printLine(i);
        }
    } else if (strchr(input, ',') != NULL) {
        char* token = strtok(input, ",");
        while (token != NULL) {
            int line = atoi(token) - 1;
            printLine(line);
            token = strtok(NULL, ",");
        }
    } else if (strchr(input, '-') != NULL) {
        int start, end;
        sscanf(input, "%d-%d", &start, &end);
        printLineRange(start - 1, end - 1);
    } else {
        int line = atoi(input) - 1;
        printLine(line);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    readFile(argv[1]);

    char input[100];
    printf("Pls 'Enter' the line to select : ");
    scanf("%s", input);

    processInput(input);

    return 0;
}

