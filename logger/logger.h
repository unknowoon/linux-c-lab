#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <time.h>
#include <stdarg.h>

// 로그 레벨 정의
typedef enum {
    LOG_DEBUG = 0,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_FATAL
} LogLevel;

// 로그 설정 구조체
typedef struct {
    FILE *file;
    LogLevel level;
    int console_output;
    int file_output;
    char filename[256];
} Logger;

// 전역 로거 인스턴스
extern Logger g_logger;

// 함수 프로토타입
void logger_init(const char *filename, LogLevel level);
void logger_set_level(LogLevel level);
void logger_enable_console(int enable);
void logger_enable_file(int enable);
void logger_close(void);

// 내부 로그 작성 함수 (직접 호출하지 마세요)
void log_write(LogLevel level, const char *file, const char *function, int line, const char *format, ...);

// 매크로를 통한 로그 출력 (파일명과 라인 번호 자동 전달)
#define log_debug(...)    log_write(LOG_DEBUG, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define log_info(...)     log_write(LOG_INFO, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define log_warning(...)  log_write(LOG_WARNING, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define log_error(...)    log_write(LOG_ERROR, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define log_fatal(...)    log_write(LOG_FATAL, __FILE__, __func__, __LINE__, __VA_ARGS__)

#endif // LOGGER_H