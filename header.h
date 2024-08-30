void startShell(deque<char *> &commandList);

void executeCommand(char *firstArg, char *command, deque<char *> &commandList);

void printCurrDirectory();

void execEcho(char *command);

void initHistory(deque<char *> &commandList);

void printHistory(char *totalCommand, deque<char *> &commandList);

void writeHistoryToFile(deque<char *> &commandList);

void execLs(char *firstArg, char *totalCommand);

void setHome();

char *getHome();

char *getCurrentDirectory();

bool isCurrDirHome();

void setCurrDirectory(char *currDirectory);

void execCD(char *firstArg, char *totalCommand);

void searchFile(char *firstArg, char *totalCommand);