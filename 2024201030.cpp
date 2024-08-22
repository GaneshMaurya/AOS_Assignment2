#include <bits/stdc++.h>
#include <stdio.h>       // For printf and scanf
#include <sys/utsname.h> // For uname (To get info about the kernel)
#include <string.h>      // For strtok
#include <unistd.h>      // Fot hostname
#include <pwd.h>         // To get the username
#include <sys/types.h>
using namespace std;

bool containsHome(string directory)
{
    int n = directory.size();
    string res = "";
    for (int i = 0; i < 4; i++)
    {
        res += directory[i];
    }

    return res == "home";
}

void startShell()
{
    while (1)
    {
        char *buffer = (char *)malloc(1024);

        struct passwd userDetails;
        struct passwd *result;

        uid_t userId = getuid();

        if (getpwuid_r(userId, &userDetails, buffer, 1024, &result) < 0)
        {
            printf("Error. User not found");
            return;
        }

        char *hostname = (char *)malloc(1024);
        if (gethostname(hostname, 1024) < 0)
        {
            printf("Error in getting the hostname");
        }

        char *currDirectory = (char *)malloc(1024);
        if (getcwd(currDirectory, 1024) == NULL)
        {
            printf("Error in retrieving current directory");
        }

        string terminal = userDetails.pw_name;
        terminal += '@';
        terminal += hostname;
        terminal += ':';
        if (containsHome(currDirectory))
        {
            terminal += '~';
        }
        else
        {
            terminal += currDirectory;
        }
        terminal += "> ";

        cout << terminal;
        string command;
        cin >> command;
        if (command == "exit()")
        {
            break;
        }
    }

    return;
}

int main()
{
    startShell();

    return 0;
}