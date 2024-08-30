#include <bits/stdc++.h>
#include <fstream>
using namespace std;

#define BUFFER_SIZE 1024

void execPinfo(char *firstArg, char *totalCommand)
{
    char *temp = strtok(totalCommand, " ");
    temp = strtok(NULL, " ");

    string processId = temp;
    string procFile = "/proc/" + processId + "/stat";
    ifstream file(procFile);

    vector<string> procData;
    if (file.is_open())
    {
        char *data = new char[BUFFER_SIZE];
        string temp;
        getline(file, temp);
        strcpy(data, temp.c_str());

        char *buffer = strtok(data, " ");
        while (buffer != NULL)
        {
            procData.push_back(string(buffer));
            buffer = strtok(NULL, " ");
        }

        cout << "pid -- " << procData[0] << "\n";
        cout << "Process Status -- " << procData[2] << "\n";
        cout << "memory -- " << procData[22] << "\n";

        string execPath = "/proc/" + processId + "/exe";
        char *execFile = new char[BUFFER_SIZE];
        int n = readlink(execPath.c_str(), execFile, BUFFER_SIZE);
        if (n != -1)
        {
            execFile[n] = '\0';
        }

        cout << "Executable Path -- " << execFile << "\n";
    }

    file.close();
}