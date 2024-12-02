#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT 512

// 메시지 구조체
struct message {
    long msg_type;  // 메시지 타입
    char msg_text[MAX_TEXT];  // 메시지 내용
};

int main() {
    key_t key = ftok("chat_server.c", 65);  // 고유 키 생성
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    // 메시지 큐 생성
    int msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    // 자식 프로세스 생성
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // 자식 프로세스 1 (사용자 1) - 메시지 읽기 및 입력
        struct message msg;
        msg.msg_type = 1;

        while (1) {
            printf("User 1: ");
            fgets(msg.msg_text, MAX_TEXT, stdin);
            msg.msg_text[strcspn(msg.msg_text, "\n")] = 0;  // 줄바꿈 제거

            // 메시지를 메시지 큐에 전송
            msgsnd(msgid, &msg, sizeof(msg), 0);

            if (strcmp(msg.msg_text, "exit") == 0) {
                break;
            }
        }
        exit(0);
    } else {
        // 자식 프로세스 2 (사용자 2) - 메시지 읽기
        struct message msg;
        msg.msg_type = 1;

        while (1) {
            // 메시지 큐에서 메시지 읽기
            msgrcv(msgid, &msg, sizeof(msg), msg.msg_type, 0);
            printf("User 2: %s\n", msg.msg_text);

            if (strcmp(msg.msg_text, "exit") == 0) {
                break;
            }

            // 사용자 2의 응답
            printf("User 2: ");
            fgets(msg.msg_text, MAX_TEXT, stdin);
            msg.msg_text[strcspn(msg.msg_text, "\n")] = 0;  // 줄바꿈 제거

            // 메시지를 메시지 큐에 전송
            msgsnd(msgid, &msg, sizeof(msg), 0);

            if (strcmp(msg.msg_text, "exit") == 0) {
                break;
            }
        }

        // 메시지 큐 삭제
        msgctl(msgid, IPC_RMID, NULL);
        exit(0);
    }

    return 0;
}
