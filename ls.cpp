#include <bits/stdc++.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>
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

string permissions(struct stat fileInfo)
{
    mode_t mode = fileInfo.st_mode;
    string perm = "----------";

    if (S_ISDIR(mode) == 1)
    {
        perm[0] = 'd';
    }
    if (mode & 0400)
    {
        perm[1] = 'r';
    }
    if (mode & 0200)
    {
        perm[2] = 'w';
    }
    if (mode & 0100)
    {
        perm[3] = 'x';
    }
    if (mode & 0040)
    {
        perm[4] = 'r';
    }
    if (mode & 0020)
    {
        perm[5] = 'w';
    }
    if (mode & 0010)
    {
        perm[6] = 'x';
    }
    if (mode & 0004)
    {
        perm[7] = 'r';
    }
    if (mode & 0002)
    {
        perm[8] = 'w';
    }
    if (mode & 0001)
    {
        perm[9] = 'x';
    }

    return perm;
}

void printTime(struct stat fileInfo)
{
    struct tm *info = localtime(&fileInfo.st_mtime);
    char *time = new char[BUFFER_SIZE];
    strftime(time, BUFFER_SIZE, "%b %d %H:%M", info);

    cout << time << "\t";
}

void displayHiddenLs(const char *currDir)
{
    struct stat dirInfo;
    // const char *currDir = getCurrentDirectory();

    if (stat(currDir, &dirInfo) == -1)
    {
        cout << "There is some error in getting the details of the folder.\n";
        return;
    }

    int total = 0;
    cout << "total " << dirInfo.st_blocks << "\n";

    char *username = (char *)malloc(BUFFER_SIZE);
    char *buffer = (char *)malloc(BUFFER_SIZE);

    DIR *directory = opendir(getCurrentDirectory());
    struct dirent *directoryInfo = readdir(directory);

    while (directoryInfo != NULL)
    {
        struct stat fileInfo;
        string fname = directoryInfo->d_name;
        string path = getCurrentDirectory() + (string) "/" + fname;

        stat(path.c_str(), &fileInfo);
        string perms = permissions(fileInfo);
        cout << perms << "\t";

        cout << fileInfo.st_nlink << "\t";

        struct passwd userDetails;
        struct passwd *result1;

        getpwuid_r(dirInfo.st_uid, &userDetails, buffer, BUFFER_SIZE, &result1);
        cout << userDetails.pw_name << "\t";

        struct passwd groupDetails;
        struct passwd *result2;

        getpwuid_r(dirInfo.st_gid, &groupDetails, buffer, BUFFER_SIZE, &result2);
        cout << userDetails.pw_name << "\t";
        cout << fileInfo.st_size << "\t";

        printTime(fileInfo);
        cout << directoryInfo->d_name << "\t";

        cout << "\n";
        directoryInfo = readdir(directory);
    }

    closedir(directory);
}

void displayLs(const char *currDir)
{
    struct stat dirInfo;
    // const char *currDir = getCurrentDirectory();

    if (stat(currDir, &dirInfo) == -1)
    {
        cout << "There is some error in getting the details of the folder.\n";
        return;
    }

    int total = 0;
    cout << "total " << dirInfo.st_blocks << "\n";

    char *username = (char *)malloc(BUFFER_SIZE);
    char *buffer = (char *)malloc(BUFFER_SIZE);

    DIR *directory = opendir(getCurrentDirectory());
    struct dirent *directoryInfo = readdir(directory);

    while (directoryInfo != NULL)
    {
        if (directoryInfo->d_name[0] != '.')
        {
            struct stat fileInfo;
            string fname = directoryInfo->d_name;
            string path = getCurrentDirectory() + (string) "/" + fname;

            stat(path.c_str(), &fileInfo);
            string perms = permissions(fileInfo);
            cout << perms << "\t";

            cout << fileInfo.st_nlink << "\t";

            struct passwd userDetails;
            struct passwd *result1;

            getpwuid_r(dirInfo.st_uid, &userDetails, buffer, BUFFER_SIZE, &result1);
            cout << userDetails.pw_name << "\t";

            struct passwd groupDetails;
            struct passwd *result2;

            getpwuid_r(dirInfo.st_gid, &groupDetails, buffer, BUFFER_SIZE, &result2);
            cout << userDetails.pw_name << "\t";
            cout << fileInfo.st_size << "\t";

            printTime(fileInfo);
            cout << directoryInfo->d_name << "\t";

            cout << "\n";
        }
        directoryInfo = readdir(directory);
    }

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
            const char *currDir = getCurrentDirectory();
            displayLs(currDir);
        }
        else if (strcmp(v[1], "-la") == 0)
        {
            const char *currDir = getCurrentDirectory();
            displayHiddenLs(currDir);
        }
        else if (strcmp(v[1], "-al") == 0)
        {
            const char *currDir = getCurrentDirectory();
            displayHiddenLs(currDir);
        }
    }
    else if (v.size() == 3)
    {
        if (strcmp(v[1], "-a") == 0 && strcmp(v[2], "-l"))
        {
            const char *currDir = getCurrentDirectory();
            displayHiddenLs(currDir);
        }
        else if (strcmp(v[1], "-l") == 0 && strcmp(v[2], "-a"))
        {
            const char *currDir = getCurrentDirectory();
            displayHiddenLs(currDir);
        }
    }
    else
    {
    }
}