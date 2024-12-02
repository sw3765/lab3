#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>  // opendir, readdir, closedir
#include <sys/types.h> // DIR, struct dirent
#include <unistd.h>    // getcwd

void list_directory(const char *dir_name) {
    DIR *dir = opendir(dir_name);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    char path[1024];

    printf("%s:\n", dir_name);

    // 디렉토리 내 파일 및 디렉토리 출력
    while ((entry = readdir(dir)) != NULL) {
        // .과 ..을 제외하고 출력
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            // 디렉토리인 경우
            if (entry->d_type == DT_DIR) {
                printf("%s/\n", entry->d_name);
                // 재귀적으로 디렉토리 탐색
                snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);
                list_directory(path);
            } else {
                // 파일인 경우
                printf("%s\n", entry->d_name);
            }
        }
    }

    closedir(dir);
}

int main() {
    char cwd[1024];

    // 현재 작업 디렉토리 확인
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        list_directory(cwd);  // 현재 디렉토리부터 시작
    } else {
        perror("getcwd");
        return 1;
    }

    return 0;
}
