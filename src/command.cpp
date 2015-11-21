/*
 * Author: Nicholas Pelham
 * Date  : 11/21/2015
 *
 * Command: Wraper to execute commands not built into rshell
 */

#include "command.h"

Command::Command() : Instruction() {
    argv = NULL;
}

Command::Command(char ** argv) {
    this->argv = argv;
}

/*
 * Deconstructor: argv is created by malloc(), so it is deleted
 *                with free()
 */
Command::~Command() {
    int i = 0;
    while (argv[i] != NULL)
        free(argv[i++]);
    free(argv[i]);
    free(argv);
}

/*
 * addArgv: sets argv after command is created.
 *          Not used.
 */
void Command::addArgv(char ** argv) {
    this->argv = argv;
}

/*
 * execute: forks the process to allow a command to run before continuing
 *          program execution.
 */
int Command::execute() {
    pid_t c_pid, pid;
    int status;

    // pipe setup
    int exeStatus = 0;
    int pfd[2];
    if (pipe(pfd) < 0)
        perror("pipe");

    c_pid = fork();

    if (c_pid < 0) {
        perror("fork failed");
        exit(2);
    } else if (c_pid == 0) {
        pid = getpid();
        // close reading end of pipe in child
        close(pfd[0]);

        exeStatus = execvp(argv[0], argv);
        perror("Error executing");

        // write to pipe
        write(pfd[1], &exeStatus, sizeof(int));
        close(pfd[1]);

        exit(12);
    } else if (c_pid > 0) {
        if ((pid = wait(&status)) < 0) {
            perror("wait");
            exit(1);
        }
    }

    // close write pipe in parent
    close(pfd[1]);
    // read from pipe
    read(pfd[0], &exeStatus, sizeof(int));
    close(pfd[0]);

    return exeStatus;
}
