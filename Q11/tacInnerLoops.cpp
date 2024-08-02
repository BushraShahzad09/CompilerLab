#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <sstream>
using namespace std;
int getJumpTarget(const string &instruction, const vector<string> &tac)
{
    stringstream ss(instruction);
    string op, arg1, arg2;
    ss >> op >> arg1;
    if (op == "goto" || op == "if")
    {
        ss >> arg2;
        try
        {
            return stoi(arg2) - 1;
        }
        catch (const invalid_argument &e)
        {
        }
    }
    return -1;
}
vector<vector<int>> findNaturalLoops(vector<string> &tac)
{
    vector<vector<int>> loops;
    set<int> visited;
    for (int i = 0; i < tac.size(); ++i)
    {
        if (visited.count(i) == 0)
        {
            visited.insert(i);
            vector<int> potentialLoop(i);
            int j = getJumpTarget(tac[i], tac);
            while (j != -1 && visited.count(j) == 0)
            {
                visited.insert(j);
                potentialLoop.push_back(j);
                j = getJumpTarget(tac[j], tac);
            }
            if (
                j == i)
            {
                loops.push_back(potentialLoop);
            }
        }
    }
    return loops;
}
int main()
{
    string filename = "TAC.txt";
    ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        cerr << "Error: Could not open file " << filename << endl;
        return 1;
    }
    vector<string> tac;
    string line;
    while (getline(inputFile, line))
    {
        tac.push_back(line);
    }
    inputFile.close();
    vector<vector<int>> loops = findNaturalLoops(tac);
    if (loops.empty())
    {
        cout << "No natural loops found in the TAC." << endl;
    }
    else
    {
        cout << "Natural loops found:" << endl;
        for (const vector<int> &loop : loops)
        {
            cout << " - Instructions: ";
            for (int instruction : loop)
            {
                cout << instruction + 1 << " ";
            }
            cout << endl;
        }
    }
    return 0;
}