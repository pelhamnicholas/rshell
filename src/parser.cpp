#include "parser.h"

Parser::Parser() {
    tokLine = NULL;
    //cToken = NULL;
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
    try {
        cStr = (char **) malloc(size * sizeof(char*));
    } catch (...) {
        // Error handling
    }

    int j = 0;
    for (so_tokenizer::iterator i = tokLine->begin(); 
            i != tokLine->end(); ++i) {

        try {
            cStr[j] = (char*) malloc(strlen((*i).c_str()));//sizeof((*i).c_str()));
            strcpy(cStr[j++], (*i).c_str());
        } catch (...) {
            //cout << "Error allocating memory for individual cstring";
            //cout << endl;
        }
    }
    cStr[j] = NULL;

    return cStr;
}

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
