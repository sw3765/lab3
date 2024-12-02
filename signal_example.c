#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

// SIGINT 시그널 처리기
void handle_sigint(int sig) {
    printf("SIGINT 시그널을 받았습니다. 프로그램을 종료합니다.\n");
    exit(0); // 프로그램 종료
}

int main() {
    // SIGINT 시그널이 발생하면 handle_sigint 함수 실행
    signal(SIGINT, handle_sigint);

    printf("Ctrl+C를 눌러 SIGINT 시그널을 보낼 수 있습니다.\n");

    // 시그널을 기다리기 위해 무한 루프
    while (1) {
        // 무한 루프에서 프로그램이 계속 실행됨
    }

    return 0;
}
