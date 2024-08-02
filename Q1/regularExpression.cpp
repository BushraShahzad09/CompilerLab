#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;

int main()
{
    ifstream file("regularExpression.txt");
    if (!file.is_open())
    {
        cout << "Error opening file" << endl;
        return 1;
    }

    string line;
    string exp;
    while (getline(file, line))
    {
        exp += line;
    }
    cout << "Regular expression is " << exp << endl;
    regex regexp(exp);
    int type;
    while (1)
    {
        cout << "Enter 1 to check for a string." << endl;
        cout << "Enter 2 to exit." << endl;
        cin >> type;
        if (type == 1)
        {

            cout << "Give input string to check with the given regular expression" << endl;
            string input;
            cin >> input;

            if (regex_match(input, regexp))
            {
                cout << input;
                cout << " string accepted by the given regular expression" << endl;
            }

            else
            {
                cout << input;
                cout << " string not accepted by the given regular expression" << endl;
            }
        }
        else if (type == 2)
        {
            cout << "Exit" << endl;
            break;
        }
    }

    return 0;
}