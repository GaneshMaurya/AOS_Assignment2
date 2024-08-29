#include <bits/stdc++.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>
using namespace std;

#define BUFFER_SIZE 1024

void printCurrDirectory()
{
    char *currDirectory = (char *)malloc(BUFFER_SIZE);
    if (getcwd(currDirectory, 1024) == NULL)
    {
        printf("Error in retrieving current directory");
    }

    printf("%s\n", currDirectory);
}