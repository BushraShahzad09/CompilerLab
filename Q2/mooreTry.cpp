#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> dfa;
int initialState;
int convertToInt(string s)
{
    int num = 0;
    for (int i = 0; i < s.size(); i++)
    {
        num = num * 10 + (s[i] - '0');
    }
    return num;
}
vector<int> stringToVector(string &line)
{
    int i = 0;
    vector<int> v;
    while (i < line.size())
    {
        if (line[i] == '-')
        {
            int x = -1;
            v.push_back(x);
            i++;
        }
        else if (line[i] != '-' and line[i] != ' ')
        {
            v.push_back(line[i] - '0');
        }
        i++;
    }
    return v;
}
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
        ans += dfa[currentState][size - 1] + '0';
        currentState = dfa[currentState][input[i] - '0'];
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
        ans += dfa[currentState][size - 1] + '0';
        return "Accepted and the output is  " + ans;
    }
}
int main()
{
    fstream myfile("moore.txt");
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
        vector<int> temp;
        if (currentLine == 0)
        {
            initialState = convertToInt(line);
        }
        else
        {
            temp = stringToVector(line);
            dfa.push_back(temp);
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