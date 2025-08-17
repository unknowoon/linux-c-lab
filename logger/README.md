# Logger Library

C언어로 구현한 간단하고 효율적인 로깅 라이브러리입니다.

## 기능

- 5가지 로그 레벨 지원 (DEBUG, INFO, WARNING, ERROR, FATAL)
- 콘솔과 파일 동시 출력
- 컬러 출력 지원 (콘솔)
- Thread-safe (pthread mutex 사용)
- 포맷 문자열 지원 (printf 스타일)
- 런타임 로그 레벨 변경 가능

## 프로젝트 구조

```
logger/
├── inc/                    # 헤더 파일들
│   └── logger.h           # 라이브러리 헤더
├── libsrc/                # 라이브러리 소스
│   └── logger.c           # 라이브러리 구현
├── src/                   # 예제/테스트 소스
│   ├── main.c            # 간단한 사용 예제
│   └── test_logger.c     # 종합 테스트 프로그램
├── build/                 # 빌드 오브젝트들 (자동 생성)
├── liblogger.a           # 정적 라이브러리 (빌드 후 생성)
├── Makefile              # 빌드 스크립트
└── README.md             # 이 파일
```

## 빌드 시스템

### 사용 가능한 명령어

```bash
# 전체 빌드 (라이브러리 + 실행 파일들)
make

# 개별 빌드
make liblogger.a          # 라이브러리만 빌드
make test_logger          # 테스트 프로그램만 빌드
make main                 # 메인 예제만 빌드

# 실행
make test                 # 테스트 프로그램 실행
make run                  # 메인 예제 실행

# 정리
make clean                # 빌드 결과물 삭제

# 라이브러리 확인
make install              # 라이브러리 상태 확인
```

## 사용법

### 헤더 인클루드
```c
#include "inc/logger.h"    // 직접 사용 시
// 또는
#include "logger.h"        // 라이브러리 설치 후
```

### 초기화
```c
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

// 콘솔 출력 활성화/비활성화
logger_enable_console(1);  // 활성화
logger_enable_console(0);  // 비활성화

// 파일 출력 활성화/비활성화
logger_enable_file(1);     // 활성화
logger_enable_file(0);     // 비활성화
```

### 종료
```c
logger_close();
```

## 라이브러리 사용법

### 정적 링크
```bash
# 컴파일 시 라이브러리 링크
gcc -Iinc your_program.c -L. -llogger -pthread -o your_program
```

### 외부 프로젝트에서 사용
```bash
# 헤더 복사
cp inc/logger.h /your/project/includes/

# 라이브러리 복사
cp liblogger.a /your/project/libs/

# 컴파일
gcc your_code.c -I/your/project/includes -L/your/project/libs -llogger -pthread
```

## 로그 레벨

| 레벨 | 설명 | 색상 |
|------|------|------|
| DEBUG | 디버깅 정보 | 청록색 |
| INFO | 일반 정보 | 녹색 |
| WARNING | 경고 메시지 | 노란색 |
| ERROR | 오류 메시지 | 빨간색 |
| FATAL | 치명적 오류 | 자홍색 |

## 멀티스레드 지원

라이브러리는 pthread mutex를 사용하여 thread-safe합니다:

```c
#include <pthread.h>
#include "inc/logger.h"

void* worker_thread(void* arg) {
    int id = *(int*)arg;
    log_info("Worker thread %d started", id);
    // ... 작업 수행
    log_info("Worker thread %d finished", id);
    return NULL;
}
```

## 예제 출력

### 콘솔 출력 (컬러)
```
[2025-08-17 22:24:24] [INFO] [main] [main.c:10] Application started
[2025-08-17 22:24:24] [WARNING] [main] [main.c:11] This is a warning message
[2025-08-17 22:24:24] [ERROR] [main] [main.c:12] This is an error message
```

### 파일 출력 (컬러 없음)
```
[2025-08-17 22:24:24] [INFO] [main] [main.c:10] Application started
[2025-08-17 22:24:24] [WARNING] [main] [main.c:11] This is a warning message
[2025-08-17 22:24:24] [ERROR] [main] [main.c:12] This is an error message
```

## 빌드 요구사항

- GCC 또는 Clang 컴파일러
- POSIX 호환 시스템 (pthread 지원)
- Make 빌드 도구