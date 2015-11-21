#ifndef INSTRUCTIONTREE_H
#define INSTRUCTIONTREE_H

#include <stack>
#include "instruction.h"
#include "connector.h"
#include "command.h"
#include "exit.h"
#include "test.h"

#define NUMPARENS 1

class InstructionTree {
    private:
        Instruction * tree;

        bool hasValidParens(char **);
        bool isConnector(char *);
        bool isComment(char *);
        bool isOpenParen(char *);
        bool isCloseParen(char *);

    public:
        static const char openParen[NUMPARENS];
        static const char closeParen[NUMPARENS];

        InstructionTree();
        ~InstructionTree();
        Instruction * getTree() { return tree; };
        Instruction * makeTree(char **);
        Instruction * makeTree(char **, int &);
        char ** makeArgv(char **);
        char ** makeArgv(char **, char *);
        char * removeOpenParen(char *);
        char * removeCloseParen(char *);
};

#endif
