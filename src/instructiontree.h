#ifndef INSTRUCTIONTREE_H
#define INSTRUCTIONTREE_H

#include <stack>
#include "instruction.h"
#include "connector.h"
#include "command.h"
#include "exit.h"

#define NUMPARENS 1

class InstructionTree {
    private:
        Instruction * tree;
        static const char openParen[NUMPARENS];
        static const char closeParen[NUMPARENS];

        bool hasValidParens(char **);
        bool isConnector(char *);
        bool isComment(char *);
        bool isOpenParen(char *);
        bool isCloseParen(char *);
        char * removeOpenParen(char *);
        char * removeCloseParen(char *);

    public:
        InstructionTree();
        ~InstructionTree();
        Instruction * getTree() { return tree; };
        Instruction * makeTree(char **);
};

#endif
