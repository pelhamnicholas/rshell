#include "instructiontree.h"

const char InstructionTree::openParen[NUMPARENS] = { '(' };
const char InstructionTree::closeParen[NUMPARENS] = { ')' };

InstructionTree::InstructionTree() {
    tree = NULL;
}

InstructionTree::~InstructionTree() {
    delete tree;
}

bool InstructionTree::hasValidParens(char ** cStr) {
    std::stack<char> parenStack;

    for (int i = 0; cStr[i] != NULL; ++i) {
        if (isOpenParen(cStr[i]))
            parenStack.push(cStr[i][0]);
        if (isCloseParen(cStr[i]) && !parenStack.empty()) {
            int j;
            for (j = 0; j < NUMPARENS &&
                    openParen[j] != parenStack.top(); ++j) ;
            if (openParen[j] == parenStack.top()) {
                parenStack.pop();
            } else
                return false;
        } else
            return false;
    }

    return parenStack.empty();
}

bool InstructionTree::isConnector(char * cStr) {
    for (int i = 0; i < NUMCONNECTORS; ++i)
        if (strcmp(cStr, Connector::CONNECTOR[i]) == 0)
            return true;
    return false;
}

bool InstructionTree::isComment(char * cStr) {
    if (cStr[0] == '#')
        return true;
    return false;
}

bool InstructionTree::isOpenParen(char * cStr) {
    for (int i = 0; i < NUMPARENS; ++i)
        if (cStr[0] == openParen[i])
            return true;
    return false;
}

bool InstructionTree::isCloseParen(char * cStr) {
    for (int i = 0; i < NUMPARENS; ++i)
        if (cStr[strlen(cStr)-1] == closeParen[i])
            return true;
    return false;
}

char * InstructionTree::removeOpenParen(char * cStr) {
    char * temp;
    cStr = cStr+sizeof(char);
    strcpy(temp, cStr);
    return temp;
}

char * InstructionTree::removeCloseParen(char * cStr) {
    char * temp;
    cStr[strlen(cStr)-1] = '\0';
    return cStr;
}

Instruction * InstructionTree::makeTree(char ** cStr) {
    Instruction * tree = NULL;

    //if (cStr[0] != ) ;

    return tree;
}

char ** InstructionTree::makeArgv(char ** cStr) {
    char ** argv = NULL;
    int size = 0;
    while (cStr[size] != NULL && !isComment(cStr[size]) 
            && !isConnector(cStr[size]))
        size++;
    argv = (char**) malloc((size + 1) * sizeof(char*));

    for (int i = 0; cStr[i] != NULL &&
            !isComment(cStr[i]) && !isConnector(cStr[i]); ++i) {
        if (isOpenParen(cStr[i])) {
            argv[i] = (char*) malloc(
                    (strlen(cStr[i]) - 1) * sizeof(char));
            strcpy(argv[i], removeOpenParen(cStr[i]));
        } else if (isCloseParen(cStr[i])) {
            argv[i] = (char*) malloc(
                    (strlen(cStr[i]) - 1) * sizeof(char));
            strcpy(argv[i], removeCloseParen(cStr[i]));
            break;
        } else {
            argv[i] = (char*) malloc(strlen(cStr[i]) * sizeof(char));
            strcpy(argv[i], cStr[i]);
        }
    }
    argv[size] = NULL;

    return argv;
}

