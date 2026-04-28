#include <iostream>
#include <sys/stat.h>  // mkdir()
#include <unistd.h>    // chdir(), rmdir()
using namespace std;

int main() {

    // 1. Create Directory
    mkdir("testDir", 0777);
    cout << "Directory created\n";

    // 2. Change Directory
    chdir("testDir");
    cout << "Changed into testDir\n";

    // 3. Go back
    chdir("..");

    // 4. Remove Directory
    rmdir("testDir");
    cout << "Directory deleted\n";

    return 0;
}