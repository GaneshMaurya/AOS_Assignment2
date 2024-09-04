#include <bits/stdc++.h>
#include <fstream>
using namespace std;

#define BUFFER_SIZE 1024

void execPinfo(char *firstArg, char *totalCommand)
{
    char *temp = strtok(totalCommand, " ");
    temp = strtok(NULL, " ");
    string ppid;

    if (temp == NULL)
    {
        pid_t pid = getpid();
        ppid = to_string(pid);
    }
    else
    {
        ppid = temp;
    }

    string processId = ppid;
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

        cout << "PID -- " << procData[0] << "\n";
        cout << "Process Status -- " << procData[2] << "\n";
        cout << "Memory -- " << procData[22] << " B\n";

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