#include "logger.h"
#include <unistd.h>
#include <pthread.h>

// 멀티스레드 테스트를 위한 함수
void* thread_logger(void* arg) {
    int thread_id = *((int*)arg);
    
    for (int i = 0; i < 5; i++) {
        log_info("Thread %d: Message %d", thread_id, i);
        usleep(100000); // 0.1초 대기
    }
    
    return NULL;
}

int main() {
    printf("=== Logger Test Program ===\n\n");
    
    // 1. 기본 로거 초기화
    printf("1. Initializing logger with file output...\n");
    logger_init("test.log", LOG_DEBUG);
    
    // 2. 각 레벨별 로그 출력 테스트
    printf("\n2. Testing different log levels:\n");
    log_debug("This is a debug message");
    log_info("This is an info message");
    log_warning("This is a warning message");
    log_error("This is an error message");
    log_fatal("This is a fatal message");
    
    // 3. 로그 레벨 변경 테스트
    printf("\n3. Changing log level to WARNING...\n");
    logger_set_level(LOG_WARNING);
    log_debug("This debug message should NOT appear");
    log_info("This info message should NOT appear");
    log_warning("This warning message SHOULD appear");
    log_error("This error message SHOULD appear");
    
    // 4. 콘솔 출력 비활성화 테스트
    printf("\n4. Disabling console output...\n");
    logger_enable_console(0);
    log_info("This message should only appear in the file, not console");
    
    // 콘솔 출력 다시 활성화
    logger_enable_console(1);
    printf("Console output re-enabled\n");
    
    // 5. 포맷 문자열 테스트
    printf("\n5. Testing formatted output:\n");
    logger_set_level(LOG_DEBUG);
    int value = 42;
    float pi = 3.14159;
    const char* str = "Hello, Logger!";
    log_info("Integer: %d, Float: %.2f, String: %s", value, pi, str);
    
    // 6. 멀티스레드 테스트
    printf("\n6. Testing thread safety:\n");
    pthread_t threads[3];
    int thread_ids[3] = {1, 2, 3};
    
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, thread_logger, &thread_ids[i]);
    }
    
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // 7. 파일 출력 비활성화 테스트
    printf("\n7. Disabling file output...\n");
    logger_enable_file(0);
    log_info("This message should only appear in console, not file");
    
    // 8. 로거 종료
    printf("\n8. Closing logger...\n");
    logger_close();
    
    printf("\n=== Test completed! ===\n");
    printf("Check 'test.log' for file output.\n");
    
    return 0;
}