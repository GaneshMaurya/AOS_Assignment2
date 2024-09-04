#include <bits/stdc++.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

#include "header.h"
#define BUFFER_SIZE 1024

int inFd = STDIN_FILENO;
int outFd = STDOUT_FILENO;

void runIOCommand(string command)
{
    pid_t processId = fork();

    if (processId < 0)
    {
        printf("Error in creating child process.\n");
    }
    else if (processId == 0)
    {
        if (inFd != STDIN_FILENO)
        {
            dup2(inFd, STDIN_FILENO);
            close(inFd);
        }

        if (outFd != STDOUT_FILENO)
        {
            dup2(outFd, STDOUT_FILENO);
            close(outFd);
        }

        char *args[BUFFER_SIZE];
        int i = 0;
        char *temp = new char[BUFFER_SIZE];
        strcpy(temp, command.c_str());
        char *word = strtok(temp, " ");
        while (word != NULL)
        {
            args[i] = word;
            word = strtok(NULL, " ");
            i++;
        }
        args[i] = NULL;

        if (execvp(args[0], args) == -1)
        {
            printf("Error in executing %s command.\n", args[0]);
            exit(1);
        }
    }
    else
    {
        wait(NULL);
    }
}

void execPipeRedirection(string totalCommand)
{
    vector<string> command;
    stringstream ss(totalCommand);
    string temp;

    while (ss >> temp)
    {
        command.push_back(temp);
    }

    string cmd;

    for (int i = 0; i < command.size(); i++)
    {
        if (command[i] == "<")
        {
            string path = getCurrentDirectory() + (string) "/" + command[i + 1];
            inFd = open(path.c_str(), O_RDONLY);
            if (inFd < 0)
            {
                cout << "Error in opening the file.\n";
                return;
            }
            i++;
        }
        else if (command[i] == ">")
        {
            string path = getCurrentDirectory() + (string) "/" + command[i + 1];
            outFd = open(path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (outFd < 0)
            {
                cout << "Error in opening the file.\n";
                return;
            }
            i++;
        }
        else if (command[i] == ">>")
        {
            string path = getCurrentDirectory() + (string) "/" + command[i + 1];
            outFd = open(path.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (outFd < 0)
            {
                cout << "Error in opening the file.\n";
                return;
            }
            i++;
        }
        else
        {
            if (cmd.size() > 0)
            {
                cmd += " ";
            }
            cmd += command[i];
        }
    }

    cout << cmd << endl;

    runIOCommand(cmd);
}

void runPipeline(vector<char *> command)
{
    pid_t processId = fork();

    if (processId < 0)
    {
        printf("Error in creating child process.\n");
    }

    if (processId == 0)
    {
        if (inFd != STDIN_FILENO)
        {
            dup2(inFd, STDIN_FILENO);
            close(inFd);
        }

        if (outFd != STDOUT_FILENO)
        {
            dup2(outFd, STDOUT_FILENO);
            close(outFd);
        }

        bool ioFlag = false;
        char *args[BUFFER_SIZE];
        for (int i = 0; i < command.size(); i++)
        {
            if (command[i] == "<" || command[i] == ">")
            {
                ioFlag = true;
            }
            args[i] = command[i];
        }

        if (ioFlag == true)
        {
            string newCommand = "";
            for (int i = 0; i < command.size(); i++)
            {
                newCommand += command[i];
            }
            execPipeRedirection(newCommand);
        }
        else
        {
            if (execvp(command[0], args) == -1)
            {
                printf("Error in executing %s command.\n", command[0]);
            }
        }
    }
    else
    {
        wait(NULL);
    }
}

void execPipeIO(char *firstArg, char *totalCommand)
{
    vector<char *> allCommands;
    char *commands = strtok(totalCommand, "|");
    while (commands != NULL)
    {
        allCommands.push_back(commands);
        commands = strtok(NULL, "|");
    }

    vector<vector<char *>> tokens;
    for (auto it : allCommands)
    {
        vector<char *> temp;
        char *word = strtok(it, " ");
        while (word != NULL)
        {
            temp.push_back(word);
            word = strtok(NULL, " ");
        }
        tokens.push_back(temp);
    }

    int n = allCommands.size();
    int pipes[n - 1][2];
    for (int i = 0; i < n - 1; i++)
    {
        pipe(pipes[i]);
    }

    for (int i = 0; i < n - 1; i++)
    {
        if (i == 0)
        {
            inFd = STDIN_FILENO;
        }
        else
        {
            inFd = pipes[i - 1][0];
        }

        outFd = pipes[i][1];

        runPipeline(tokens[i]);
        close(outFd);
    }

    inFd = pipes[n - 2][0];
    outFd = STDOUT_FILENO;
    runPipeline(tokens[n - 1]);
}