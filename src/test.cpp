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
    int argc;
    for (argc = 0; argv[argc] != NULL; ++argc) ;

    char flag;
    if (argc == 1) {
        flag = 'e';
    } else {
        int flag_i;
        for (flag_i = 0; flag_i != argc && argv[flag_i][0] != '-'; ++flag_i) ;
        if (flag_i < argc)
            flag = argv[flag_i][1];
        else {
            cout << "Error: Improper test usage. Test command failed." << endl;
            return -1;
        }
    }

    stat(argv[argc-1], &sb);
    switch(flag) {
        case 'd':
            if (S_ISDIR(sb.st_mode))
                return 0;
            break;
        case 'f':
            if (S_ISREG(sb.st_mode))
                return 0;
            break;
        case 'e':
            if (S_ISREG(sb.st_mode) || S_ISDIR(sb.st_mode))
                return 0;
            break;
    }

    return 1;
}

