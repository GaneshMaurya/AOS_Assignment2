#include <bits/stdc++.h>
#include <stdio.h>
#include <pwd.h>
#include <string.h> // For strtok
using namespace std;

#include "header.h"

#define BUFFER_SIZE 1024
#define historySize 20

pid_t pid = -1;

void handleZ(int num)
{
    if (pid != -1)
    {
        cout << "Terminated\n";
        kill(pid, SIGCONT);
        pid = 0;
    }
    cout << pid << endl;
}

void handleC(int num)
{
    if (pid != -1)
    {
        cout << "Interrupted\n";
        kill(pid, SIGINT);
        pid = 0;
    }
}

string getTerminalName(struct passwd userDetails, char *hostname, string workingDir)
{
    string terminal = userDetails.pw_name;
    terminal += '@';
    terminal += hostname;
    terminal += ':';
    terminal += workingDir;
    terminal += "> ";

    return terminal;
}

void startShell(deque<char *> &commandList)
{
    signal(SIGINT, handleC);
    signal(SIGCONT, handleZ);
    while (1)
    {
        char *buffer = (char *)malloc(BUFFER_SIZE);

        struct passwd userDetails;
        struct passwd *result;

        uid_t userId = getuid();

        if (getpwuid_r(userId, &userDetails, buffer, BUFFER_SIZE, &result) < 0)
        {
            printf("Error. User not found");
            return;
        }

        char *hostname = (char *)malloc(BUFFER_SIZE);
        if (gethostname(hostname, BUFFER_SIZE) < 0)
        {
            printf("Error in getting the hostname");
        }

        char *currDirectory = (char *)malloc(BUFFER_SIZE);
        if (getcwd(currDirectory, 1024) == NULL)
        {
            printf("Error in retrieving current directory");
        }

        char *workingDir = (char *)malloc(BUFFER_SIZE);

        if (isCurrDirHome())
        {
            strcpy(workingDir, "~");
        }
        else
        {
            char *temp = getCurrentDirectory();
            char *home = getHome();

            int n = strlen(temp);
            int m = strlen(home);

            char *extra = new char[BUFFER_SIZE];
            for (int i = m; i < n; i++)
            {
                extra[i - m] = temp[i];
            }

            workingDir = extra;
        }

        string terminalText = "";
        if (strcmp(workingDir, "") == 0)
        {
            // string curr = getCurrentDirectory();
            // curr = curr + '/';
            terminalText = getTerminalName(userDetails, hostname, getCurrentDirectory());
        }
        else
        {
            terminalText = getTerminalName(userDetails, hostname, workingDir);
        }

        cout << "\033[36m" << terminalText.c_str() << "\033[0m";
        string temp;
        getline(cin, temp);

        if (temp.empty())
        {
            if (cin.eof())
            {
                cout << "\n";
                return;
            }
            continue;
        }

        int start = 0;
        for (int i = 0; i < temp.size(); i++)
        {
            if (temp[i] != ' ' && temp[i] != '\t')
            {
                start = i;
                break;
            }
        }
        string temp2 = temp.substr(start, temp.size() - start);
        char *commands = new char[BUFFER_SIZE];
        strcpy(commands, temp2.c_str());

        // Tokenize the input
        char *command = strtok(commands, ";");
        if (strcmp(command, "exit") == 0)
        {
            if (commandList.size() < 20)
            {
                if (commandList.empty())
                {
                    commandList.push_front(command);
                }
                else if (strcmp(commandList.front(), command) != 0)
                {
                    commandList.push_front(command);
                }
            }
            else
            {
                commandList.pop_back();
                if (commandList.empty())
                {
                    commandList.push_front(command);
                }
                else if (strcmp(commandList.front(), command) != 0)
                {
                    commandList.push_front(command);
                }
            }
            return;
        }
        vector<char *> list;

        while (command != NULL)
        {
            if (strcmp(command, "exit") == 0)
            {
                if (commandList.size() < 20)
                {
                    if (commandList.empty())
                    {
                        commandList.push_front(command);
                    }
                    else if (strcmp(commandList.front(), command) != 0)
                    {
                        commandList.push_front(command);
                    }
                }
                else
                {
                    commandList.pop_back();
                    if (commandList.empty())
                    {
                        commandList.push_front(command);
                    }
                    else if (strcmp(commandList.front(), command) != 0)
                    {
                        commandList.push_front(command);
                    }
                }
                return;
            }

            if (commandList.size() < 20)
            {
                char *totalCommand = new char[BUFFER_SIZE];
                strcpy(totalCommand, temp2.c_str());
                if (commandList.empty())
                {
                    commandList.push_front(totalCommand);
                }
                else if (strcmp(commandList.front(), totalCommand) != 0)
                {
                    commandList.push_front(totalCommand);
                }
            }
            else
            {
                char *totalCommand = new char[BUFFER_SIZE];
                strcpy(totalCommand, temp2.c_str());
                commandList.pop_back();
                if (commandList.empty())
                {
                    commandList.push_front(totalCommand);
                }
                else if (strcmp(commandList.front(), totalCommand) != 0)
                {
                    commandList.push_front(totalCommand);
                }
            }
            list.push_back(command);
            command = strtok(NULL, ";");
        }

        for (auto listEl : list)
        {
            char *temp = strdup(listEl);
            char *firstArg = strtok(temp, " ");
            pid = executeCommand(firstArg, listEl, commandList);
        }
    }

    return;
}