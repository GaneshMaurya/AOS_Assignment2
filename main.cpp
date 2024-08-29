#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>       // For printf and scanf
#include <sys/utsname.h> // For uname (To get info about the kernel)
#include <string.h>      // For strtok
#include <unistd.h>      // Fot hostname
#include <pwd.h>         // To get the username
#include <sys/types.h>
using namespace std;

#define BUFFER_SIZE 1024

#include "header.h"

deque<char *> commandList;

int main()
{
    setHome();
    char *currDirectory = (char *)malloc(BUFFER_SIZE);
    if (getcwd(currDirectory, 1024) == NULL)
    {
        printf("Error in retrieving current directory");
    }
    setCurrDirectory(currDirectory);
    startShell(commandList);
    return 0;
}