#ifndef PARSER_H
#define PARSER_H

#include <boost/tokenizer.hpp>
#include <string>
#include <string.h>
#include "instruction.h"

using std::string;
using boost::tokenizer;
using boost::escaped_list_separator;

typedef tokenizer<escaped_list_separator<char> > so_tokenizer;

class Parser {
    private:
        so_tokenizer * tokLine;
        char ** cToken; // a null terminated array of cstrings

        //char ** get_cstrTokens(so_tokenize::iterator);

    public:
        Parser();
        ~Parser();
        int size();
        char ** get_cstrTokens();
        char ** tokenize(const string &);
        char ** tokenize(const char *);
};

#endif
