#ifndef COMMAND_H
#define COMMAND_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "instruction.h"

class Command : public Instruction {
    private:
        char ** argv;

    public:
        Command();
        Command(char **);
        ~Command();
        void addArgv(char **);
        int execute();
        //Instruction * connect(Instruction *);
};

#endif
