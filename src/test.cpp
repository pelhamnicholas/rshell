/*
 * Author: Nicholas Pelham
 * Date  : 11/21/2015
 *
 * Test: tests if a file exists as a regular file or a directory
 *       based on arguments passed through the command line
 */
#include "test.h"

Test::Test() {
    argv = NULL;
}

Test::Test(char ** argv) {
    this->argv = argv;
}

/*
 * destructor: argv is allocated with c, so it's memory is
 *             deallocated using fre()
 */
Test::~Test() {
    for (int i = 0; argv[i] != NULL; ++i)
        free(argv[i]);
    free(argv);
}

/*
 * execute: uses POSIX stat() to test for a file whose path
 *          is stored in argv
 */
int Test::execute() {
    struct stat sb;

    // check for enough arguments
    int numargs = 0;
    for ( ; argv[numargs] != NULL; ++numargs) ;
    if (numargs < 2 || (numargs < 3 && (argv[0][0] == '[' 
                || strcmp(argv[0], "test") == 0))) {
        cout << "Invalid arguments: Must be \"test [flag] [file/path]\""
            << endl;
        return 1;
    }

    if (numargs == 2) {
        if (stat(argv[1], &sb) == -1) {
            cout << "Bad path: " << argv[1] << endl;
            return 1;
        }
    } else
        if (stat(argv[2], &sb) == -1) {
            cout << "Bad path: " << argv[2] << endl;
            return 1;
        }

    for (int i = 0; argv[numargs - 2][i] != '\0'; ++i) {
        switch(argv[numargs - 2][i]) {
            case 'd':
                if (S_ISDIR(sb.st_mode))// & S_IFMT == S_ISDIR)
                    return 0;
                break;
            case 'f':
                if (S_ISREG(sb.st_mode))// & S_IFMT == S_ISREG)
                    return 0;
                break;
            case 'e':
                if (S_ISREG(sb.st_mode) ||// & S_IFMT == S_ISREG) ||
                        S_ISDIR(sb.st_mode))// & S_IFMT == S_ISDIR))
                    return 0;
                break;
        }
    }

    return 1;
}

