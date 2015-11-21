#include "command.h"

Command::Command() : Instruction() {
    argv = NULL;
}

Command::Command(char ** argv) {
    this->argv = argv;
}

Command::~Command() {
    int i = 0;
    while (argv[i] != NULL)
        free(argv[i++]);
    free(argv[i]);
    free(argv);
}

void Command::addArgv(char ** argv) {
    this->argv = argv;
}

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

/*
Instruction * Command::connect(Connector * inst) { 
    if (inst->getConnector() == NULL) 
        return this;
    if (inst->getLeft() == NULL) {
        inst->setLeft(this);
    } else if (inst->getRight() == NULL) {
        inst->setRight(this);
        return inst;
    }
    return this;
}
*/
