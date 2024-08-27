#include <bits/stdc++.h>
#include <string.h>
using namespace std;

#include "header.h"

void executeCommand(char *firstArg, char *command)
{
    if (strcmp(firstArg, "pwd") == 0)
    {
        printCurrDirectory();
    }
    else if (strcmp(firstArg, "history") == 0)
    {
        // printHistory();
    }
    else if (strcmp(firstArg, "echo") == 0)
    {
        execEcho(command);
    }
    else
    {
        // Execvp
    }
}