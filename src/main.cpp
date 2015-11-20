#include "parser.h"
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

    // parser test
    Parser parser;

    while (1) {

        cout << "$ ";
        getline(cin, s);

        // bad way of handling exit

        if (s == "exit")
            break;

        cStr = parser.tokenize(s);

        // handle command
        pid_t c_pid, pid;
        int status;
        int * error;

        error = new int(0);

        c_pid = fork();

        if (c_pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (c_pid == 0) {
            pid = getpid();

            cout << "execvp returned: " << execvp(cStr[0], cStr) << endl;
            //*error = execvp(temp[0], temp); // I think I'll need to return from here
            perror("Error executing");
            exit(12);
        } else if (c_pid > 0) {
            if ((pid = wait(&status)) < 0) {
                perror("wait");
                exit(1);
            }
        }
        cout << "error: " << *error << endl;
        cout << "status: " << status << endl;
 
        // free memory used by argv
        try {
            for (int i = 0; i < parser.size(); ++i)
                free(cStr[i]);
            free(cStr);
        } catch (...) {
            cout << "free error caught" << endl;
            continue;
        }
    }
}
