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

void runCommand(string command, int inFd, int outFd)
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

    int inFd = STDIN_FILENO;
    int outFd = STDOUT_FILENO;
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

    runCommand(cmd, inFd, outFd);
}

// #include <bits/stdc++.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <sys/wait.h>
// #include <string>
// #include <algorithm>
// #include <cctype>
// #include <locale>
// using namespace std;

// #include "header.h"
// #define BUFFER_SIZE 1024

// void runRL(string left, string right, int fd)
// {
//     pid_t processId = fork();

//     if (processId < 0)
//     {
//         printf("Error in creating child process.\n");
//     }

//     if (processId == 0)
//     {
//         if (fd != STDIN_FILENO)
//         {
//             dup2(fd, STDIN_FILENO);
//             close(fd);
//         }

//         char *args[BUFFER_SIZE];
//         int i = 0;
//         char *temp = new char[BUFFER_SIZE];
//         strcpy(temp, left.c_str());
//         char *word = strtok(temp, " ");
//         while (word != NULL)
//         {
//             args[i] = word;
//             word = strtok(NULL, " ");
//             i++;
//         }
//         args[i] = NULL;

//         if (execvp(args[0], args) == -1)
//         {
//             printf("Error in executing %s command.\n", args[0]);
//         }
//     }
//     else
//     {
//         wait(NULL);
//     }
// }

// void runLR(string left, string right, int fd)
// {
//     pid_t processId = fork();

//     if (processId < 0)
//     {
//         printf("Error in creating child process.\n");
//     }

//     if (processId == 0)
//     {
//         if (fd != STDOUT_FILENO)
//         {
//             dup2(fd, STDOUT_FILENO);
//             close(fd);
//         }

//         char *args[BUFFER_SIZE];
//         int i = 0;
//         char *temp = new char[BUFFER_SIZE];
//         strcpy(temp, left.c_str());
//         char *word = strtok(temp, " ");
//         while (word != NULL)
//         {
//             args[i] = word;
//             word = strtok(NULL, " ");
//             i++;
//         }
//         args[i] = NULL;

//         if (execvp(args[0], args) == -1)
//         {
//             printf("Error in executing %s command.\n", args[0]);
//             exit(1);
//         }
//     }
//     else
//     {
//         wait(NULL);
//     }
// }

// void execRedirection(char *firstArg, char *totalCommand)
// {
//     // vector<string> commands;
//     // string word = "";
//     // for (int i = 0; i < strlen(totalCommand); i++)
//     // {
//     //     if (totalCommand[i] != '<' && totalCommand[i] != '>')
//     //     {
//     //         word += totalCommand[i];
//     //     }
//     //     else
//     //     {
//     //         commands.push_back(word);
//     //         string op = "";
//     //         op += totalCommand[i];
//     //         commands.push_back(op);
//     //         word = "";
//     //     }
//     // }

//     // if (!word.empty())
//     // {
//     //     commands.push_back(word);
//     // }

//     vector<string> commands;
//     string totCommand = totalCommand;
//     stringstream ss(totCommand);
//     cout << totCommand << endl;
//     string temp;

//     while (ss >> temp)
//     {
//         commands.push_back(temp);
//     }

//     // for (int i = 0; i < commands.size(); i++)
//     // {
//     //     cout << commands[i] << endl;
//     // }

//     for (int i = 0; i < commands.size(); i++)
//     {
//         if (commands[i] == "<")
//         {
//             string path = getCurrentDirectory() + (string) "/" + commands[i + 1];
//             int fd = open(path.c_str(), O_RDWR);
//             runRL(commands[i - 1], commands[i + 1], fd);
//         }
//         else if (commands[i] == ">")
//         {
//             string path = getCurrentDirectory() + (string) "/" + commands[i + 1];
//             int fd = open(path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
//             runLR(commands[i - 1], commands[i + 1], fd);
//         }
//         else if (commands[i] == ">>")
//         {
//             string path = getCurrentDirectory() + (string) "/" + commands[i + 1];
//             int fd = open(path.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
//             runLR(commands[i - 1], commands[i + 1], fd);
//         }
//     }
// }