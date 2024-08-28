#include <bits/stdc++.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fstream>
using namespace std;

#define printMax 10

const char *HISTORY_FILE = "history.txt";

void initHistory(deque<char *> &commandList)
{
    ifstream file(HISTORY_FILE);
    if (file.is_open() == true)
    {
        string line;
        while (getline(file, line))
        {
            char *temp = new char[line.size() + 1];
            commandList.push_front(temp);
        }

        file.close();
    }
    else
    {
        return;
    }
}

void writeHistoryToFile(deque<char *> &commandList)
{
    ofstream file(HISTORY_FILE);
    if (file.is_open() == true)
    {
        int i = 0;
        int n = commandList.size();
        while (i < n)
        {
            file << commandList[i] << endl;
            i++;
        }

        file.close();
    }
    else
    {
        printf("Error in creating the history file.\n");
        return;
    }
}

void printHistory(char *totalCommand, deque<char *> &commandList)
{
    writeHistoryToFile(commandList);

    string temp = "";
    for (int i = 7; i < strlen(totalCommand); i++)
    {
        temp += totalCommand[i];
    }

    int num = commandList.size() > printMax ? printMax : commandList.size();
    if (temp.size() > 0)
    {
        num = stoi(temp);
    }

    vector<char *> commands(commandList.begin(), commandList.end());
    for (int i = 0; i < num; i++)
    {
        cout << commands[i] << "\n";
    }
}