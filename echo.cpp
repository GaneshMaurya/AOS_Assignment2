#include <iostream>
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
        if (str[i] != ' ')
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
}

void printWithQuotes(char *command)
{
    string resultString = "";
    for (int i = 5; i < strlen(command); i++)
    {
        resultString += command[i];
    }

    cout << resultString << "\n";
}

void execEcho(char *command)
{
    // Default Case - without quotes
    if (containsQuotes(command) == false)
    {
        printWithoutQuotes(command);
    }
    else
    {
        printWithQuotes(command);
    }
}