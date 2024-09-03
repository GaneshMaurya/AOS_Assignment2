#include <bits/stdc++.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fstream>
using namespace std;

#include "header.h"

#define printMax 10
#define BUFFER_SIZE 1024

string getHistoryPath()
{
    string path = getHome() + (string) "/history.txt";
    return path;
}

void initHistory(deque<char *> &commandList)
{
    string HISTORY_FILE = getHistoryPath();

    ifstream file(HISTORY_FILE);
    if (file.is_open() == true)
    {
        string line;
        while (getline(file, line))
        {
            char *temp = new char[BUFFER_SIZE];
            strcpy(temp, line.c_str());
            commandList.push_front(temp);
        }

        file.close();
    }
    else
    {
        printf("Error in creating the history file.\n");
        return;
    }
}

void writeHistoryToFile(deque<char *> &commandList)
{
    string HISTORY_FILE = getHistoryPath();

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
        num = stoi(temp) > commandList.size() ? commandList.size() : stoi(temp);
    }

    vector<char *> commands(commandList.begin(), commandList.end());
    for (int i = num - 1; i >= 0; i--)
    {
        cout << commands[i] << "\n";
    }
}