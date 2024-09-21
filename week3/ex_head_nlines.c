#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define BUFFER_SIZE 4096
void head(int fd, int n);
int main(int argc, char *argv[]) {
    int opt;
    int n = 10; // 기본값: 10줄
    // 옵션 처리
    while ((opt = getopt(argc, argv, "n:")) != -1) {
        switch (opt) {
            case 'n':
            n = atoi(optarg); //hint : atoi라는 함수를 사용
            break;
        default:
            fprintf(stderr, "Usage: %s [-n number_of_lines] <filename>\n", argv[0]);
            exit(-1);
        }
    }
    if (optind >= argc) {
        fprintf(stderr, "Usage: %s [-n number_of_lines] <filename>\n", argv[0]);
        exit(-2);
    }
    int fd = open(argv[optind], O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(-3);
    }
        head(fd, n);
        close(fd);
        return 0;
}
void head(int fd, int n) {
    char buffer[BUFFER_SIZE];
    int nline = 0;
    ssize_t nread;
    while ((nread = read(fd, buffer, BUFFER_SIZE)) > 0) {
        for (ssize_t i = 0; i < nread; ++i) {
            if (buffer[i] == '\n') {
                ++nline;
            }
            if (nline == n) {
                if (write(STDOUT_FILENO, buffer, i + 1) == -1) {
                    perror("write");
                    exit(-4);
                }
                return;
            }
        }
    if (write(STDOUT_FILENO, buffer, nread) == -1) {
        perror("write");
        exit(-5);
    }
    }
    if (nread == -1) {
        perror("read");
        exit(-6);
    }
}

