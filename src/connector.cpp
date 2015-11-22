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

/*
 * Left and right are initialized to NULL
 */
Connector::Connector() {
    type = NULL;
    left = NULL;
    right = NULL;
}

Connector::Connector(char * cStr) {
    type = cStr;
    left = NULL;
    right = NULL;
}

Connector::~Connector() {
    if (type != NULL)
        free(type);
    if (left != NULL)
        delete left;
    if (right != NULL)
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
 * setLeft: Doesn't allow overwriting children
 */
Instruction * Connector::setLeft(Instruction * inst) {
    if (left != NULL)
        return this;
    left = inst;
    return this;
}

/*
 * setRight: Doesn't allow overwriting children
 */
Instruction * Connector::setRight(Instruction * inst) {
    if (right != NULL)
        return this;
    right = inst;
    return this;
}

/*
 * execute: properly execute the right and left instructions
 *          according to the connector type
 */
int Connector::execute() {

    // check that both children exist
    if (left == NULL && right == NULL)
        return -1;
    else if (right == NULL) {
        if (left->execute() != 0)
            return -1;
        else if (strcmp(type, "&&") == 0)
            return 0;
        else
            return -1;
    } else if (left == NULL) {
        if (right->execute() != 0)
            return -1;
        else if (strcmp(type, "&&") == 0)
            return 0;
        else
            return -1;
    }
        
    int c = 0;
    while (c < NUMCONNECTORS && strcmp(type, CONNECTOR[c]) != 0) 
        c++;

    // cases correllate to CONNECTOR as defined above
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

