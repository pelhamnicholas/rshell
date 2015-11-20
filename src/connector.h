#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "instruction.h"

#define NUMCONNECTORS 3

class Connector : public Instruction {
    private:
        char * type;
        static const char * const CONNECTOR[NUMCONNECTORS];

    protected:
        Instruction * left;
        Instruction * right;

    private:
        Connector();
        Connector(char *);
        ~Connector();
        //virtual Instruction * getConnector();
        Instruction * getLeft() { return left; };
        Instruction * getRight() { return right; };
        Instruction * setLeft(Instruction *);
        Instruction * setRight(Instruction *);
        virtual int execute();
        //Instruction * connect(Instruction *);
};

#endif
