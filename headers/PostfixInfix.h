//
// Created by arsanuos on 21/03/18.
//

#ifndef COMPILER_POSTFIXINFIX_H
#define COMPILER_POSTFIXINFIX_H

#include "NFA.h"
#include <string>
#include <map>
#include <stack>

class PostfixInfix {
private:
    std::map<string, NFA> def;
    string lastAssign;
    std::stack<string> chars;
    std::stack<NFA> nfas;
    std::stack<string> operations;
    vector<pair<string,NFA>> regular_exp;
    NFA eval(string operation, NFA a, NFA b);
    NFA eval_unary(string operation, NFA a);
    NFA calculate();
    NFA construct_regular_expression(vector<string> words);
    NFA construct_definition(vector<string> words);
    NFA result;

public:
    void regular_definitions(string name, vector<string> words);
    void regular_expressions(string name, vector<string> words);
    void Keyword(vector<string> words);
    void Punctuation(vector<string> words);
    void  collect();
    NFA  get_NFA();
};


#endif //COMPILER_POSTFIXINFIX_H
