#include "parser.h"

Parser::Parser() {
    tokLine = NULL;
}

Parser::~Parser() {
}

int Parser::size() {
    return distance(tokLine->begin(), tokLine->end());
}

char ** Parser::get_cstrTokens() {
    char ** cStr;

    // get size
    int size = distance(tokLine->begin(), tokLine->end()) + 1;
    // try catch
    cStr = (char **) malloc(size * sizeof(char*));

    int j = 0;
    for (so_tokenizer::iterator i = tokLine->begin(); 
            i != tokLine->end(); ++i) {
        // try catch
        cStr[j] = (char*) malloc(sizeof((*i).c_str()));
        strcpy(cStr[j++], (*i).c_str());
    }

    return cStr;
}

/*
char ** Parser::get_cstrTokens(so_tokenizer::iterator i) {
    char ** cStr;

    //get size
    int size = 0;
    for (so_tokenizer::iterator j = i; j != tokLine.end() 
            && !isConnector(*j) && !isComment(*j); ++j)
        size++;

    cStr = (char**) malloc((size+1) * sizeof(char*));
    int k = 0;
    for (so_tokenize::iterator j = i; j != tokLine.end()
            && !isConnector(*j) && !isComment(*j); ++j) {
        cStr[k] = (char*) malloc(sizeof((*j).cStr()));
        strcpy(cStr[k++], (*j).c_str());
    }
    cStr[k] = NULL;

    return cStr;
}
*/

char ** Parser::tokenize(const string & s) {
    if (tokLine != NULL)
        delete tokLine;
    tokLine = new so_tokenizer(s, 
            escaped_list_separator<char>('\\', ' ', '\"'));
    return get_cstrTokens();
}

char ** Parser::tokenize(const char * s) {
    string _s(s);
    
    return tokenize(_s);
}
