//
// Created by arsanuos on 21/03/18.
//

#define ccat "concat"

#include "../headers/PostfixInfix.h"
#include "../headers/Construction.h"
#include "../headers/OperationHandler.h"
#include "../headers/Evaluator.h"
#include <iostream>

void PostfixInfix::regular_definitions(string name, vector<string> words) {

    NFA definition = construct_definition(words);
    def.insert(pair<string, NFA>(name, definition));

}
void PostfixInfix::regular_expressions(string name, vector<string> words) {
    NFA expression = construct_regular_expression(words);
    regular_exp.push_back(pair<string, NFA>(name, expression));
}

void PostfixInfix::Keyword(vector<string> words) {
    for(int i = 0 ;i < words.size(); i++){
        vector<string> tmp;
        for(int j = 0 ;j < words[i].size(); j++){
            string p(1, words[i][j]);
            tmp.push_back(p);
        }
        regular_definitions(words[i], tmp);
    }

}
void PostfixInfix::Punctuation(vector<string> words) {
    for(int i = 0 ;i < words.size(); i++){
        vector<string> tmp;
        tmp.push_back(words[i]);
        regular_definitions(words[i],tmp);
    }
}

void PostfixInfix::collect(){
    for(int i = 0 ;i < regular_exp.size(); i++){
        regular_exp[i].second.getEndNode().addAcceptance(pair<int, string>(regular_exp.size() - i, regular_exp[i].first));
        result = Evaluator::oring(result, regular_exp[i].second);
    }
}

NFA PostfixInfix::get_NFA(){
    return result;
}

NFA PostfixInfix::construct_definition(vector<string> words){
    bool last_is_char = false;
    bool last_is_unary = false;
    for(int i = 0 ;i < words.size(); i++){
        if(words[i].size() == 1 && isalnum(words[i].at(0))){
            chars.push(words[i]);
            nfas.push(Construction::construct(words[i]));
            if(last_is_char || last_is_unary){
                while(operations.size() > 0 && OperationHandler::precedence(ccat) <= OperationHandler::precedence(operations.top())){
                    calculate();
                }
                operations.push(ccat);
            }
            last_is_char = true;
        }else if(OperationHandler::isOperation(words[i])){
            if(words[i] == ")"){
                string op = operations.top();
                do{
                    calculate();
                    op = operations.top();
                }while(op != "(");
                operations.pop();
            }else{
                if(OperationHandler::isUnary(words[i])){
                    operations.push(words[i]);
                    calculate();
                    last_is_unary = true;
                }else{
                    while(operations.size() > 0 && OperationHandler::precedence(words[i]) <= OperationHandler::precedence(operations.top())){
                        calculate();
                    }
                    operations.push(words[i]);
                    last_is_unary = false;
                }
            }
            last_is_char = false;
        }else {
            throw "non-classified char";
        }
    }
    while(operations.size() != 0){
        calculate();
    }

    NFA result = nfas.top();
    nfas.pop();
    return result;
}


NFA PostfixInfix::eval(string operation, NFA a, NFA b){
    if(operation == ccat){
        return Evaluator::concat(a, b);
    }else if(operation == "|"){
        return Evaluator::oring(a, b);
    }else if(operation == "-"){
        return Evaluator::dash(a, b);
    }
    throw "non determined operation";
}

NFA PostfixInfix::eval_unary(string operation, NFA a){
    if(operation == "*"){
        return Evaluator::star(a);
    }else if(operation == "+"){
        return Evaluator::plus(a);
    }
    throw "non determined unary operation";
}


NFA PostfixInfix::calculate(){
    string operation = operations.top();
    operations.pop();
    string x1 = chars.top();chars.pop();
    NFA a = nfas.top();nfas.pop();
    if(OperationHandler::isUnary(operation)){
        NFA operation_result = eval_unary(operation, a);
        string operation_string = x1 + operation;
        nfas.push(operation_result);
        chars.push(operation_string);
    }else{
        string x2 = chars.top();chars.pop();
        string operation_string = x2 + operation + x1;
        NFA b = nfas.top();nfas.pop();
        NFA operation_result = eval(operation ,b ,a);
        nfas.push(operation_result);
        chars.push(operation_string);
    }
}



NFA PostfixInfix::construct_regular_expression(vector<string> words) {
    bool last_is_char = false;
    bool last_is_unary = false;
    for(int i = 0 ;i < words.size(); i++){
        map<string, NFA>::iterator tmp = def.find(words[i]);
        if(tmp == def.end()){
            //definition found
            chars.push(words[i]);
            nfas.push(tmp->second);
            if(last_is_char || last_is_unary){
                while(operations.size() > 0 && OperationHandler::precedence(ccat) <= OperationHandler::precedence(operations.top())){
                    calculate();
                }
                operations.push(ccat);
            }
            last_is_char = true;
        }else if(words[i].size() == 1 && isalnum(words[i].at(0))){
            chars.push(words[i]);
            nfas.push(Construction::construct(words[i]));
            if(last_is_char || last_is_unary){
                while(operations.size() > 0 && OperationHandler::precedence(ccat) <= OperationHandler::precedence(operations.top())){
                    calculate();
                }
                operations.push(ccat);
            }
            last_is_char = true;
        }else if(OperationHandler::isOperation(words[i])){
            if(words[i] == ")"){
                string op = operations.top();
                do{
                    calculate();
                    op = operations.top();
                }while(op != "(");
                operations.pop();
            }else{
                if(OperationHandler::isUnary(words[i])){
                    operations.push(words[i]);
                    calculate();
                    last_is_unary = true;
                }else{
                    while(operations.size() > 0 && OperationHandler::precedence(words[i]) <= OperationHandler::precedence(operations.top())){
                        calculate();
                    }
                    operations.push(words[i]);
                    last_is_unary = false;
                }
            }
            last_is_char = false;
        }else {
            throw "non-classified char";
        }
    }
    while(operations.size() != 0){
        calculate();
    }

    NFA result = nfas.top();
    nfas.pop();
    return result;
}
