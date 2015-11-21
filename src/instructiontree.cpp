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
    strcpy(temp, cStr);
    temp = temp+sizeof(char);
    return temp;
}

/*
 * doesnt work
 */
char * InstructionTree::removeCloseParen(char * cStr) {
    char * temp;
    temp = (char*) malloc((strlen(cStr)) * sizeof(char));
    strcpy(temp, cStr);
    temp[strlen(cStr) - 1] = '\0';
    return temp;
}

Instruction * InstructionTree::makeTree(char ** cStr) {
    Instruction * tree = NULL;

    for (int i = 0; cStr[i] != NULL; ++i) {
        if (isComment(cStr[i]))
            break;
        else if (isConnector(cStr[i])) {
            Connector * conn = new Connector(cStr[i]);
            tree = conn->setLeft(tree);
        } else if (strcmp(cStr[i], "exit") == 0) {//isExit(cStr[i])) {
            Exit * exit = new Exit();
            if (tree == NULL) {
                tree = exit;
            } else if (tree->getConnector() != NULL) {
                ((Connector*)tree)->setRight(exit);
            } else
                // error - cannot connect commands
                ;
        //} else if (isOpenParen(cStr[i])) {
        //    if (tree->getConnector() != NULL) {
        //        ((Connector *)tree)
        //                ->setRight(makeSubTree((char**)cStr[i]), &i);
        //    } else
                // error - cannot connect to a comman
        //        ;
        } else {
            Command * cmd = new Command(makeArgv(&cStr[i]));
            while (cStr[i] != NULL && !isComment(cStr[i]) &&
                    !isConnector(cStr[i]) && !isCloseParen(cStr[i])) 
                i++;
            i--;
            if (tree == NULL) {
                tree = cmd;
            } else if (tree->getConnector() != NULL) {
                tree = ((Connector*)tree)->setRight(cmd);
            } else
                // error - cannot connect commands
                ;
        }
    }

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

