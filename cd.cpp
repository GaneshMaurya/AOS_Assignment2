#include <bits/stdc++.h>
#include <sys/types.h>
#include <dirent.h>
using namespace std;

#include "header.h"

#define BUFFER_SIZE 1024

void execCD(char *firstArg, char *totalCommand)
{
    char *dummy = strtok(totalCommand, " ");
    char *directoryName = strtok(NULL, " ");

    // Base case - only cd
    if (directoryName == NULL)
    {
        // Do nothing
    }
    else if (strcmp(directoryName, ".") == 0)
    {
        // Do nothing
    }
    else if (strcmp(directoryName, "~") == 0)
    {
        chdir(getHome());
        setCurrDirectory(getHome());
    }
    else if (strcmp(directoryName, "..") == 0)
    {
        chdir("..");
        char *parentDirectory = (char *)malloc(BUFFER_SIZE);
        getcwd(parentDirectory, BUFFER_SIZE);
        setCurrDirectory(parentDirectory);
    }
    else
    {
        if (directoryName[0] == '/')
        {
            if (chdir(directoryName) < 0)
            {
                cout << "Chdir failed.\n"
                     << endl;
                return;
            }
            setCurrDirectory(directoryName);
        }
        else
        {
            if (chdir(directoryName) < 0)
            {
                cout << "Chdir failed.\n"
                     << endl;
                return;
            }
            string temp = getCurrentDirectory();
            temp += '/';
            char *dummy = new char[BUFFER_SIZE];
            strcpy(dummy, temp.c_str());
            strcat(dummy, directoryName);
            setCurrDirectory(dummy);
        }
    }
}