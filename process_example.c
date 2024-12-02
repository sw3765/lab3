#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();  // 자식 프로세스 생성

    if (pid == -1) {
        // fork 실패
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // 자식 프로세스 코드
        printf("Child process: PID = %d\n", getpid());

        // exec()로 다른 프로그램 실행 (예: ls 명령어 실행)
        execlp("/bin/ls", "ls", "-l", NULL);
        
        // execlp()가 성공적으로 실행되면 아래 코드는 실행되지 않습니다.
        perror("execlp");  // execlp 실패시
        exit(1);
    } else {
        // 부모 프로세스 코드
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);

        // 자식 프로세스가 종료될 때까지 기다림
        wait(NULL);
        printf("Child process has terminated.\n");
    }

    return 0;
}
