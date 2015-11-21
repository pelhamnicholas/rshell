/*
 * Author: Nicholas Pelham
 * Date  : 11/21/2015
 *
 * Parser: doesn't actually do any real parsing
 *         tokenizes a c style string or a c++ string object
 *         takes into account quotations and allows them to be 
 *         included in tokens with the '\' character
 */
#include "parser.h"

Parser::Parser() {
    tokLine = NULL;
}

Parser::~Parser() {
}

/*
 * size: returns the size of the tokenizer 
 */
int Parser::size() {
    return distance(tokLine->begin(), tokLine->end());
}

/*
 * get_cstrTokens: returns the set of tokens as an array of 
 *                 c style strings
 */
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
            cStr[j] = (char*) malloc(strlen((*i).c_str()));
            strcpy(cStr[j++], (*i).c_str());
        } catch (...) {
            //cout << "Error allocating memory for individual cstring";
            //cout << endl;
        }
    }
    cStr[j] = NULL;

    return cStr;
}

/*
 * tokenize: tokenizes a c++ string object using boost::tokenizer
 */
char ** Parser::tokenize(const string & s) {
    if (tokLine != NULL)
        delete tokLine;
    tokLine = new so_tokenizer(s, 
            escaped_list_separator<char>('\\', ' ', '\"'));
    return get_cstrTokens();
}

/*
 * tokenize: tokenizes a c style string using boost::tokenizer
 */
char ** Parser::tokenize(const char * s) {
    string _s(s);
    
    return tokenize(_s);
}
