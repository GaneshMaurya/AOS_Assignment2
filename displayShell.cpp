#include <bits/stdc++.h>
#include <pwd.h>
using namespace std;

#define BUFFER_SIZE 1024

string getTerminalName(struct passwd userDetails, char *hostname, string workingDir)
{
    string terminal = userDetails.pw_name;
    terminal += '@';
    terminal += hostname;
    terminal += ':';
    terminal += workingDir;
    terminal += "> ";

    return terminal;
}

void startShell()
{
    while (1)
    {
        char *buffer = (char *)malloc(BUFFER_SIZE);

        struct passwd userDetails;
        struct passwd *result;

        uid_t userId = getuid();

        if (getpwuid_r(userId, &userDetails, buffer, BUFFER_SIZE, &result) < 0)
        {
            printf("Error. User not found");
            return;
        }

        char *hostname = (char *)malloc(BUFFER_SIZE);
        if (gethostname(hostname, BUFFER_SIZE) < 0)
        {
            printf("Error in getting the hostname");
        }

        char *currDirectory = (char *)malloc(BUFFER_SIZE);
        if (getcwd(currDirectory, 1024) == NULL)
        {
            printf("Error in retrieving current directory");
        }

        string terminalText = getTerminalName(userDetails, hostname, "~");

        cout << terminalText;
        string command;
        cin >> command;
        if (command == "exit")
        {
            break;
        }
    }

    return;
}