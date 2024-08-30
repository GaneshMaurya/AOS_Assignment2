#include <bits/stdc++.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

#define BUFFER_SIZE 1024

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
        struct stat dirStat;

        if (dirInfo->d_name[0] != '.')
        {
            if (fileName == dirInfo->d_name)
            {
                closedir(directory);
                return true;
            }

            if (stat(newFolder.c_str(), &dirStat) == 0)
            {
                if (S_ISDIR(dirStat.st_mode) == true)
                {
                    if (dfs(fileName, newFolder) == true)
                    {
                        closedir(directory);
                        return true;
                    }
                }
            }
            else
            {
                cout << "Error in getting stat of folder.\n";
                return false;
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