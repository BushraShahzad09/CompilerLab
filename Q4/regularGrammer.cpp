#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>

using namespace std;
map<char, set<string>> mp;

bool solve(string &s, int idx, string toCheck)
{
    if (s.substr(idx) == toCheck)
        return true;
    else if (toCheck == "")
        return false;
    for (auto t : mp[toCheck[0]])
    {
        int sz = t.size(), i = idx, j = 0;
        while (j < sz && i < s.size() && s[i] == t[j])
        {
            i++, j++;
        }
        if (j == sz && solve(s, i, toCheck.substr(1)))
            return true;
        else if (j < sz && t[j] == '#' && solve(s, i, toCheck.substr(1)))
            return true;
        else if (j < sz && t[j] >= 'A' && t[j] <= 'Z' && solve(s, i, t.substr(j) + toCheck.substr(1)))
            return true;
    }
    return false;
}
string checkGrammar(string s = "")
{
    if (solve(s, 0, "S"))
        return "Accepted\n";
    return "Not Accepted\n";
}

int main()
{
    ifstream inputF("regularGrammer.txt");
    string t;
    while (getline(inputF, t))
    {
        string x;
        for (int i = 3; i < t.size(); i++)
        {
            if (t[i] != '|')
                x.push_back(t[i]);
            else
            {
                mp[t[0]].insert(x);
                x = "";
            }
        }
        mp[t[0]].insert(x);
    }
    for (auto ch : mp)
    {
        cout << ch.first << "-> ";
        for (auto t : mp[ch.first])
            cout << t << "| ";
        cout << endl;
    }
    while (true)
    {
        cout << "Enter a string : ";
        string s;
        cin >> s;
        if (s == "exit")
            break;
        cout << checkGrammar(s) << endl;
    }
    return 0;
}