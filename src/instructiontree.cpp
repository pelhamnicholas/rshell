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
        if (isOpenParen(cStr[i])) {
            for (unsigned int j = 0; j < strlen(cStr[i]) && 
                    isOpenParen(cStr[i][j]); ++j) {
                parenStack.push(cStr[i][j]);
            }
        }
        if (isCloseParen(cStr[i])) {
            if (parenStack.empty())
                return false;
            for (int j = strlen(cStr[i]) - 1; j >= 0 && 
                    isCloseParen(cStr[i][j]); --j) {
                for (int k = 0; k < NUMPARENS; ++k) {
                    if (cStr[i][j] == closeParen[k]) {
                        if (openParen[k] != parenStack.top())
                            return false;
                        else
                            parenStack.pop();
                    }
                }
            }
        }
    }
    return parenStack.empty();
}

/*
 * isConnector: returns true if a c style string represents a
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
    return isOpenParen(cStr[0]);
}

bool InstructionTree::isOpenParen(char ch) {
    for (int i = 0; i < NUMPARENS; ++i)
        if (ch == openParen[i])
            return true;
    return false;
}

/*
 * isCloseParen: returns true if a c style string ends with a
 *               closing parenthesis
 */
bool InstructionTree::isCloseParen(char * cStr) {
    return isCloseParen(cStr[strlen(cStr)-1]);
}

bool InstructionTree::isCloseParen(char ch) {
    for (int i = 0; i < NUMPARENS; ++i)
        if (ch == closeParen[i])
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
    //cStr[strlen(cStr) - 1] = '\0';
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
                cStr[i] = &cStr[i][1];
                i--; // to offset the for loop increment
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
                delete exit;
        // test command stuff
        } else if (strcmp(cStr[i], "test") == 0) {
            Test * test = new Test(makeArgv(&cStr[i]));
            while (cStr[i] != NULL && !isComment(cStr[i]) &&
                    !isConnector(cStr[i]) && !isCloseParen(cStr[i]))
                i++;
            i--; // to offset the for loop increment
            if (tree == NULL)
                tree = test;
            else if (tree->getConnector() != NULL) {
                ((Connector*)tree)->setRight(test);
            } else
                // error - cannot connect commands
                delete test;
        // test command stuff
        } else if (cStr[i][0] == '[') {
            if (cStr[i][1] != '\0')
                cStr[i] = &cStr[i][1];//removeOpenParen(cStr[i]);
            else
                i++;
            Test * test = new Test(makeArgv(&cStr[i], (char *) "]\0"));
            while (cStr[i] != NULL && !isComment(cStr[i]) &&
                    !isConnector(cStr[i])// && !isCloseParen(cStr[i])
                    && (cStr[i][strlen(cStr[i]) - 1] != ']'))
                i++;
            //i--; // to offset the for loop increment
            if (tree == NULL)
                tree = test;
            else if (tree->getConnector() != NULL)
                ((Connector*)tree)->setRight(test);
            else
                // error - cannot connect commands
                delete test;
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
                // error - cannot connect to a command
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
                delete cmd;
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
        if (isCloseParen(cStr[i])) {
            // get the size of the argument leading the closing parens
            unsigned int tmp_size;
            for (int j = 0; j < NUMPARENS; ++j) {
                for (tmp_size = 0; tmp_size < strlen(cStr[i]); 
                        ++tmp_size)
                    if (cStr[i][tmp_size] == closeParen[j])
                        break;
                if (cStr[i][tmp_size] == closeParen[j])
                    break;
            }
            // allocate space for argv
            if (tmp_size == 0) {
                argv[i] = NULL;
                break;
            }
            argv[i] = (char*) malloc((tmp_size+1) * sizeof(char));
            strncpy(argv[i], cStr[i], tmp_size);
            argv[i][tmp_size] = '\0';
            // change cStr to point to closing paren
            cStr[i] = &cStr[i][tmp_size];
            i--; // offset for the for loop from the call? 
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
        // there is no case for parentheses
        if (cStr[i][strlen(cStr[i])-1] == delim[0]) {
            if (strcmp(cStr[i], delim) == 0) {
                argv[i] = NULL;
                break;
            }
            // allocate space for argv[i]
            unsigned int tmp_size = strlen(cStr[i]);
            argv[i] = (char*) malloc(tmp_size * sizeof(char));
            strncpy(argv[i], cStr[i], tmp_size-1);
            argv[i][tmp_size-1] = '\0';
            break;
        } else {
            argv[i] = (char*) malloc(strlen(cStr[i]) * sizeof(char));
            strcpy(argv[i], cStr[i]);
        }
    }
    argv[size] = NULL;

    return argv;
}

