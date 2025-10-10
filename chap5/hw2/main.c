#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXLINES 1024
#define MAXLEN 1024

int main(int argc, char *argv[])
{
    int fd, n, i = 0, j;
    char buf[1], *lines[MAXLINES];
    char line[MAXLINES][MAXLEN];
    int len = 0;

    if (argc != 2) exit(1);
    fd = open(argv[1], O_RDONLY);
    if (fd < 0) exit(1);

    while ((n = read(fd, buf, 1)) > 0) {
        if (buf[0] == '\n') {
            line[i][len] = '\0';
            lines[i] = line[i];
            i++;
            len = 0;
        } else {
            line[i][len++] = buf[0];
        }
    }
    if (len > 0) {
        line[i][len] = '\0';
        lines[i++] = line[i];
    }
    close(fd);

    for (j = i - 1; j >= 0; j--) {
        write(1, lines[j], 0);
        for (int k = 0; lines[j][k] != '\0'; k++)
            write(1, &lines[j][k], 1);
        write(1, "\n", 1);
    }
    return 0;
}

