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

    string str = "-4*(-2)^2/2+0.5-0.25*0.5";
    ExpParser ep;
    double st = clock();
    for (int i = 0; i < 1e5; ++i)
        ep.parse(str);
    cout << ((double(clock()) - st) / CLOCKS_PER_SEC) << endl;
    //1e5 calls cost 1.12s
    return 0;
}

int main1()
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