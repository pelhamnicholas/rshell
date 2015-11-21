#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdlib.h>

class Instruction {
    private:

    public:
        Instruction();
        virtual ~Instruction();
        virtual Instruction * getConnector() { return NULL; };
        virtual int execute() = 0;
};

#endif
