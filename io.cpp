#include <bits/stdc++.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <vector>
using namespace std;

#include "header.h"

#define BUFFER_SIZE 1024

void runCommand(string command, int input_fd, int output_fd)
{
    pid_t processId = fork();

    if (processId < 0)
    {
        printf("Error in creating child process.\n");
    }
    else if (processId == 0)
    {
        if (input_fd != STDIN_FILENO)
        {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }

        if (output_fd != STDOUT_FILENO)
        {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
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

void execRedirection(string totalCommand)
{
    vector<string> command;
    stringstream ss(totalCommand);
    string temp;

    while (ss >> temp)
    {
        command.push_back(temp);
    }

    // for (int i = 0; i < command.size(); i++)
    // {
    //     cout << command[i] << endl;
    // }

    int input_fd = STDIN_FILENO;
    int output_fd = STDOUT_FILENO;
    string cmd;

    for (int i = 0; i < command.size(); i++)
    {
        if (command[i] == "<")
        {
            string path = getCurrentDirectory() + (string) "/" + command[i + 1];
            input_fd = open(path.c_str(), O_RDONLY);
            if (input_fd < 0)
            {
                cout << "Error in opening the file.\n";
                return;
            }
        }
        else if (command[i] == ">")
        {
            string path = getCurrentDirectory() + (string) "/" + command[i + 1];
            output_fd = open(path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (output_fd < 0)
            {
                cout << "Error in opening the file.\n";
                return;
            }
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

    runCommand(cmd, input_fd, output_fd);
}