/****************
LE2: Introduction to Unnamed Pipes
****************/
#include <unistd.h> // pipe, fork, dup2, execvp, close
#include <iostream> // cout, endl
using namespace std;

int main () {
    // lists all the files in the root directory in the long format
    char* cmd1[] = {(char*) "ls", (char*) "-al", (char*) "/", nullptr};
    // translates all input from lowercase to uppercase
    char* cmd2[] = {(char*) "tr", (char*) "a-z", (char*) "A-Z", nullptr};

    // TODO: add functionality
    // Create pipe
    int RW[2];
    pipe(RW);

    // Create child to run first command
    if (fork() == 0){
        // In child, redirect output to write end of pipe
        dup2(RW[1], STDOUT_FILENO);
        // Close the read end of the pipe on the child side
        close(RW[0]);
        // In child, execute the command
        execvp(cmd1[0], cmd1);
    }

    // Create another child to run second command
    if (fork() == 0){
        // In child, redirect input to the read end of the pipe
        dup2(RW[0], STDIN_FILENO);
        // Close the write end of the pipe on the child side.
        close(RW[1]);
        // Execute the second command.
        execvp(cmd2[0], cmd2);
    }
    // Reset the input and output file descriptors of the parent.

}
