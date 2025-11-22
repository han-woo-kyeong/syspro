#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define MAXARG 64
#define MAXLINE 256

void run_command(char *line);

int main() {
    char line_input[MAXLINE];

    while (1) {
        printf("\nPls input cmd : ");
        fflush(stdout);

        if (!fgets(line_input, sizeof(line_input), stdin))
            break;

        line_input[strcspn(line_input, "\n")] = 0;

        if (strlen(line_input) == 0)
            continue;

        if (strcmp(line_input, "exit") == 0) {
            printf("Exit\n");
            break;
        }

        run_command(line_input);
    }

    while(waitpid(-1, NULL, WNOHANG) > 0); 
    
    return 0;
}

void run_command(char *line) {
    char *args[MAXARG];
    char *token, *saveptr;
    int background = 0;
    int status;
	int child;
    char temp_line[MAXLINE];

    strcpy(temp_line, line);

    int len = strlen(temp_line);
    int i = len - 1;

    while (i >= 0 && temp_line[i] == ' ')
        temp_line[i--] = 0;

    if (i >= 0 && temp_line[i] == '&') {
        background = 1;
        temp_line[i] = 0;
    }

    int argc = 0;
    token = strtok_r(temp_line, " \t", &saveptr);
    while (token != NULL && argc < MAXARG - 1) {
        args[argc++] = token;
        token = strtok_r(NULL, " \t", &saveptr);
    }
    args[argc] = NULL;

    if (argc == 0) return;

    printf("[%d] Parent process start\n", getpid());

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork error");
        return;
    }

    if (pid == 0) {
		if (background) {
			printf("[%d] child process start\n", getpid());
		}

		execvp(args[0], args);
        exit(1);

    }
		
    else {
        child= waitpid(pid, &status, 0);
        
        int execvp_failed = (WIFEXITED(status) && WEXITSTATUS(status) != 0);

        if (!execvp_failed) {
			if (background) {
				printf("[%d] child process end %d\n", getpid(), child);
			}
			printf("SUCCESS\n");
        } 
        
        if (execvp_failed) {
             printf("Parent process end\n");
			 printf("Exit\n");
             exit(0);
        }
    }
}
