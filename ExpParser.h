#ifndef EXP_PARSER_H
#define EXP_PARSER_H

#include <iostream>
#include <cmath>
#include <iomanip>
#include "ArrayStack.h"

class ExpParser
{
    Array<char> op;

    double s2d(const string &s); //string to double
    Array<string> splitExp(const string &s);
    int getPriority(const string &opstr); //get priority of op ,included '('
    Array<string> toSuffixExp(Array<string> &expstr);
    string cal(string &num2, string &num1, const string &op);
    double calcSuffixExp(Array<string> suffixExp);
    bool isOp(const string &s); //check up the string if it is an op
    bool isOp(const char &s);   //ditto,check up the char
    bool isNumStr(string &s);   //check if it is a number string for negative numbers
    double __pow(double a, int b);

public:
    ExpParser();
    bool checkInput(string &str); //check if it is a illeage exp,included parenthesis matching
    double parse(string &exp);
};

#endif