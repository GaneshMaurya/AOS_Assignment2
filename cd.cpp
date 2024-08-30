#include <bits/stdc++.h>
#include <sys/types.h>
#include <dirent.h>
using namespace std;

#include "header.h"

#define BUFFER_SIZE 1024
string prevDir = "";
string currentDir = "";

void execCD(char *firstArg, char *totalCommand)
{
    char *dummy = strtok(totalCommand, " ");
    char *directoryName = strtok(NULL, " ");

    if (prevDir == "" && currentDir == "")
    {
        currentDir = getCurrentDirectory();
        prevDir = getCurrentDirectory();
    }

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
        string temp = currentDir;
        chdir(getHome());
        setCurrDirectory(getHome());
        currentDir = getCurrentDirectory();
        prevDir = temp;
    }
    else if (strcmp(directoryName, "..") == 0)
    {
        string temp = currentDir;
        chdir("..");

        char *parentDirectory = (char *)malloc(BUFFER_SIZE);
        getcwd(parentDirectory, BUFFER_SIZE);
        setCurrDirectory(parentDirectory);

        currentDir = getCurrentDirectory();
        prevDir = temp;
    }
    else if (strcmp(directoryName, "-") == 0)
    {

        string temp = currentDir;

        char *redirectHere = new char[BUFFER_SIZE];
        strcpy(redirectHere, prevDir.c_str());

        chdir(redirectHere);
        setCurrDirectory(redirectHere);
        currentDir = getCurrentDirectory();
        prevDir = temp;
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
            string temp = currentDir;
            setCurrDirectory(directoryName);
            currentDir = getCurrentDirectory();
            prevDir = temp;
            cout << currentDir << endl;
            cout << prevDir << endl;
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

            string temp2 = currentDir;
            setCurrDirectory(dummy);
            currentDir = getCurrentDirectory();
            prevDir = temp2;
            cout << currentDir << endl;
            cout << prevDir << endl;
        }
    }
}