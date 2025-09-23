#include <stdio.h>
#include <string.h>
#include "copy.h"

#define N 5

char line[MAXLINE];
char lines[N][MAXLINE];
int lengths[N];

int main() {
    int i, j;
    char temp[MAXLINE];
    int tempLen;

    for (i = 0; i < N; i++) {
        if (fgets(line, MAXLINE, stdin) == NULL) break;
        line[strcspn(line, "\n")] = '\0';
        copy(line, lines[i]);
        lengths[i] = strlen(lines[i]);
    }

    for (i = 0; i < N - 1; i++) {
        for (j = i + 1; j < N; j++) {
            if (lengths[i] < lengths[j]) {
                tempLen = lengths[i];
                lengths[i] = lengths[j];
                lengths[j] = tempLen;

                copy(lines[i], temp);
                copy(lines[j], lines[i]);
                copy(temp, lines[j]);
            }
        }
    }

    for (i = 0; i < N; i++) {
        printf("%s\n", lines[i]);
    }

    return 0;
}

