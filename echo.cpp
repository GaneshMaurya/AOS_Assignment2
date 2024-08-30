#include <bits/stdc++.h>
using namespace std;

bool containsQuotes(char *command)
{

    for (int i = 0; i < strlen(command); i++)
    {
        if (command[i] == '\'')
        {
            return true;
        }
        else if (command[i] == '\"')
        {
            return true;
        }
    }

    return false;
}

vector<string> getWords(string str)
{
    vector<string> words;
    string word = "";

    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] != ' ' && str[i] != '\t')
        {
            word += str[i];
        }
        else
        {
            if (word.size() > 1)
            {
                words.push_back(word);
            }
            word = "";
        }
    }
    words.push_back(word);

    return words;
}

void printWithoutQuotes(char *command)
{
    string newCommand = command;
    vector<string> words = getWords(newCommand);

    for (int i = 1; i < words.size(); i++)
    {
        cout << words[i] << " ";
    }
    cout << "\n";
    // string resultString = "";
    // for (int i = 5; i < strlen(command); i++)
    // {
    //     resultString += command[i];
    // }

    // cout << resultString << "\n";
}

void printWithQuotes(char *command)
{
    int n = strlen(command);
    string com = command;
    string res = "";
    int i = 5;
    bool flag = false;
    bool flag1 = false;
    while (i < n)
    {
        if (com[i] == '\"' && flag == false)
        {
            flag = true;
            flag1 = false;
            res += com[i];
            i++;
            while (i < n && com[i] != '\"')
            {
                res += com[i];
                i++;
            }

            res += com[i];
            if (com[i] == '\"' && flag == true)
            {
                flag = false;
            }
        }
        else if (com[i] != ' ' && flag == false)
        {
            flag1 = false;
            res += com[i];
        }
        else if (com[i] == ' ' && flag == false)
        {
            if (flag1 == true)
            {
            }
            else
            {
                flag1 = true;
                res += com[i];
            }
        }
        i++;
    }
    cout << res << "\n";
}

void execEcho(char *command)
{
    // Default Case - without quotes
    if (containsQuotes(command) == false)
    {
        printWithoutQuotes(command);
        return;
    }
    else
    {
        printWithQuotes(command);
        return;
    }
}