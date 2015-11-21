#include "connector.h"

const char * const Connector::CONNECTOR[NUMCONNECTORS] 
        = { "&&", "||", ";" };

Connector::Connector() {
    left = NULL;
    right = NULL;
}

Connector::Connector(char * cStr) {
    type = cStr;
    left = NULL;
    right = NULL;
}

Connector::~Connector() {
    delete left;
    delete right;
}

Instruction * Connector::setLeft(Instruction * inst) {
    if (left != NULL)
        return this;
    left = inst;
    return this;
}

Instruction * Connector::setRight(Instruction * inst) {
    if(right != NULL)
        return this;
    right = inst;
    return this;
}

int Connector::execute() {
    int c = 0;
    while (c < NUMCONNECTORS && type != CONNECTOR[c++]) ;

    switch (c) {
        case 0:
            if (left->execute() != -1 && right->execute() != -1)
                return 0;
            else
                return -1;
            break;
        case 1:
            if (left->execute() != -1 || right->execute() != -1)
                return 0;
            else
                return -1;
            break;
        case 2:
        default:
            left->execute();
            right->execute();
            return 0;
    }
}

/*
Instruction * Connector::connect(Instruction * inst) {
    if (inst->getConnector() == NULL)
        return inst->connect(this);
    if (inst->getLeft() == NULL) {
        inst->setLeft(this);
        return inst;
    } else if (inst->getRight == NULL) {
        inst->setRight(this);
        return inst;
    }
        return this;
}
*/
