#ifndef TEST_H
#define TEST_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include "instruction.h"

using std::cout;
using std::endl;

class Test : public Instruction {
    private:
        char ** argv;
        
    public:
        Test();
        Test(char **);
        ~Test();
        virtual int execute();
        //Instruction * connect(Instruction *);
};

#endif
