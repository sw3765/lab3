#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>  // waitpid()를 사용하기 위한 헤더

int my_system(const char *command) {
    pid_t pid = fork();  // 자식 프로세스 생성

    if (pid == -1) {
        // fork 실패
        perror("fork");
        return -1;
    }

    if (pid == 0) {
        // 자식 프로세스에서 명령 실행
        char *args[] = {"/bin/sh", "-c", (char *)command, NULL}; // 명령어를 실행할 쉘 설정
        execvp(args[0], args);  // 쉘 명령 실행
        // execvp() 실패 시
        perror("execvp");
        return -1;
    } else {
        // 부모 프로세스: 자식이 종료될 때까지 대기
        int status;
        waitpid(pid, &status, 0);
        return status;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        return 1;
    }

    // 명령어를 문자열로 조합
    char command[256] = "";
    for (int i = 1; i < argc; i++) {
        strcat(command, argv[i]);
        strcat(command, " ");
    }

    // my_system을 호출하여 명령 실행
    int status = my_system(command);
    if (status == -1) {
        fprintf(stderr, "Command execution failed\n");
        return 1;
    }

    return 0;
}
