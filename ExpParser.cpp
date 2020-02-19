#include "ExpParser.h"

ExpParser::ExpParser() : op()
{
    op.addLast('+');
    op.addLast('-');
    op.addLast('*');
    op.addLast('/');
    op.addLast('^');
    op.addLast('(');
    op.addLast(')');
}

bool ExpParser::isOp(string s)
{
    return op.contains(s[0]);
}

bool ExpParser::isOp(char s)
{
    return op.contains(s);
}

bool ExpParser::isNumStr(string s)
{
    for (char &c : s)
    {
        if (isdigit(c))
            return true;
    }
    return false;
}

bool ExpParser::checkInput(string &str)
{
    ArrayStack<char> as;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '(')
        {
            as.push(str[i]);
            continue;
        }
        else if (str[i] == ')')
        {
            if (!as.size())
            {
                return false;
            }
            else
            {
                as.pop();
            }
            continue;
        }

        if (str[i] != '.')
            if (!isdigit(str[i]) && !isOp(str[i]))
            {
                return false;
            }
    }
    if (as.size())
        return false;

    return true;
}

double ExpParser::s2d(string s)
{
    double res = 0.0;
    int sign = 1;
    int index = 0;
    if (s[0] == '-')
    {
        s.erase(0, 1);
        sign = -1;
    }
    if ((index = s.find('.')) == s.npos)
    {
        for (int i = s.size() - 1; i >= 0; i--)
        {
            res += (double)(s[i] - '0') * pow(10, s.size() - i - 1);
        }
    }
    else
    {
        for (int i = index - 1; i >= 0; i--)
        {
            res += (double)(s[i] - '0') * pow(10, index - i - 1);
        }
        for (int j = index + 1; j < s.size(); j++)
        {
            res += (double)(s[j] - '0') * pow(0.1, j - index);
        }
    }
    return res * sign;
}

Array<string> ExpParser::splitExp(string s)
{
    Array<string> tmp;
    for (int i = 0; i < s.size(); i++)
    {

        string num;
        while (isdigit(s[i]) || s[i] == '.')
        {
            num += s[i];
            i++;
        }
        if (num.size())
        {
            //cout << "str:" << num << endl;
            tmp.addLast(num);
        }
        if (isOp(s[i]))
        {

            string ss; // = to_string((char)s[i]);
            ss += s[i];
            tmp.addLast(ss);
            //cout << "op:" << s[i] << endl;
        }
    }

    //proc '-' op
    for (int i = 0; i < tmp.getSize(); i++)
    {
        if (i == 0 && tmp.getSize() > 1 && tmp[i] == "-" && isdigit(tmp[i + 1][0]))
        {
            tmp[i + 1].insert(0, "-");
            tmp.remove(i);
        }
        else if (i == 0 && tmp.getSize() > 1 && tmp[i] == "-" && tmp[i + 1][0] == '(')
        {
            string s = "0";
            tmp.addFirst(s);
        }
        else if (tmp[i] == "-" && i != 0 && !isdigit(tmp[i - 1].back()) && i != tmp.getSize() - 1 && isdigit(tmp[i + 1][0]))
        {
            if (isOp(tmp[i - 1]))
            {
                tmp[i + 1].insert(0, "-");
                tmp.remove(i);
            }
        }
    }
    //tmp.printAll();
    //cout << endl;

    return tmp;
}

int ExpParser::getPriority(string opstr)
{
    if (opstr.size() != 1)
    {
        cout << "getPriority error: " << opstr << endl;
        return 999;
    }
    int res = 0;
    char opchar = opstr[0];
    switch (opchar)
    {
    case '(':
        res = 0;
        break;

    case '^':
        res = 1;
        break;

    case '*':
    case '/':
        res = 2;
        break;

    case '+':
    case '-':
        res = 3;
        break;

    default:
        cout << "getPriority error: no match operator for " << opchar << endl;
        break;
    }

    return res;
}

Array<string> ExpParser::toSuffixExp(Array<string> &expstr)
{
    ArrayStack<string> opstk;
    ArrayStack<string> outstk;

    for (int i = 0; i < expstr.getSize(); i++)
    {
        if (isNumStr(expstr[i]))
        {
            outstk.push(expstr[i]);
            continue;
        }
        else
        {
            if (expstr[i][0] == '(')
            {
                opstk.push(expstr[i]);
                continue;
            }
            else if (expstr[i][0] == ')')
            {
                while (1)
                {
                    if (opstk.top()[0] == '(')
                    {
                        opstk.pop();
                        break;
                    }
                    else
                    {
                        outstk.push(opstk.pop());
                    }
                }
                continue;
            }
            else if (opstk.size() == 0 || getPriority(expstr[i]) < getPriority(opstk.top()) || opstk.top() == "(")
            {
                opstk.push(expstr[i]);
                continue;
            }
            else if (isOp(expstr[i]) && getPriority(expstr[i]) >= getPriority(opstk.top()))
            {
                while (opstk.size() != 0 && getPriority(expstr[i]) >= getPriority(opstk.top()))
                {
                    outstk.push(opstk.pop());
                    //i++;
                }
                opstk.push(expstr[i]);
            }
        }
    }
    int tmpsz = opstk.size();
    for (int i = 0; i < tmpsz; i++)
    {
        outstk.push(opstk.pop());
    }
    //cout << "outstk: " << outstk.size() << endl;
    //outstk.printAll();
    ArrayStack<string> tmpstk;
    Array<string> res;
    int size = outstk.size();
    for (int i = 0; i < size; i++)
    {
        tmpstk.push(outstk.pop());
    }
    while (tmpstk.size() != 0)
    {
        res.addLast(tmpstk.pop());
    }

    return res;
}

string ExpParser::cal(string &num2, string &num1, const string &op)
{
    //cout << "cal:" << num1 << "," << num2 << endl;
    double n1, n2, res;
    if (op.size() != 1)
    {
        cout << "cal error: " << op << endl;
        return "";
    }

    switch (op[0])
    {
    case '+':
        res = s2d(num1) + s2d(num2);
        break;

    case '-':
        res = s2d(num1) - s2d(num2);
        break;

    case '*':
        res = s2d(num1) * s2d(num2);
        break;

    case '/':
        res = s2d(num1) / s2d(num2);
        break;

    case '^':
        res = pow(s2d(num1), s2d(num2));
        break;

    default:
        cout << "cal error: not find operator for " << op[0] << endl;
        break;
    }
    return to_string(res);
}

double ExpParser::calcSuffixExp(Array<string> suffixExp)
{
    //suffixExp.printAll();
    string n1, n2, op;
    int sz = suffixExp.getSize();
    ArrayStack<string> tmp;
    for (int i = 0; i < sz; i++)
    {
        if (isNumStr(suffixExp[i]))
        {
            tmp.push(suffixExp[i]);
        }
        else if (isOp(suffixExp[i]))
        {
            n1 = tmp.pop();
            n2 = tmp.pop();
            tmp.push(cal(n1, n2, suffixExp[i]));
        }
    }
    //tmp.printAll();
    if (tmp.size() != 1)
    {
        cout << "calcSuffixExp error : size != 1" << endl;
        tmp.printAll();
    }
    return s2d(tmp.pop());
}

double ExpParser::parse(string &exp)
{
    Array<string> tmp = splitExp(exp);

    return calcSuffixExp(toSuffixExp(tmp));
}