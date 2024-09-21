#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
static short octarray[9] = {0400, 0200, 0100, //user : r, w, x
                        0040, 0020, 0010, //group : r, w, x
                        0004, 0002, 0001}; //others : r, w, x

void print_file_info(const char *filepath) {
        struct stat file_stat;
        // get file stat
        if (stat(filepath, &file_stat) == -1) {
                perror("stat");
                exit(-2);
        }

        // check the type of the file
        char file_type;

        if (S_ISREG(file_stat.st_mode)) file_type = 'f'; //S_ISREG는 파일모드가 regular file인지 체크하는 매크로
        else if (S_ISDIR(file_stat.st_mode)) file_type = 'd';//S_ISDIR는 파일모드가 directory인지 체크하는 매크로
        else file_type = '?';

        const char *perms_list = "rwxrwxrwx";
        char perms_data[11]; //접근 권한을 string으로 표현
        perms_data[0] = (file_type == 'd') ? 'd':'-'; //파일타입이 regular file인지 directory인지 설정 (‘?’ 제외)

        // check the permissions of the file
        for (int i = 0; i < 9; i++) {
                perms_data[i+1] = (file_stat.st_mode & octarray[i]) ? perms_list[i] : '-';
        }
        perms_data[10] = '\0';

        // get UID & GID
        struct passwd *pwd = getpwuid(file_stat.st_uid);//uid로부터 사용자 정보를 획득하는 함수
        struct group *grp = getgrgid(file_stat.st_gid);//gid로부터 그룹 정보를 획득하는 함수

        // convert time information to make it easier to read.
        char access_time[256];
        char modify_time[256];
        char change_time[256];
        strftime(access_time, sizeof(access_time), "%Y-%m-%d %H:%M:%S", localtime(&file_stat.st_atime));
        strftime(modify_time, sizeof(modify_time), "%Y-%m-%d %H:%M:%S", localtime(&file_stat.st_mtime));
        strftime(change_time, sizeof(change_time), "%Y-%m-%d %H:%M:%S", localtime(&file_stat.st_ctime));

        // print information
        printf(" File: %s\n", filepath);
        printf(" Size: %ld Blocks: %ld IO Block: %ld %s\n",
        file_stat.st_size, file_stat.st_blocks, file_stat.st_blksize,
        (file_type == 'd') ? "directory" : "regular file");
        printf("Device: %lxh/%ldd Inode: %ld Links: %ld\n",
        (unsigned long)file_stat.st_dev, (unsigned long)file_stat.st_dev,
        (long)file_stat.st_ino, (long)file_stat.st_nlink);

        printf("Access: (%04o/%s) Uid: (%d/%s) Gid: (%d/%s)\n",
        file_stat.st_mode & 07777, perms_data, file_stat.st_uid,
        (pwd != NULL) ? pwd->pw_name : "unknown",
        file_stat.st_gid, (grp != NULL) ? grp->gr_name : "unknown");

        printf("Access: %s\n", access_time);
        printf("Modify: %s\n", modify_time);
        printf("Change: %s\n", change_time);
        printf(" Birth: -\n");
}
int main(int argc, char *argv[]) {
        if (argc != 2) {
                fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
                return -1;
        }
        print_file_info(argv[1]);
        return 0;
}

