#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFSIZE 4096
int main(int argc, char *argv[]) {
        char buffer[BUFSIZE];
        ssize_t nread;
        int fd;
        if (argc < 2) {
                write(2, "Usage: ./ex_cat <filename>\n", 28);
                return 1;
        }
        fd = open(argv[1], O_RDONLY);
        if (fd == -1) {
                perror("Error opening file");
                return 1;
        }
        while ((nread = read(fd, buffer, sizeof(buffer))) > 0) {
                write(1, buffer, nread);
        }
        close(fd);
        return 0;
}

