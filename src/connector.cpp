/*
 * Author: Nicholas Pelham
 * Date  : 11/21/2015
 * 
 * Connector: Handles all of the connectors.
 */
#include "connector.h"

/*
 * To add another connector:
 *     Add the symbol here.
 *     Include execution in execute()
 *     Increase NUMCONNECTORS in connector.h
 */
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
    free(type);
    delete left;
    delete right;
}

/*
 * getConnector: Used to differentiate connectors from other
 *               instruction objects.
 */
Instruction * Connector::getConnector() {
    return this;
}

/*
 * setLet: Doesn't allow overwriting children
 */
Instruction * Connector::setLeft(Instruction * inst) {
    if (left != NULL)
        return this;
    left = inst;
    return this;
}

/*
 * setLet: Doesn't allow overwriting children
 */
Instruction * Connector::setRight(Instruction * inst) {
    if(right != NULL)
        return this;
    right = inst;
    return this;
}

/*
 * execute: properly execute the right and left instructions
 *          according to the connector type
 */
int Connector::execute() {
    int c = 0;
    while (c < NUMCONNECTORS && strcmp(type, CONNECTOR[c]) != 0) 
        c++;

    // cased correllate to CONNECTOR which is defined above
    switch (c) {
        case 0:
            if (left->execute() == 0 && right->execute() == 0)
                return 0;
            else
                return -1;
            break;
        case 1:
            if (left->execute() == 0 || right->execute() == 0)
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
