/*
 * Author: Nicholas Pelham
 * Date  : 11/21/2015
 *
 * instructiontree: used to create the tree of instructions
 */

// TO DO:
//    Handle comments at any point within a string
#include "instructiontree.h"

// adding parentheses can be done just by changing these
const char InstructionTree::openParen[NUMPARENS] = { '(' };
const char InstructionTree::closeParen[NUMPARENS] = { ')' };

InstructionTree::InstructionTree() {
    tree = NULL;
}

InstructionTree::~InstructionTree() {
    delete tree;
}

/*
 * hasValidParens: checks that an array of c style strings has
 *                 parentheses in the correct order and amount
 */
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

/*
 * isConnector: returns true is a c style string represents a
 *              connector
 */
bool InstructionTree::isConnector(char * cStr) {
    for (int i = 0; i < NUMCONNECTORS; ++i)
        if (strcmp(cStr, Connector::CONNECTOR[i]) == 0)
            return true;
    return false;
}

/*
 * isComment: returns true is a c style string begins with a comment
 *            ONLY WORKS FOR STRING WITH LEADING COMMENT
 */
bool InstructionTree::isComment(char * cStr) {
    if (cStr[0] == '#')
        return true;
    return false;
}

/*
 * isOpenParen: returns true if a c style string begins with an 
 *              opening parenthesis
 */
bool InstructionTree::isOpenParen(char * cStr) {
    for (int i = 0; i < NUMPARENS; ++i)
        if (cStr[0] == openParen[i])
            return true;
    return false;
}

/*
 * isCloseParen: returns true if a c style string ends with a
 *               closing parenthesis
 */
bool InstructionTree::isCloseParen(char * cStr) {
    for (int i = 0; i < NUMPARENS; ++i)
        if (cStr[strlen(cStr)-1] == closeParen[i])
            return true;
    return false;
}

/*
 * removeOpenParen: removes the opening character of a c
 *                  style string
 *                  used to remove opening parentheses
 */
char * InstructionTree::removeOpenParen(char * cStr) {
    return cStr+sizeof(char);
}

/*
 * removeCloseParen: removes the ending character of a c
 *                   style string
 *                   used to remove closing parentheses
 */
char * InstructionTree::removeCloseParen(char * cStr) {
    cStr[strlen(cStr) - 1] = '\0';
    return cStr;
}

/*
 * makeTree: creates a tree from the beginning of a c style
 *           string
 */
Instruction * InstructionTree::makeTree(char ** cStr) {
    int i = 0;

    if (!hasValidParens(cStr)) {
        cout << "Invalid parentheses amount/order" << endl;
        return tree;
    }

    return makeTree(cStr, i);
}

/*
 * makeTree: creates a tree from any point in an array of c style
 *           strings
 *           a reference to an integer is passed to synchronize 
 *           with the creation of subtrees using recursion
 */
Instruction * InstructionTree::makeTree(char ** cStr, int & i) {
    Instruction * tree = NULL;

    for ( ; cStr[i] != NULL; ++i) {
        if (isComment(cStr[i]))
            break;
        else if (isCloseParen(cStr[i])) {
            if (cStr[i][1] != '\0') {
                cStr[i] = removeCloseParen(cStr[i]);
                i--;
            }
            break;
        } else if (isConnector(cStr[i])) {
            Connector * conn = new Connector(cStr[i]);
            tree = conn->setLeft(tree);
        // exit command stuff
        } else if (strcmp(cStr[i], "exit") == 0) {
            Exit * exit = new Exit();
            if (tree == NULL) {
                tree = exit;
            } else if (tree->getConnector() != NULL) {
                ((Connector*)tree)->setRight(exit);
            } else
                // error - cannot connect commands
                ;
        // test command stuff
        } else if (strcmp(cStr[i], "test") == 0) {
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
            if (cStr[i][1] != '\0')
                cStr[i] = removeOpenParen(cStr[i]);
            Test * test = new Test(makeArgv(&cStr[i], (char *) "]\0"));
            while (cStr[i] != NULL && !isComment(cStr[i]) &&
                    !isConnector(cStr[i]) && !isCloseParen(cStr[i])
                    && (cStr[i][strlen(cStr[i]) - 1] != ']'))
                i++;
            i--;
            if (tree == NULL)
                tree = test;
            else if (tree->getConnector() != NULL)
                ((Connector*)tree)->setRight(test);
            else
                // error - cannot connect commands
                ;
        // create tree for parenthesis structure
        } else if (isOpenParen(cStr[i])) {
            if (cStr[i][1] != '\0')
                cStr[i] = removeOpenParen(cStr[i]);
            else
                ++i;
            if (tree == NULL)
                tree = makeTree(cStr, i);
            else if (tree->getConnector() != NULL) {
                ((Connector *)tree)
                        ->setRight(makeTree(cStr, i));
            } else
                // error - cannot connect to a comman
                ;
        // default command to use execvp()
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

/*
 * makeArgv: used to seperate a part of an arracy of c style strings
 *           into a new arracy to pass as arguments for a command
 */
char ** InstructionTree::makeArgv(char ** cStr) {
    char ** argv = NULL;
    int size = 0;
    while (cStr[size] != NULL && !isComment(cStr[size]) 
            && !isConnector(cStr[size]))
        size++;
    argv = (char**) malloc((size + 1) * sizeof(char*));

    for (int i = 0; cStr[i] != NULL && !isComment(cStr[i])
            && !isConnector(cStr[i]) ; ++i) {
        if (isOpenParen(cStr[i])) {
            argv[i] = (char*) malloc(
                    (strlen(cStr[i]) - 1) * sizeof(char));
            strcpy(argv[i], removeOpenParen(cStr[i]));
            cStr[i][0] = '(';
            cStr[i][1] = '\0';
        } else if (isCloseParen(cStr[i])) {
            argv[i] = (char*) malloc(
                    (strlen(cStr[i]) - 1) * sizeof(char));
            strcpy(argv[i], removeCloseParen(cStr[i]));
            cStr[i][0] = ')';
            cStr[i][1] = '\0';
            break;
        } else {
            argv[i] = (char*) malloc(strlen(cStr[i]) * sizeof(char));
            strcpy(argv[i], cStr[i]);
        }
    }
    argv[size] = NULL;

    return argv;
}

/*
 * makeArgv: used to create an array of arguments that ends at a special
 *           delimiting character
 */
char ** InstructionTree::makeArgv(char ** cStr, char * delim) {
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
        } else if (isCloseParen(cStr[i]) 
                || cStr[i][strlen(cStr[i])-1] == delim[0]) {
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

