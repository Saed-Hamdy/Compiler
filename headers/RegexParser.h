/*
 * RegexParser.h
 *
 *  Created on: Mar 18, 2018
 *      Author: saed
 */

#ifndef REGEXPARSER_H_
#define REGEXPARSER_H_

#include <bits/stdc++.h>
#include "Reader2.h"
#include "../headers/PostfixInfix.h"

using namespace std;


class RegexParser {

private:
	PostfixInfix p;
public:
	RegexParser();
	NFA parse_rules();
	virtual ~RegexParser();
	void regular_definitions(string name, string def);
	void regular_expressions(string name, string exp);
	void Keyword(string line);
	void Punctuation(string line);

};

#endif /* REGEXPARSER_H_ */
