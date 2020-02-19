#ifndef EXP_PARSER_H
#define EXP_PARSER_H

#include <iostream>
#include <cmath>
#include <iomanip>
#include "ArrayStack.h"

class ExpParser
{
    Array<char> op;

    double s2d(string s); //string to double
    Array<string> splitExp(string s);
    int getPriority(string opstr); //get priority of op ,included '('
    Array<string> toSuffixExp(Array<string> &expstr);
    string cal(string &num2, string &num1, const string &op);
    double calcSuffixExp(Array<string> suffixExp);
    bool isOp(string s);     //check up the string if it is an op
    bool isOp(char s);       //ditto,check up the char
    bool isNumStr(string s); //check if it is a number string for negative numbers
public:
    ExpParser();
    bool checkInput(string &str); //check if it is a illeage exp,included parenthesis matching
    double parse(string &exp);
};

#endif