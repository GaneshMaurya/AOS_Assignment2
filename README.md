# AOS_Assignment2

## The project requirement was to create a POSIX Shell Clone which mimics the Linux terminal and executes commands like cd, ls, echo, pwd, piping, IO redirection, etc.

### Some Important points regarding the files:
1. ### Main File: 
- It initializes the global variables required to run the terminal and then calls the ```displayShell()``` function to display the terminal promp and take inputs to run the commands.
- File associated = ```main.cpp```

2. ### Display Shell:
- This code handles the display part of the terminal. Here we have to get the username, hostname and current working directory and print the prompt.
- This file also takes the input from the user, tokenizes it (in case of semi colons) and then calls another function called ```executeCommand()``` to run execute the commands.
- File associated = ```displayShell.cpp```

3. ### Execute Command:
- This function acts as a redirect funtion which calls other functions according to the input that we give. 
- File associated = ```executeCommand.cpp```

4. ### Cd File:
- Based on the flags that we give to cd it changes the directory. If the directory given is not valid then an error is displayed. Else redirection takes place properly. ```cd <directory_name>```
- File associated = ```cd.cpp```

5. ### PWD File:
- This prints the path of the current working directory. ```pwd```
- File associated = ```pwd.cpp```

6. ### Echo File:
- Prints the values which we give after ```echo```. ```echo <some_input_text>```
- Printing of escape characters has been ignored. But spaces and tabs have been handled.
- File associated = ```echo.cpp```

7. ### Ls File:
- Ls command displays the files in the current directory and its details. Hidden files can also be displayed. ```ls <flags> <directories>```
- File associated = ```ls.cpp```

8. ### Background and Foreground:
- If we give an ```&``` after our command then it should open in the background and our terminal will not be usable.
- This case is handled using ```execvp()``` which should be run as a child process after forking the current process.
- In the case of foreground the parent process should keep waiting, in the case of background then the parent need not keep waiting.
- File associated = ```bg.cpp```

9. ### PInfo File:
- If ```pinfo()``` is run then the process id of the current foreground process is printed along with status, memory and executable path. 
- This fata is fetched from the ```proc``` file.
- If the process id is given as input along with pinfo then we have to print the details of that process. ```pinfo <pid>```
- File associated = ```pinfo.cpp```

10. ### Search:
- This command is used to search whether a file exists in the current or sub directories. 
- Initailly the current folder is checked and if file is found true is returned.
- Else it recursively checks all the subfolders and true is returned if found.
- Else false. ```search <filename>```
- File associated = ```search.cpp```

11. ### IO Redirection:
- There are 3 cases. 
1. ```>```: Run the command on the left and pass it's output into new/existing file. (The data in existing file should be truncated).
2. ```>>```: Run the command on the left and pass it's output into new/existing file. (The data in existing file should be appended).
3. ```<```: Run the command on the left and take the right part of ```<``` as input to the command.
- ```dup2()``` was used to update the input and output file descriptors in order to pass the input from left to right or right to left.
- File associated = ```io.cpp```

12. ### Pipeline File:
- This ensures that output of one command is given to the next command as input. 
- ```pipe()``` and ```dup2()``` was used to achieve this.
- File associated = ```pipe.cpp```

- ### Input Redirection using pipes:
- File associated = ```pipeio.cpp```

13. ### Signals:
-  Ctrl+D is used to log out of the shell. 
- Ctrl+C is used to interrupt the current foreground process.
- Ctrl+Z is used to stop a foreground process and push it into the background. ```kill()``` and ```signal()``` system calls are used to achieve this.

14. ### History File:
- All the commands are kept in a ```deque()``` and written onto a file when the ```history``` command is run. 
- This file keeps track of the commands run till now so that when a new session is opened then also the history commands are stored and can be displayed properly.
```history``` and ```history <num>```
- There is a limit of 10 commands that can be displayed when ```history``` is run and the file stores only 20 commands.
- File associated = ```history.cpp```

15. ### Miscellaneous Files:
- ```directories.cpp``` acts as a setter and getter file used to get and set current directory, home directory.
- File associated = ```directories.cpp```

#### Make File
- The ```make``` file contains all the names of the C++ files and compiles all these files at a time and generates a build file.
- File associated = ```makefile```

#### Header File
- Contains all the functions that are present separately in different folders. It makes sure that the functions can be called in any other file without any issues.
- File associated = ```header.h```

#### How to Run the file
- Run the below command
```make mainProg``` or ```make```.
- ```./a.out``` is already present in the make file, hence it is not required to run this command separately.