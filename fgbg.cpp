#include <bits/stdc++.h>
#include <sys/wait.h>
using namespace std;

#define BUFFER_SIZE 1024

void execBackground(char *firstArg, char *totalCommand)
{
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

    pid_t processId = fork();
    if (processId < 0)
    {
        printf("Error in creating child process.\n");
    }

    if (processId == 0)
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
        cout << processId << "\n";
    }
}