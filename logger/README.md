# Logger Library

C언어로 구현한 간단하고 효율적인 로깅 라이브러리입니다.

## 기능

- 5가지 로그 레벨 지원 (DEBUG, INFO, WARNING, ERROR, FATAL)
- 콘솔과 파일 동시 출력
- 컬러 출력 지원 (콘솔)
- Thread-safe (pthread mutex 사용)
- 포맷 문자열 지원 (printf 스타일)
- 런타임 로그 레벨 변경 가능

## 사용법

### 컴파일
```bash
make
```

### 테스트 실행
```bash
make run
```

### 초기화
```c
#include "logger.h"

// 로거 초기화 (파일명, 로그 레벨)
logger_init("app.log", LOG_INFO);
```

### 로그 출력
```c
log_debug("Debug message: %d", value);
log_info("Info message: %s", str);
log_warning("Warning message");
log_error("Error occurred: %s", error_msg);
log_fatal("Fatal error!");
```

### 설정 변경
```c
// 로그 레벨 변경
logger_set_level(LOG_WARNING);

// 콘솔 출력 비활성화
logger_enable_console(0);

// 파일 출력 비활성화
logger_enable_file(0);
```

### 종료
```c
logger_close();
```

## 파일 구조

- `logger.h` - 헤더 파일
- `logger.c` - 구현 파일
- `test_logger.c` - 테스트 프로그램
- `Makefile` - 빌드 스크립트