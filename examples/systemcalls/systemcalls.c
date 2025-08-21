#include "systemcalls.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

/**
 * Execute a command with system()
 */
bool do_system(const char *cmd)
{
    if(cmd == NULL) return false;

    int ret = system(cmd);
    if(ret == -1) return false; // system call lỗi
    if(WIFEXITED(ret) && WEXITSTATUS(ret) == 0) return true; // command thành công

    return false; // command lỗi
}

/**
 * Execute a command with execv using fork
 */
bool do_exec(int count, ...)
{
    va_list args;
    va_start(args, count);
    char *command[count+1];

    for(int i = 0; i < count; i++)
        command[i] = va_arg(args, char *);
    command[count] = NULL;

    // Check absolute path for command[0]
    if(command[0][0] != '/') {
        va_end(args);
        return false;
    }

    fflush(stdout); // tránh duplicate output

    pid_t pid = fork();
    if(pid < 0) {
        va_end(args);
        return false; // fork lỗi
    } else if(pid == 0) {
        execv(command[0], command);
        perror("execv failed");
        _exit(1);
    } else {
        int status;
        if(waitpid(pid, &status, 0) == -1) {
            va_end(args);
            return false;
        }
        va_end(args);
        return (WIFEXITED(status) && WEXITSTATUS(status) == 0);
    }
}

/**
 * Execute command with stdout redirected to a file
 */
bool do_exec_redirect(const char *outputfile, int count, ...)
{
    va_list args;
    va_start(args, count);
    char *command[count+1];

    for(int i = 0; i < count; i++)
        command[i] = va_arg(args, char *);
    command[count] = NULL;

    // Check absolute path for command[0]
    if(command[0][0] != '/') {
        va_end(args);
        return false;
    }

    fflush(stdout);

    pid_t pid = fork();
    if(pid < 0) {
        va_end(args);
        return false;
    } else if(pid == 0) {
        int fd = open(outputfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(fd < 0) {
            perror("open failed");
            _exit(1);
        }
        if(dup2(fd, STDOUT_FILENO) < 0) {
            perror("dup2 failed");
            _exit(1);
        }
        close(fd);

        execv(command[0], command);
        perror("execv failed");
        _exit(1);
    } else {
        int status;
        if(waitpid(pid, &status, 0) == -1) {
            va_end(args);
            return false;
        }
        va_end(args);
        return (WIFEXITED(status) && WEXITSTATUS(status) == 0);
    }
}

