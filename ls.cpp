#include <bits/stdc++.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
using namespace std;

#include "header.h"

#define BUFFER_SIZE 1024

void printFiles(char *currDirectory)
{
    DIR *directory = opendir(currDirectory);
    struct dirent *dirInfo = readdir(directory);

    while (dirInfo != NULL)
    {
        if (dirInfo->d_name[0] != '.')
        {
            cout << dirInfo->d_name << "\t";
        }
        dirInfo = readdir(directory);
    }
    cout << "\n";

    closedir(directory);
}

void printHiddenFiles(char *currDirectory)
{
    DIR *directory = opendir(currDirectory);
    struct dirent *dirInfo = readdir(directory);

    while (dirInfo != NULL)
    {
        cout << dirInfo->d_name << "\t";
        dirInfo = readdir(directory);
    }
    cout << "\n";

    closedir(directory);
}

void execLs(char *firstArg, char *totalCommand)
{
    vector<char *> v;
    char *args = strtok(totalCommand, " ");
    while (args != NULL)
    {
        v.push_back(args);
        args = strtok(NULL, " ");
    }

    if (v.size() == 1)
    {
        // Only ls
        char *currDirectory = getCurrentDirectory();
        printFiles(currDirectory);
    }
    else if (v.size() == 2)
    {
        if (strcmp(v[1], ".") == 0)
        {
            // ls .
            char *currDirectory = getCurrentDirectory();
            printFiles(currDirectory);
        }
        else if (strcmp(v[1], "..") == 0)
        {
            char *currDirectory = getCurrentDirectory();
            string currDir = currDirectory;
            int end = currDir.size() - 1;
            while (currDir[end] != '/')
            {
                end--;
            }

            char *parentDirectory = new char[end];
            for (int i = 0; i < end; i++)
            {
                parentDirectory[i] = currDirectory[i];
            }

            if (end <= 0)
            {
                printFiles(currDirectory);
            }
            else
            {
                printFiles(parentDirectory);
            }
        }
        else if (strcmp(v[1], "~") == 0)
        {
            char *homeDirectory = getHome();
            printFiles(homeDirectory);
        }
        else if (strcmp(v[1], "-a") == 0)
        {
            char *currDirectory = getCurrentDirectory();
            printHiddenFiles(currDirectory);
        }
        else if (strcmp(v[1], "-l") == 0)
        {
            struct stat dirInfo;
            const char *currDir = getCurrentDirectory();

            if (stat(currDir, &dirInfo) == -1)
            {
                cout << "There is some error in getting the details of the folder.\n";
                return;
            }

            int total = 0;
            cout << "total " << total << "\n";

            char *username = (char *)malloc(BUFFER_SIZE);
            char *buffer = (char *)malloc(BUFFER_SIZE);

            DIR *directory = opendir(getCurrentDirectory());
            struct dirent *directoryInfo = readdir(directory);

            while (directoryInfo != NULL)
            {
                if (directoryInfo->d_name[0] != '.')
                {
                    struct stat fileInfo;
                    stat(currDir, &fileInfo);
                    cout << fileInfo.st_nlink << "\t";
                    cout << directoryInfo->d_name << "\t";
                    struct passwd userDetails;
                    struct passwd *result1;

                    getpwuid_r(dirInfo.st_uid, &userDetails, buffer, BUFFER_SIZE, &result1);
                    cout << userDetails.pw_name << "\t";

                    struct passwd groupDetails;
                    struct passwd *result2;

                    getpwuid_r(dirInfo.st_gid, &groupDetails, buffer, BUFFER_SIZE, &result2);
                    cout << userDetails.pw_name << "\t";
                }
                directoryInfo = readdir(directory);
                cout << "\n";
            }
        }
        else if (strcmp(v[1], "-la") == 0)
        {
        }
        else if (strcmp(v[1], "-al") == 0)
        {
        }
    }
    else
    {
    }
}