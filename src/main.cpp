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

    // used for user@host prompt
    char * name, host[16], pwd[128];

    // parser
    Parser parser;

    while (1) {
        // get name@host:pwd
        name = getlogin();
        gethostname(host, sizeof(host));
        getcwd(pwd, sizeof(pwd));

        // get input
        cout << name << "@" << host << ":" << pwd << " $ ";
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
