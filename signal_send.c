#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    printf("프로그램 시작! 자신에게 SIGUSR1 시그널을 보냅니다.\n");
    sleep(2); // 2초 대기

    // 자신에게 SIGUSR1 시그널 보내기
    kill(getpid(), SIGUSR1);

    // 무한 루프
    while (1) {
        // 무한 루프에서 프로그램이 계속 실행됨
    }

    return 0;
}
