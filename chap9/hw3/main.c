#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>

#define MAXARG 64
#define MAXLINE 256

void run_single_command(char *cmd_str);

int main() {
    char input_line[MAXLINE];
    char *saveptr_main; 

    while (1) {
        printf("\n[shell] ");
        fflush(stdout);

        if (!fgets(input_line, sizeof(input_line), stdin))
            break; 

        input_line[strcspn(input_line, "\n")] = 0; 

        if (strlen(input_line) == 0)
            continue;

        char *cmd_token = strtok_r(input_line, ";", &saveptr_main);
        while (cmd_token != NULL) {
            while (*cmd_token == ' ') cmd_token++;
            if (*cmd_token != '\0') {
                run_single_command(cmd_token);
            }
            cmd_token = strtok_r(NULL, ";", &saveptr_main);
        }
    }
    
    while(waitpid(-1, NULL, WNOHANG) > 0);

    return 0;
}

void run_single_command(char *cmd_str) {
    char *args[MAXARG];
    int argc = 0;
    int background = 0;
    int in_redirect = -1;
    int out_redirect = -1;
    char *saveptr_cmd; 

    char temp_cmd[MAXLINE];
    strncpy(temp_cmd, cmd_str, MAXLINE);
    temp_cmd[MAXLINE - 1] = '\0';
    
    char *start_ptr = temp_cmd;
    char *end_ptr = temp_cmd + strlen(temp_cmd) - 1;

    while (end_ptr >= start_ptr && *end_ptr == ' ') {
        *end_ptr-- = '\0';
    }

    if (end_ptr >= start_ptr && *end_ptr == '&') {
        background = 1;
        *end_ptr-- = '\0';
        
        while (end_ptr >= start_ptr && *end_ptr == ' ') {
            *end_ptr-- = '\0';
        }
    }
    
    while (*start_ptr == ' ') {
        start_ptr++;
    }

    char *token = strtok_r(start_ptr, " \t", &saveptr_cmd);
    while (token != NULL) {

        if (strcmp(token, ">") == 0) {
            token = strtok_r(NULL, " \t", &saveptr_cmd); 
            if (token == NULL) { fprintf(stderr, "[shell] missing file for >\n"); return; }
            out_redirect = open(token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (out_redirect == -1) { perror("[shell] open error for output"); return; }
        }
        else if (strcmp(token, "<") == 0) {
            token = strtok_r(NULL, " \t", &saveptr_cmd);
            if (token == NULL) { fprintf(stderr, "[shell] missing file for <\n"); return; }
            in_redirect = open(token, O_RDONLY);
            if (in_redirect == -1) { perror("[shell] open error for input"); return; }
        }
        else {
            if (argc < MAXARG - 1) {
                args[argc++] = token;
            } else {
                fprintf(stderr, "[shell] too many arguments\n");
                return;
            }
        }
        token = strtok_r(NULL, " \t", &saveptr_cmd);
    }
    args[argc] = NULL; 

    if (argc == 0) return; 

    pid_t pid = fork();

    if (pid == 0) { 
        if (in_redirect != -1) {
            if (dup2(in_redirect, STDIN_FILENO) == -1) { perror("[shell] dup2 error"); exit(1); }
            close(in_redirect);
        }
        if (out_redirect != -1) {
            if (dup2(out_redirect, STDOUT_FILENO) == -1) { perror("[shell] dup2 error"); exit(1); }
            close(out_redirect);
        }

        execvp(args[0], args);
        perror("[shell] execvp failed");
        exit(1);
    }
    else if (pid > 0) {
        if (in_redirect != -1) close(in_redirect);
        if (out_redirect != -1) close(out_redirect);

        if (!background) {
            waitpid(pid, NULL, 0);
        } else {
            fprintf(stderr, "[shell] background job started with PID: %d\n", pid);
        }
    } else { 
        perror("[shell] fork failed");
    }
}
