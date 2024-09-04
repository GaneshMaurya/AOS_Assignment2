void startShell(deque<char *> &commandList);

int executeCommand(pid_t processId, char *firstArg, char *command, deque<char *> &commandList);

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

void execPinfo(char *firstArg, char *totalCommand);

int execBackground(char *firstArg, char *totalCommand);

void execPipe(char *firstArg, char *totalCommand);

void execRedirection(string totalCommand);

// void execRedirection(char *firstArg, char *totalCommand);

void handleZ(int num);

void handleC(int num);