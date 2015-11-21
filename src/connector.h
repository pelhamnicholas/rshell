#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <string.h>
#include "instruction.h"

#define NUMCONNECTORS 3

class Connector : public Instruction {
    private:
        char * type;

    protected:
        Instruction * left;
        Instruction * right;

    public:
        static const char * const CONNECTOR[NUMCONNECTORS];

        Connector();
        Connector(char *);
        ~Connector();
        virtual Instruction * getConnector();
        Instruction * getLeft() { return left; };
        Instruction * getRight() { return right; };
        Instruction * setLeft(Instruction *);
        Instruction * setRight(Instruction *);
        virtual int execute();
        //Instruction * connect(Instruction *);
};

#endif
