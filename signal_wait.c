#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_sigusr1(int sig) {
    printf("SIGUSR1 시그널을 받았습니다. 프로그램이 종료됩니다.\n");
    exit(0); // 프로그램 종료
}

int main() {
    // SIGUSR1 시그널이 발생하면 handle_sigusr1 함수 실행
    signal(SIGUSR1, handle_sigusr1);

    printf("프로그램이 시그널을 기다리고 있습니다...\n");

    // 시그널을 기다리기 위해 pause() 호출
    pause();

    return 0;
}
