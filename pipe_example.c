#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int pipe_fd[2];  // 파이프 파일 디스크립터 (읽기용, 쓰기용)
    pid_t pid;
    char message[] = "Hello from parent!";
    char buffer[100];

    // 파이프 생성
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();  // 자식 프로세스 생성

    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // 자식 프로세스: 파이프에서 데이터 읽기
        close(pipe_fd[1]);  // 쓰기 끝을 닫음
        read(pipe_fd[0], buffer, sizeof(buffer));  // 부모에서 보낸 데이터 읽기
        printf("Child received: %s\n", buffer);
        close(pipe_fd[0]);  // 읽기 끝을 닫음
    } else {
        // 부모 프로세스: 파이프에 데이터 쓰기
        close(pipe_fd[0]);  // 읽기 끝을 닫음
        write(pipe_fd[1], message, sizeof(message));  // 자식에게 데이터 보내기
        close(pipe_fd[1]);  // 쓰기 끝을 닫음
    }

    return 0;
}
