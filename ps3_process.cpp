#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    else if (pid == 0) {

        cout << "Child Process ID: " << getpid() << endl;
        // Replaces child process with ls -l command.
        execl("/bin/ls", "ls", "-l", NULL);

        perror("exec failed");
        exit(1);
    }

    else {
        // PARENT PROCESS
        cout << "Parent Process ID: " << getpid() << endl;
        // Parent waits until child finishes execution.
        wait(NULL);
        cout << "Child process completed\n";
    }

    return 0;
}