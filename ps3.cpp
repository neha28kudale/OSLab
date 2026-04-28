#include <iostream>
#include <unistd.h>   // fork(), exec()
#include <sys/wait.h> // wait()
using namespace std;

int main() {

    pid_t pid = fork();

    if (pid < 0) {
        cout << "Fork failed\n";
    }
    else if (pid == 0) {
        // Child Process
        cout << "Child Process: PID = " << getpid() << endl;

        execl("/bin/ls", "ls", NULL);  // run ls command

        cout << "This line will not execute if exec works\n";
    }
    else {
        // Parent Process
        cout << "Parent Process: PID = " << getpid() << endl;

        wait(NULL);  // wait for child
        cout << "Child process completed\n";
    }

    return 0;
}