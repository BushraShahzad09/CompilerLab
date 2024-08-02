#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> dfa;
int initialState;
string isAccepted(vector<vector<int>> &dfa, string input)
{
    string ans = "";
    int currentState = initialState;
    int i = 0;
    int n = input.size();
    int size = dfa[0].size();
    for (int i = 0; i < n; i++)
    {
        if (input[i] - '0' >= size)
            return "Invalid Input";
    }
    cout << "\nTransitions: ";
    cout << "q" << currentState << " ->";
    while (i < input.size() && currentState != -1)
    {
        int currentInput = input[i] - '0';
        if (currentInput == 0)
        {
            if (dfa[currentState][currentInput + 1] != -1)
                ans += (dfa[currentState][currentInput + 1]) + '0'; // dfa[currentState][1]
            currentState = dfa[currentState][currentInput];         // dfa[currentState][0]
        }
        else if (currentInput == 1)
        {
            if (dfa[currentState][currentInput + 2] != -1)
                ans += (dfa[currentState][currentInput + 2]) + '0'; // dfa[currentState][3]
            currentState = dfa[currentState][currentInput + 1];     // dfa[currentState][2]
        }
        if (currentState != -1)
            cout << "q" << currentState << " -> ";
        else
            cout << "Dead state";

        i++;
    }
    cout << endl;
    if (currentState == -1)
        return "Not Accepted and the output is " + ans;
    else
    {
        return "Accepted and the output is  " + ans;
    }
}
int main()
{
    fstream myfile("mealy.txt");
    string line;
    if (!myfile.is_open())
        cout << "Error opening file!\n";
    else
        cout << "File opened successfully!\n";
    cout << "Given DFA - \n";
    while (getline(myfile, line))
    {
        cout << line << endl;
    }
    myfile.clear();
    myfile.seekg(0);
    int currentLine = 0;
    while (getline(myfile, line))
    {
        if (currentLine == 0)
        {
            initialState = stoi(line);
        }
        else
        {
            int i = 0;
            vector<int> v;
            while (i < line.size())
            {
                if (line[i] == '-')
                {
                    v.push_back(-1);
                    i++;
                }
                else if (line[i] != '-' and line[i] != ' ')
                {
                    v.push_back(line[i] - '0');
                }
                i++;
            }
            dfa.push_back(v);
        }
        currentLine++;
    }
    string input;
    cout << "\nEnter input consisting of 0's and 1's: ";
    getline(cin, input);
    string ans = isAccepted(dfa, input);
    cout << endl;
    cout << ans << endl;

    return 0;
}