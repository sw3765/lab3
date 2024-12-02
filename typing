#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LENGTH 1000

int main() {
    char sentence[MAX_LENGTH] = "The quick brown fox jumps over the lazy dog.";
    char input[MAX_LENGTH];
    int errors = 0;
    int total_chars = 0;

    // 시작 시간 기록
    clock_t start_time = clock();

    printf("타자 연습 프로그램\n");
    printf("다음 문장을 타이핑하세요: \n");
    printf("\"%s\"\n", sentence);
    printf("입력 시작: ");
    
    // 사용자 입력 받기
    fgets(input, MAX_LENGTH, stdin);

    // 입력한 문장에서 잘못 타이핑한 횟수 계산
    for (int i = 0; i < strlen(sentence); i++) {
        if (input[i] != sentence[i]) {
            errors++;
        }
        if (input[i] != '\0') {
            total_chars++;  // 실제 타이핑한 문자 수 계산
        }
    }

    // 끝난 시간 기록
    clock_t end_time = clock();

    // 경과 시간 계산
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    
    // 평균 분당 타자수 계산
    double typing_speed = (total_chars / time_taken) * 60;

    // 결과 출력
    printf("\n타자 연습 결과:\n");
    printf("잘못 타이핑한 횟수: %d\n", errors);
    printf("평균 분당 타자수: %.2f\n", typing_speed);

    return 0;
}
