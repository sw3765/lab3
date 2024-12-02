#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>  // wait() 함수 사용

#define SHM_SIZE 1024

// 세마포어 관련 구조체
struct sembuf sem_op;

int main() {
    // 공유 메모리 생성
    printf("Creating shared memory...\n");
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, SHM_SIZE, 0666|IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        return 1;
    }
    char *data = (char *) shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) {
        perror("shmat failed");
        return 1;
    }

    // 세마포어 생성
    printf("Creating semaphore...\n");
    int semid = semget(key, 1, 0666|IPC_CREAT);
    if (semid == -1) {
        perror("semget failed");
        return 1;
    }

    // 세마포어 초기화
    semctl(semid, 0, SETVAL, 1);

    // 공유 메모리에 데이터 쓰기 (파일 읽기)
    printf("Reading data from source file...\n");
    FILE *source_file = fopen("source.txt", "r");
    if (source_file == NULL) {
        perror("Failed to open source file");
        return 1;
    }
    fread(data, 1, SHM_SIZE, source_file);
    fclose(source_file);

    // 세마포어 값 감소
    printf("Decreasing semaphore...\n");
    sem_op.sem_num = 0;
    sem_op.sem_op = -1;
    sem_op.sem_flg = 0;
    semop(semid, &sem_op, 1);

    printf("Parent finished writing to shared memory\n");

    // 자식 프로세스 생성
    pid_t pid = fork();
    if (pid == -1) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {  // 자식 프로세스
        // 자식 프로세스에서 데이터 읽기
        printf("Child process: attaching shared memory...\n");
        char *child_data = (char *) shmat(shmid, (void *)0, 0);
        if (child_data == (char *)(-1)) {
            perror("shmat failed");
            return 1;
        }

        // 세마포어 연결
        printf("Child process: attaching semaphore...\n");
        int child_semid = semget(key, 1, 0666);
        if (child_semid == -1) {
            perror("semget failed");
            return 1;
        }

        // 세마포어 값 증가
        printf("Child process: increasing semaphore...\n");
        sem_op.sem_num = 0;
        sem_op.sem_op = 1;
        sem_op.sem_flg = 0;
        semop(child_semid, &sem_op, 1);

        // 데이터 출력
        printf("Child received data: %s\n", child_data);

        shmdt(child_data);
        return 0;
    } else {  // 부모 프로세스
        // 자식 프로세스가 종료될 때까지 기다림
        wait(NULL);
        shmdt(data);
        shmctl(shmid, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID);
    }

    return 0;
}
