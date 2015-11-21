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

        if (instTree != NULL)
            delete instTree;
        instTree = tree.makeTree(cStr);
        
        // execute tree
        if (instTree != NULL)
            instTree->execute();
    }
}
