#include <bits/stdc++.h>
#include <sys/types.h>
#include <dirent.h>
using namespace std;

#define BUFFER_SIZE 1024
char *home = (char *)malloc(BUFFER_SIZE);
char *currDirectory = (char *)malloc(BUFFER_SIZE);

void setHome()
{
    if (getcwd(home, BUFFER_SIZE) == NULL)
    {
        printf("Error in retrieving current directory");
    }
}

char *getHome()
{
    return home;
}

void setCurrDirectory(char *path)
{
    strcpy(currDirectory, path);
    int n = strlen(currDirectory);
    if (currDirectory[n - 1] == '/')
    {
        currDirectory[n - 1] = '\0';
    }
}

char *getCurrentDirectory()
{
    return currDirectory;
}

bool isCurrDirHome()
{
    if (strcmp(getCurrentDirectory(), getHome()) == 0)
    {
        return true;
    }

    return false;
}