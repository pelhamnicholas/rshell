// used for tokenizing and converting to argv
#include <string>
#include <string.h>
#include <boost/tokenizer.hpp>
// used for handling commands
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <iostream>

using namespace std;
using boost::tokenizer;
using boost::escaped_list_separator;

typedef tokenizer<escaped_list_separator<char> > so_tokenizer;

int main(void) {
    string s;
    char ** cStr;

    char * temp[64];
    while (1) {

        cout << "$ ";
        getline(cin, s);

        // bad way of handling exit

        if (s == "exit")
            break;

        // parsing input into tokens
        so_tokenizer tok(s, escaped_list_separator<char>('\\', ' ', '\"'));

        // create argv
        char ** temp;
        int size = distance(tok.begin(), tok.end()) + 1;
        try {
            temp = (char**)malloc(size * sizeof(char*));
        } catch (...) {
            cout << "malloc error caught" << endl;
            continue;
        }
        int j = 0;
        for (so_tokenizer::iterator i = tok.begin(); i != tok.end(); ++i) {
            //cout << *i << endl;
            //cout << (*i).c_str() << endl;

            try {
                temp[j] = (char*) malloc(sizeof((*i).c_str()));
                strcpy(temp[j++], (*i).c_str());
            } catch (...) {
                cout << "malloc error caught" << endl;
                continue;
            }
        }
        temp[j] = NULL;

        // print argv
        //for (int i = 0; temp[i] != NULL; ++i)
            //cout << temp[i] << endl;

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

            cout << "execvp returned: " << execvp(temp[0], temp) << endl;
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
            for (int i = 0; i < size; ++i)
                free(temp[i]);
            //free(temp);
        } catch (...) {
            cout << "free error caught" << endl;
            continue;
        }
    }
}
