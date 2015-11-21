#include "parser.h"
#include "instructiontree.h"
#include "instruction.h"
#include "command.h"
#include "exit.h"
// used for handling commands
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <iostream>

using namespace std;

typedef tokenizer<escaped_list_separator<char> > so_tokenizer;

int main(void) {
    string s;
    char ** cStr;
    Instruction * instTree = NULL;
    InstructionTree tree;

    // parser test
    Parser parser;

    while (1) {

        // get input
        cout << "$ ";
        getline(cin, s);

        cStr = parser.tokenize(s);

        /*
        // test commands
        if (instTree != NULL)
            delete instTree;
        if (strcmp(cStr[0], "exit") == 0)
            instTree = new Exit();
        else
            instTree = new Command(tree.makeArgv(cStr));
        */

        instTree = tree.makeTree(cStr);
        
        // execute tree
        instTree->execute();
    }
}
