#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>  // mkdir
#include <dirent.h>    // opendir, readdir, closedir
#include <unistd.h>    // rmdir, remove

int main() {
    // 1. 디렉토리 생성
    const char *dir_name = "example_dir";
    if (mkdir(dir_name, 0755) == 0) {
        printf("Directory '%s' created successfully.\n", dir_name);
    } else {
        perror("mkdir");
    }

    // 2. 파일 생성 및 쓰기
    const char *file_name = "example_dir/example_file.txt";
    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }
    fprintf(file, "Hello, Ubuntu!\n");
    fclose(file);
    printf("File '%s' created and written successfully.\n", file_name);

    // 3. 파일 읽기
    file = fopen(file_name, "r");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("Read from file: %s", buffer);
    }
    fclose(file);

    // 4. 디렉토리 내용 읽기
    DIR *dir = opendir(dir_name);
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }
    struct dirent *entry;
    printf("Contents of directory '%s':\n", dir_name);
    while ((entry = readdir(dir)) != NULL) {
        printf("  %s\n", entry->d_name);
    }
    closedir(dir);

    // 5. 파일 삭제
    if (remove(file_name) == 0) {
        printf("File '%s' deleted successfully.\n", file_name);
    } else {
        perror("remove");
    }

    // 6. 디렉토리 삭제
    if (rmdir(dir_name) == 0) {
        printf("Directory '%s' deleted successfully.\n", dir_name);
    } else {
        perror("rmdir");
    }

    return 0;
}
