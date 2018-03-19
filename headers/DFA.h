//
// Created by default on 19/03/18.
//

#ifndef COMPILER_DFA_H
#define COMPILER_DFA_H


#include "Node.h"

class DFA {

public:
    const vector<Node> &getDfaGraph() const;
    void convert_from_NFA_to_DFA();

private:
    vector<Node> dfaGraph;
};


#endif //COMPILER_DFA_H