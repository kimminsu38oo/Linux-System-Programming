#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 4096

void tail(int fd);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(-1);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(-2);
    }
    tail(fd);

    close(fd);
    return 0;
}

void tail(int fd) {
    off_t file_size = lseek(fd, 0, SEEK_END);
    if (file_size == -1) {
        perror("lseek");
        exit(-3);
    }

    char buffer[BUFFER_SIZE];
    off_t cur_pos = file_size;

    int nline = 0;


    while (cur_pos > 0 && nline <= 10) {
        ssize_t bytes_to_read = (cur_pos > BUFFER_SIZE) ? BUFFER_SIZE : cur_pos;
        cur_pos -= bytes_to_read;
        if (lseek(fd, cur_pos, SEEK_SET) != cur_pos) {
            perror("lseek");
            exit(-4);
        }

        ssize_t nread = read(fd, buffer, bytes_to_read);

        if (nread == -1) {
            perror("read");
            exit(-5);
        }

        for (ssize_t i = nread - 1; i >= 0; --i) {
            if (buffer[i]=='\n') {
                ++nline;
                if (nline > 10) {
                    cur_pos += i + 1;
                    break;
                }
            }
        }
    }
    if (lseek(fd, cur_pos, SEEK_SET) != cur_pos) {
        perror("lseek");
        exit(-6);
    }

    ssize_t nread;
    while ((nread = read(fd, buffer, BUFFER_SIZE)) > 0) {
        if (write(1, buffer, nread) < nread) {
            perror("write");
            exit(-7);
        }
    }

    if (nread == -1) {
        perror("read");
        exit(-8);
    }
}

