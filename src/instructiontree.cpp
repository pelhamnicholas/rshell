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
        if (isCloseParen(cStr[i])) {
            if (parenStack.empty())
                return false;
            int j;
            for (j = 0; j < NUMPARENS &&
                    closeParen[j] != cStr[i][strlen(cStr[i]) - 1]; ++j) ;
            if (openParen[j] == parenStack.top()) {
                parenStack.pop();
            } else
                return false;
        }
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
    int i = 0;

    return makeTree(cStr, i);
}

Instruction * InstructionTree::makeTree(char ** cStr, int & i) {
    Instruction * tree = NULL;

    if (!hasValidParens(cStr))
        return tree;

    for ( ; cStr[i] != NULL; ++i) {
        if (isComment(cStr[i]))
            break;
        else if (isCloseParen(cStr[i]))
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
        } else if (strcmp(cStr[i], "test") == 0) {
            // do test command stuff
            Test * test = new Test(makeArgv(&cStr[i]));
            while (cStr[i] != NULL && !isComment(cStr[i]) &&
                    !isConnector(cStr[i]) && !isCloseParen(cStr[i]))
                i++;
            i--;
            if (tree == NULL)
                tree = test;
            else if (tree->getConnector() != NULL) {
                ((Connector*)tree)->setRight(test);
            } else
                // error - cannot connect commands
                ;
        } else if (cStr[i][0] == '[') {
            // other test stuff
            Test * test = new Test(makeArgv(&cStr[i], (char *) "]\0"));
            while (cStr[i] != NULL && !isComment(cStr[i]) &&
                    !isConnector(cStr[i]) && !isCloseParen(cStr[i])
                    && (cStr[i][strlen(cStr[i]) - 1] != ']'))
                i++;
            //i++;
            if (tree == NULL)
                tree = test;
            else if (tree->getConnector() != NULL)
                ((Connector*)tree)->setRight(test);
            else
                // error - cannot connect commands
                ;
        } else if (isOpenParen(cStr[i])) {
            if (tree == NULL)
                tree = makeTree(cStr, ++i);
            else if (tree->getConnector() != NULL) {
                ((Connector *)tree)
                        ->setRight(makeTree(cStr, ++i));
            } else
                // error - cannot connect to a comman
                ;
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
            !isComment(cStr[i]) && !isConnector(cStr[i])
            //&& ((strcmp(cStr[0], "[") || strcmp(cStr[0], "test"))
                //&& strcmp(cStr[i], "]")) // for test
            ; ++i) {
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

char ** InstructionTree::makeArgv(char ** cStr, char * delim) {
    char ** argv = NULL;
    int size = 0;
    while (cStr[size] != NULL && !isComment(cStr[size]) 
            && !isConnector(cStr[size]))
        size++;
    argv = (char**) malloc((size + 1) * sizeof(char*));

    for (int i = 0; cStr[i] != NULL &&
            !isComment(cStr[i]) && !isConnector(cStr[i])
            && strcmp(cStr[i], delim); ++i) {
        if (isOpenParen(cStr[i])) {
            argv[i] = (char*) malloc(
                    (strlen(cStr[i]) - 1) * sizeof(char));
            strcpy(argv[i], removeOpenParen(cStr[i]));
        } else if (isCloseParen(cStr[i])) {
            argv[i] = (char*) malloc(
                    (strlen(cStr[i]) - 1) * sizeof(char));
            strcpy(argv[i], removeCloseParen(cStr[i]));
            //cStr[i] = &cStr[i][strlen(cStr[i]-1)];
            break;
        } else {
            argv[i] = (char*) malloc(strlen(cStr[i]) * sizeof(char));
            strcpy(argv[i], cStr[i]);
        }
    }
    argv[size] = NULL;

    return argv;
}

