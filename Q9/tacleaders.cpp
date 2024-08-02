#include <bits/stdc++.h>

using namespace std;

int stoi(string &num)
{
    int ans = 0;
    for (int i = 0; i < num.size(); i++)
    {
        ans = ans * 10 + num[i] - '0';
    }
    return ans;
}

int main()
{
    ifstream myfile("TAC.txt", ios::in);
    int curr_line = 1;
    string line;
    vector<string> tac;
    set<int> leaders;
    leaders.insert(1);
    while (getline(myfile, line))
    {
        string temp;
        int sz = line.size();
        for (int i = 0; i < sz; i++)
        {
            if (line[i] != ' ')
                temp += line[i];
        }
        tac.push_back(temp);
        sz = temp.size();
        int pos = temp.find("goto");
        string num = "";
        if (pos != -1)
        {
            for (int i = pos + 5; temp[i] <= '9' and temp[i] >= '0'; i++)
            {
                num += temp[i];
            }
            int n = stoi(num);
            leaders.insert(n);
            leaders.insert(curr_line + 1);
        }
        curr_line++;
    }
    curr_line--;
    cout << "\nLEADERS\n";
    for (auto i : leaders)
    {
        if (i == curr_line + 1)
            leaders.erase(i);
        cout << i << " ";
    }
    cout << endl;
    vector<pair<int, int>> blocks;
    int p = -1;
    for (int i : leaders)
    {
        if (p != -1)
        {
            blocks.push_back({p, i - 1});
        }
        p = i;
    }
    blocks.push_back({p, curr_line});
    cout << "B1" << endl;
    cout << "-----------------" << endl;
    int count = 1;
    for (int i = 0; i < blocks.size(); i++)
    {
        for (int j = blocks[i].first - 1; j < blocks[i].second; j++)
        {
            cout << j + 1 << " " << tac[j] << endl;
        }
        cout << "-----------------" << endl;
        count++;
        if (i < blocks.size() - 1)
        {
            cout << endl
                 << "B" << count << endl;
            cout << "-----------------" << endl;
        }
    }
    return 0;
}
