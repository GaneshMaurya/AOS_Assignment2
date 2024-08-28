#include <bits/stdc++.h>
#include <stdio.h>
#include <pwd.h>
#include <string.h> // For strtok
using namespace std;

#include "header.h"

#define BUFFER_SIZE 1024

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

        string terminalText = getTerminalName(userDetails, hostname, "~");

        printf("%s", terminalText.c_str());
        string temp;
        getline(cin, temp);
        char *commands = new char[temp.length() + 1];
        strcpy(commands, temp.c_str());

        // Tokenize the input
        char *command = strtok(commands, ";");
        vector<char *> list;

        while (command != NULL)
        {
            if (strcmp(command, "exit") == 0)
            {
                return;
            }

            commandList.push_front(command);
            list.push_back(command);
            command = strtok(NULL, ";");
        }

        for (auto listEl : list)
        {
            char *temp = strdup(listEl);
            char *firstArg = strtok(temp, " ");
            executeCommand(firstArg, listEl);
        }
    }

    return;
}