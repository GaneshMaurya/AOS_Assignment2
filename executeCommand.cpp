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

bool containsPipe(char *str)
{
    int n = strlen(str);
    for (int i = 0; i < n; i++)
    {
        if (str[i] == '|')
        {
            return true;
        }
    }

    return false;
}

bool containsRedirection(char *str)
{
    int n = strlen(str);
    for (int i = 0; i < n; i++)
    {
        if (str[i] == '<' || str[i] == '>')
        {
            return true;
        }
    }

    return false;
}

pid_t processId;
pid_t foregroundProcessId = -1;
pid_t backgroundProcessId = -1;

void handleZ(int num)
{
    // Push foreground to background

    if (foregroundProcessId > 0 && foregroundProcessId != processId)
    {
        cout << "Terminated\n";
        kill(foregroundProcessId, SIGTSTP);
        backgroundProcessId = foregroundProcessId;
        foregroundProcessId = -1;
    }
}

void handleC(int num)
{
    // Interrupt the foreground process

    if (foregroundProcessId > 0)
    {
        cout << "Interrupted\n";
        kill(foregroundProcessId, SIGINT);
        foregroundProcessId = -1;
    }
}

int executeCommand(pid_t processId, char *firstArg, char *totalCommand, deque<char *> &commandList)
{
    signal(SIGINT, handleC);
    signal(SIGCONT, handleZ);

    if (containsPipe(totalCommand) == true)
    {
        // cout << totalCommand << endl;
        execPipe(firstArg, totalCommand);
    }
    else if (containsRedirection(totalCommand) == true)
    {
        string temp = totalCommand;
        execRedirection(temp);
        // cout << totalCommand << endl;
        // execRedirection(firstArg, totalCommand);
    }
    else if (containsLastAnd(totalCommand) == true)
    {
        // Background Process
        char *args[BUFFER_SIZE];
        int i = 0;
        char *tempCommand = strdup(totalCommand);

        char *word = strtok(tempCommand, " ");
        while (word != NULL)
        {
            if (strcmp(word, "&") != 0)
            {
                args[i] = word;
                i++;
            }
            word = strtok(NULL, " ");
        }
        args[i] = NULL;

        pid_t pid = fork();

        if (pid < 0)
        {
            printf("Error in creating child process.\n");
        }

        if (pid == 0)
        {
            if (setpgid(0, 0) < -1)
            {
                printf("Error.\n");
            }
            if (execvp(firstArg, args) == -1)
            {
                printf("Error in executing %s command.\n", firstArg);
            }
        }
        else
        {
            backgroundProcessId = pid;
            cout << backgroundProcessId << "\n";
        }
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
        // Foreground and default execvp

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

        pid_t pid = fork();
        if (pid < 0)
        {
            printf("Error in creating child process.\n");
        }

        if (pid == 0)
        {
            if (execvp(firstArg, args) < 0)
            {
                printf("Error in executing %s command.\n", firstArg);
            }
        }
        else
        {
            foregroundProcessId = pid;
            waitpid(foregroundProcessId, NULL, 0);
            foregroundProcessId = -1;
        }
    }

    if (foregroundProcessId > 0)
    {
        return foregroundProcessId;
    }
    else
    {
        return backgroundProcessId;
    }
}