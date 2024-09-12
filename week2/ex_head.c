#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define BUFFER_SIZE 4096
void head(int fd);
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
        head(fd);
        close(fd);
        return 0;
}
void head(int fd) {
        char buffer[BUFFER_SIZE];
        int nline = 0;
        ssize_t nread;
        while ((nread = read(fd, buffer, BUFFER_SIZE)) > 0) {
                for (ssize_t i = 0; i < nread; ++i) {
                        if (buffer[i]=='\n') { //hint: 행의 수를 셀 수 있는 기준이 되는 character
                                ++nline;
                        }
                        if (nline == 10) {
                                if (write(1, buffer, i+1) < i+1) { //hint: write을 수행하고 실패시 scope 진입
                                        perror("write");
                                        exit(-3);
                                }
                                return;
                        }
                }
                if (write(1, buffer, nread) < nread) {// Text is less than 10 lines.
                        perror("write");
                        exit(-4);
                }
        }
        if (nread == -1) {
                perror("read");
                exit(-5);
        }
}

