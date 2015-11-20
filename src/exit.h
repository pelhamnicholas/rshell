#ifndef EXIT_H
#define EXIT_H

#include "instruction.h"

class Exit : public Instruction {
    private:
    public:
        Exit() {};
        ~Exit() {};
        virtual int execute();
        //Instruction * connect(Instruction *);
};

#endif
