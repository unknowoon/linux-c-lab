#include "logger.h"
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

// 전역 로거 인스턴스
Logger g_logger = {
    .file = NULL,
    .level = LOG_INFO,
    .console_output = 1,
    .file_output = 1,
    .filename = ""
};

// 로그 레벨 문자열
static const char *level_strings[] = {
    "DEBUG",
    "INFO",
    "WARNING",
    "ERROR",
    "FATAL"
};

// 로그 레벨에 따른 색상 코드 (ANSI escape codes)
static const char *level_colors[] = {
    "\033[36m",  // DEBUG - Cyan
    "\033[32m",  // INFO - Green
    "\033[33m",  // WARNING - Yellow
    "\033[31m",  // ERROR - Red
    "\033[35m"   // FATAL - Magenta
};

// 색상 리셋 코드
static const char *color_reset = "\033[0m";

// 뮤텍스 for thread safety
static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

void logger_init(const char *filename, LogLevel level) {
    pthread_mutex_lock(&log_mutex);
    
    // 기존 파일이 열려있다면 닫기
    if (g_logger.file != NULL) {
        fclose(g_logger.file);
        g_logger.file = NULL;
    }
    
    // 새 파일 열기
    if (filename != NULL && strlen(filename) > 0) {
        strncpy(g_logger.filename, filename, sizeof(g_logger.filename) - 1);
        g_logger.filename[sizeof(g_logger.filename) - 1] = '\0';
        
        g_logger.file = fopen(g_logger.filename, "a");
        if (g_logger.file == NULL) {
            fprintf(stderr, "Failed to open log file: %s\n", g_logger.filename);
            g_logger.file_output = 0;
        }
    }
    
    g_logger.level = level;
    
    pthread_mutex_unlock(&log_mutex);
}

void logger_set_level(LogLevel level) {
    pthread_mutex_lock(&log_mutex);
    g_logger.level = level;
    pthread_mutex_unlock(&log_mutex);
}

void logger_enable_console(int enable) {
    pthread_mutex_lock(&log_mutex);
    g_logger.console_output = enable;
    pthread_mutex_unlock(&log_mutex);
}

void logger_enable_file(int enable) {
    pthread_mutex_lock(&log_mutex);
    g_logger.file_output = enable;
    pthread_mutex_unlock(&log_mutex);
}

void logger_close(void) {
    pthread_mutex_lock(&log_mutex);
    
    if (g_logger.file != NULL) {
        fclose(g_logger.file);
        g_logger.file = NULL;
    }
    
    pthread_mutex_unlock(&log_mutex);
}

void log_write_internal(LogLevel level, const char *file, int line, const char *format, va_list args) {
    if (level < g_logger.level) {
        return;
    }
    
    pthread_mutex_lock(&log_mutex);
    
    // 현재 시간 구하기
    time_t now;
    time(&now);
    struct tm *local_time = localtime(&now);
    
    char time_str[32];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", local_time);
    
    // 파일명에서 경로 제거 (마지막 '/' 이후만 표시)
    const char *filename = strrchr(file, '/');
    if (filename) {
        filename++; // '/' 다음 문자부터
    } else {
        filename = file;
    }
    
    // 콘솔 출력
    if (g_logger.console_output) {
        fprintf(stderr, "%s[%s] [%s] [%s:%d]%s ", 
                level_colors[level], time_str, level_strings[level], 
                filename, line, color_reset);
        vfprintf(stderr, format, args);
        fprintf(stderr, "\n");
        fflush(stderr);
    }
    
    // 파일 출력
    if (g_logger.file_output && g_logger.file != NULL) {
        fprintf(g_logger.file, "[%s] [%s] [%s:%d] ", 
                time_str, level_strings[level], filename, line);
        vfprintf(g_logger.file, format, args);
        fprintf(g_logger.file, "\n");
        fflush(g_logger.file);
    }
    
    pthread_mutex_unlock(&log_mutex);
}

void log_debug_internal(const char *file, int line, const char *format, ...) {
    va_list args;
    va_start(args, format);
    log_write_internal(LOG_DEBUG, file, line, format, args);
    va_end(args);
}

void log_info_internal(const char *file, int line, const char *format, ...) {
    va_list args;
    va_start(args, format);
    log_write_internal(LOG_INFO, file, line, format, args);
    va_end(args);
}

void log_warning_internal(const char *file, int line, const char *format, ...) {
    va_list args;
    va_start(args, format);
    log_write_internal(LOG_WARNING, file, line, format, args);
    va_end(args);
}

void log_error_internal(const char *file, int line, const char *format, ...) {
    va_list args;
    va_start(args, format);
    log_write_internal(LOG_ERROR, file, line, format, args);
    va_end(args);
}

void log_fatal_internal(const char *file, int line, const char *format, ...) {
    va_list args;
    va_start(args, format);
    log_write_internal(LOG_FATAL, file, line, format, args);
    va_end(args);
}