void startShell(deque<char *> &commandList);

void executeCommand(char *firstArg, char *command, deque<char *> &commandList);

void printCurrDirectory();

void execEcho(char *command);

void initHistory(deque<char *> &commandList);

void printHistory(char *totalCommand, deque<char *> &commandList);

void writeHistoryToFile(deque<char *> &commandList);