#include <iostream>
#include <fcntl.h>   // open()
#include <unistd.h>  // read(), write(), close(), unlink()
#include <cstring>   // strlen()
using namespace std;

int main() {
    int fd;
    char data[] = "Hello, this is file handling using system calls.\n";
    char buffer[100];

    // 1. Create & Write File
    fd = open("file1.txt", O_CREAT | O_WRONLY, 0644);
    write(fd, data, strlen(data));
    close(fd);

    cout << "File created and written successfully.\n";

    // 2. Read File
    fd = open("file1.txt", O_RDONLY);
    int n = read(fd, buffer, sizeof(buffer));
    buffer[n] = '\0';
    cout << "File Content: " << buffer;
    close(fd);

    // 3. Copy File
    int fd2 = open("file2.txt", O_CREAT | O_WRONLY, 0644);
    write(fd2, buffer, strlen(buffer));
    close(fd2);

    cout << "File copied to file2.txt\n";

    // 4. Delete File
    unlink("file1.txt");
    cout << "file1.txt deleted\n";

    return 0;
}