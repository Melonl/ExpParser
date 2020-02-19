#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include "ArrayStack.h"
#include "ArrayStack.cpp"
#include "ExpParser.h"
#include "ExpParser.cpp"


using namespace std;

int main()
{
    string str;
    ExpParser ep;
    cout << "Please input a legal mathematical expression." << endl
         << "Input number 0 to exit the program. " << endl;
    while (cin.peek() != EOF)
    {
        cin >> str;
        if (str.size() == 1 && str[0] - '0' == 0)
            break;
        if (!ep.checkInput(str))
        {
            cout << str << endl;
            cout << "illeagal input." << endl;
            continue;
        }
        cout << setprecision(16) << ep.parse(str) << endl;
    }
    return 0;
}