#include <bits/stdc++.h>
#include <sys/wait.h> // For the wait command
#include <string.h>
using namespace std;

#include "header.h"
#define BUFFER_SIZE 1024

bool containsLastAnd(char *str)
{
    string command = str;
    string last;
    string temp = "";
    for (int i = 0; i < command.size(); i++)
    {
        if (command[i] == ' ')
        {
            last = temp;
            temp = "";
        }
        else
        {
            temp += command[i];
        }
    }
    last = temp;
    if (last == "&")
    {
        return true;
    }

    return false;
}

void executeCommand(char *firstArg, char *totalCommand, deque<char *> &commandList)
{
    if (strlen(totalCommand) > 0 && containsLastAnd(totalCommand) == true)
    {
        execBackground(firstArg, totalCommand);
    }
    else if (strcmp(firstArg, "pwd") == 0)
    {
        printCurrDirectory();
    }
    else if (strcmp(firstArg, "history") == 0)
    {
        printHistory(totalCommand, commandList);
    }
    else if (strcmp(firstArg, "echo") == 0)
    {
        execEcho(totalCommand);
    }
    else if (strcmp(firstArg, "ls") == 0)
    {
        execLs(firstArg, totalCommand);
    }
    else if (strcmp(firstArg, "cd") == 0)
    {
        execCD(firstArg, totalCommand);
    }
    else if (strcmp(firstArg, "search") == 0)
    {
        searchFile(firstArg, totalCommand);
    }
    else if (strcmp(firstArg, "pinfo") == 0)
    {
        execPinfo(firstArg, totalCommand);
    }
    else
    {
        char *args[BUFFER_SIZE];
        int i = 0;
        char *tempCommand = strdup(totalCommand);

        char *word = strtok(tempCommand, " ");
        while (word != NULL)
        {
            args[i] = word;
            i++;
            word = strtok(NULL, " ");
        }
        args[i] = NULL;

        pid_t processId = fork();
        if (processId < 0)
        {
            printf("Error in creating child process.\n");
        }

        if (processId == 0)
        {
            if (execvp(firstArg, args) < 0)
            {
                printf("Error in executing %s command.\n", firstArg);
            }
        }
        else
        {
            wait(NULL);
        }
    }
}