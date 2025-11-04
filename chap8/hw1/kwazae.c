#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

extern char **environ;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Error: Option is required.\n");
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-e") == 0) {
        if (argc == 3) {
            char *name = argv[2];
            char *val  = getenv(name);
            if (val) {
                printf("%s = %s\n", name, val);
            } else {
                fprintf(stderr, "Error: Environment variable \"%s\" does not exist or has no value.\n", name);
                return EXIT_FAILURE;
            }
        }
        else if (argc == 2) {
            for (char **p = environ; *p != NULL; p++) {
                printf("%s \n", *p);
            }
        }
        else {
            fprintf(stderr, "Error: Invalid number of arguments for option \"-e\".\n");
            return EXIT_FAILURE;
        }
    }
    else if (strcmp(argv[1], "-u") == 0) {
        uid_t ruid = getuid();
        uid_t euid = geteuid();
        struct passwd *pw1 = getpwuid(ruid);
        struct passwd *pw2 = getpwuid(euid);
        printf("My Realistic User ID : %d(%s) \n", 
				getuid(), getpwuid(getuid())->pw_name);
        printf("My Valid User ID : %d(%s) \n", 
				getuid(), getpwuid(geteuid())->pw_name);
    }
    else if (strcmp(argv[1], "-g") == 0) {
        gid_t rgid = getgid();
        gid_t egid = getegid();
        struct group *gr1 = getgrgid(rgid);
        struct group *gr2 = getgrgid(egid);
        printf("My Realistic Group ID : %d(%s) \n", 
				getgid(), getgrgid(getgid())->gr_name);
        printf("My Valid Group ID : %d(%s) \n", 
				getegid(), getgrgid(getegid())->gr_name);
    }
    else if (strcmp(argv[1], "-i") == 0) {
        printf("My process number : [%d]\n", (int)getpid());
    }
    else if (strcmp(argv[1], "-p") == 0) {
        printf("My parent's process number : [%d]\n", (int)getppid());
    }
    else {
        fprintf(stderr, "Error: Unknown option \"%s\".\n", argv[1]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

