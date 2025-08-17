#include "../inc/logger.h"

int main() {
    printf("=== Logger Simple Example ===\n");
    
    // Logger 초기화
    logger_init("example.log", LOG_DEBUG);
    
    // 간단한 로그 메시지들
    log_info("Application started");
    log_warning("This is a warning message");
    log_error("This is an error message");
    
    // Logger 종료
    logger_close();
    
    printf("Check 'example.log' for output.\n");
    return 0;
}