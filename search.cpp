#include <bits/stdc++.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

#define BUFFER_SIZE 1024

bool isDirectory(string path)
{
    struct stat dirStat;
    if (stat(path.c_str(), &dirStat) == -1)
    {
        cout << "Error in getting the stat of file/folder.\n";
        return false;
    }

    if (S_ISDIR(dirStat.st_mode))
    {
        return true;
    }

    return false;
}

bool dfs(string fileName, string folderName)
{
    DIR *directory = opendir(folderName.c_str());
    if (directory == NULL)
    {
        return false;
    }

    struct dirent *dirInfo = readdir(directory);
    while (dirInfo != NULL)
    {
        string newFolder = folderName + "/" + dirInfo->d_name;

        if (dirInfo->d_name[0] != '.')
        {
            if (fileName == dirInfo->d_name)
            {
                closedir(directory);
                return true;
            }

            if (isDirectory(newFolder))
            {
                if (dfs(fileName, newFolder) == true)
                {
                    closedir(directory);
                    return true;
                }
            }
        }

        dirInfo = readdir(directory);
    }

    closedir(directory);
    return false;
}

void searchFile(char *firstArg, char *totalCommand)
{
    string fileName = "";
    char *buffer = strtok(totalCommand, " ");
    buffer = strtok(NULL, " ");
    fileName = buffer;

    char *currentDir = new char[BUFFER_SIZE];
    getcwd(currentDir, BUFFER_SIZE);

    string folderName = currentDir;
    if (dfs(fileName, folderName) == true)
    {
        cout << "True\n";
    }
    else
    {
        cout << "False\n";
    }
}