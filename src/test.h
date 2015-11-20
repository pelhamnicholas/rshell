#ifndef TEST_H
#define TEST_H

#include "instruction.h"

class Test : public Instruction {
    private:
        char ** argv;
        
    public:
        Test();
        ~Test();
        virtual int execute();
        //Instruction * connect(Instruction *);
};

#endif
