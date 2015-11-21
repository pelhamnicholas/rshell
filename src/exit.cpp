/*
 * Author: Nicholas Pelham
 * Date:   11/21/2015
 *
 * exit: simple command to exit program
 */
#include "exit.h"

int Exit::execute() {
    exit(0);
}

/*
Instruction * Exit::connect(Instruction * inst) {
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
