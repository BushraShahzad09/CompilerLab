#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

struct BasicBlock
{
  vector<string> instructions;
  unordered_set<string> genSet;
  unordered_set<string> killSet;
};

unordered_map<int, BasicBlock> basicBlocks;

void findLeaders(vector<int> &leaders)
{
  fstream myfile;
  myfile.open("tac_file.txt", ios::in);
  string line;
  int i = 1;
  while (getline(myfile, line))
  {
    size_t gotoPos = line.find("goto");
    if (gotoPos != string::npos)
    {
      leaders.push_back(stoi(line.substr(gotoPos + 6))); // Assuming the "goto" keyword is followed by line number without space
      leaders.push_back(i + 1);
    }
    i++;
  }
  sort(leaders.begin(), leaders.end());
  auto uniqueEnd = unique(leaders.begin(), leaders.end());
  leaders.erase(uniqueEnd, leaders.end());
  sort(leaders.begin(), leaders.end());
  myfile.close();
}

void printBlocks(vector<int> &leaders)
{
  fstream myfile;
  myfile.open("tac_file.txt", ios::in);
  string line;
  int j = 0, i = 0;
  while (getline(myfile, line))
  {
    if (find(leaders.begin(), leaders.end(), j + 1) != leaders.end())
    {
      // cout << "\nBlock " << j + 1 << ":" << endl;
      ++i;
    }
    basicBlocks[i].instructions.push_back(line);
    // cout << j + 1 << ": " << line << endl;
    ++j;
  }
  myfile.close();
}

void computeGen()
{
  // Iterate over each basic block
  for (auto &block : basicBlocks)
  {
    BasicBlock &currentBlock = block.second;

    // Initialize GEN set for the block
    unordered_set<string> genSet;

    // Iterate over each instruction in the block
    for (const string &instruction : currentBlock.instructions)
    {
      // Extract defined variable
      size_t equalPos = instruction.find('=');
      if (equalPos != string::npos)
      {
        string definedVar = instruction.substr(0, equalPos);
        if (definedVar.find("if") != string::npos)
        {
          break;
        }
        // Add definedVar to GEN set
        genSet.insert(definedVar);
      }
    }
    // Update GEN set for the block
    currentBlock.genSet = genSet;
  }
}

void computeKill()
{
  // Iterate over each basic block
  for (auto &block : basicBlocks)
  {
    BasicBlock &currentBlock = block.second;

    // Iterate over each variable in the current block's GEN set
    for (const string &var : currentBlock.genSet)
    {
      // Check if the variable is defined in another block
      for (const auto &otherBlock : basicBlocks)
      {
        if (&otherBlock != &block)
        {
          const BasicBlock &other = otherBlock.second;
          if (other.genSet.find(var) != other.genSet.end())
          {
            // If the variable is defined in another block, add it to the KILL set
            currentBlock.killSet.insert(var);
            break;
          }
        }
      }
    }
  }
}

int main()
{
  vector<int> leaders = {1};
  findLeaders(leaders);
  cout << "Leaders:\n"
       << endl;
  for (int i = 0; i < leaders.size(); i++)
  {
    cout << leaders[i] << " ";
  }
  cout << endl;
  printBlocks(leaders);

  for (int i = 1; i <= basicBlocks.size(); ++i)
  {
    auto it = basicBlocks.find(i);
    if (it != basicBlocks.end())
    {
      cout << "\nBlock " << it->first << " Instructions:" << endl;
      cout << "---------------------\n";
      for (const auto &instruction : it->second.instructions)
      {
        cout << instruction << endl;
      }
    }
  }
  cout << endl;

  computeGen();
  computeKill();

  // Print GEN and KILL sets for each block
  for (int i = 1; i <= basicBlocks.size(); ++i)
  {
    auto it = basicBlocks.find(i);
    if (it != basicBlocks.end())
    {
      cout << "Block " << it->first << " GEN Set:";
      for (const string &var : it->second.genSet)
      {
        cout << " " << var;
      }
      cout << endl;

      cout << "Block " << it->first << " KILL Set:";
      for (const string &var : it->second.killSet)
      {
        cout << " " << var;
      }
      cout << endl
           << endl;
    }
  }
}
