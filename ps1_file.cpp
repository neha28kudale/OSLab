#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

using namespace std;

int main() {
    int fd;
    char buffer[100];

    // CREATE + WRITE
    fd = open("file.txt", O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    write(fd, "Hello, OS Assignment\n", 22);
    close(fd);

    cout << "File created & written\n";

    // READ
    fd = open("file.txt", O_RDONLY);
    int n = read(fd, buffer, sizeof(buffer));
    buffer[n] = '\0';
    cout << "File Content: " << buffer << endl;
    close(fd);

    // COPY
    int fd2 = open("copy.txt", O_CREAT | O_WRONLY, 0644);
    fd = open("file.txt", O_RDONLY);

    while ((n = read(fd, buffer, sizeof(buffer))) > 0) {
        write(fd2, buffer, n);
    }

    close(fd);
    close(fd2);

    cout << "File copied\n";

    // DELETE
    unlink("file.txt");
    cout << "Original file deleted\n";

    return 0;
}