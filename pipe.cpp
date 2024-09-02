#include <bits/stdc++.h>
#include <sys/wait.h>
using namespace std;

#define BUFFER_SIZE 1024

void runPipe(vector<char *> command, int inFd, int outFd)
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

        char *args[BUFFER_SIZE];
        for (int i = 0; i < command.size(); i++)
        {
            args[i] = command[i];
        }

        cout << command[0] << endl;
        if (execvp(command[0], args) == -1)
        {
            printf("Error in executing %s command.\n", command[0]);
        }
    }
    else
    {
        wait(NULL);
    }
}

void execPipe(char *firstArg, char *totalCommand)
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
        cout << pipes[i][0] << " : " << pipes[i][1] << endl;
    }

    for (int i = 0; i < n - 1; i++)
    {
        int inFd;
        int outFd;

        if (i == 0)
        {
            inFd = STDIN_FILENO;
        }
        else
        {
            inFd = pipes[i - 1][0];
        }

        outFd = pipes[i][1];

        runPipe(tokens[i], inFd, outFd);
        close(outFd);
    }

    int inFd = pipes[n - 2][0];
    int outFd = STDOUT_FILENO;
    runPipe(tokens[n - 1], inFd, outFd);
}