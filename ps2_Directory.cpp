#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

using namespace std;

int main() {

    // CREATE DIRECTORY
    if (mkdir("mydir", 0777) == 0)
        cout << "Directory created\n";
    else
        perror("mkdir");

    // OPEN & LIST DIRECTORY
    DIR *d;
    struct dirent *dir;

    d = opendir(".");
    if (d) {
        cout << "\nContents of current directory:\n";
        while ((dir = readdir(d)) != NULL) {
            cout << dir->d_name << endl;
        }
        closedir(d);
    }

    // CHANGE DIRECTORY
    if (chdir("mydir") == 0)
        cout << "\nChanged to mydir\n";
    else
        perror("chdir");

    // GO BACK
    if (chdir("..") == 0)
        cout << "Returned to parent directory\n";

    // DELETE DIRECTORY
    if (rmdir("mydir") == 0)
        cout << "Directory removed\n";
    else
        perror("rmdir");

    return 0;
}