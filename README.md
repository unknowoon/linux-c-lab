# Linux C Lab

C언어를 이용한 시스템 프로그래밍 실습 프로젝트입니다.

## 프로젝트 구조

```
linux-c-lab/
├── logger/                 # 로깅 라이브러리
│   ├── inc/               # 헤더 파일
│   ├── libsrc/            # 라이브러리 소스
│   ├── src/               # 예제/테스트
│   ├── tests/             # Google Test 단위 테스트
│   └── Makefile
├── my_string/             # 문자열 함수 라이브러리
│   ├── my_*.c             # 각종 문자열 함수 구현
│   ├── my_string.h        # 헤더 파일
│   └── Makefile
├── linked_list/           # 범용 연결 리스트
│   ├── linked_list.c      # 연결 리스트 구현
│   ├── linked_list.h      # 헤더 파일
│   ├── main.c             # 예제 프로그램
│   └── Makefile
└── Makefile               # 루트 빌드 스크립트
```

## 빌드 시스템

전체 프로젝트는 **Makefile 기반**으로 구성되어 있습니다.

### 루트 디렉토리 명령어

```bash
# 전체 프로젝트 빌드
make all

# 개별 프로젝트 빌드
make logger        # 로거 라이브러리만
make my_string     # 문자열 라이브러리만
make linked_list   # 연결 리스트만

# 테스트 실행
make test          # 모든 프로젝트 테스트
make gtest         # 로거 Google Test 실행

# 정리 및 기타
make clean         # 모든 빌드 결과물 삭제
make install       # 라이브러리 상태 확인
make help          # 도움말 출력
```

### 개별 프로젝트 명령어

```bash
# 특정 프로젝트에서 작업
make -C logger <target>      # 로거 프로젝트
make -C my_string <target>   # 문자열 프로젝트  
make -C linked_list <target> # 연결 리스트 프로젝트
```

## 서브프로젝트 소개

### 1. Logger 라이브러리
- **목적**: Thread-safe 로깅 시스템
- **기능**: 
  - 5가지 로그 레벨 (DEBUG, INFO, WARNING, ERROR, FATAL)
  - 콘솔/파일 동시 출력
  - 컬러 출력 지원
  - Google Test 단위 테스트
- **파일**: `logger/README.md` 참조

### 2. My String 라이브러리  
- **목적**: 표준 문자열 함수 재구현
- **기능**: memchr, memcmp, strcpy, strcat, strtok 등
- **특징**: C 표준 라이브러리 호환 인터페이스

### 3. Linked List
- **목적**: 범용 연결 리스트 구현
- **기능**: 
  - 전처리 매크로를 이용한 타입 안전성
  - 다양한 데이터 타입 지원
  - 삽입, 삭제, 검색 연산

## 빌드 요구사항

- **컴파일러**: GCC 또는 Clang
- **표준**: C11
- **시스템**: POSIX 호환 (pthread 지원)
- **도구**: Make
- **선택사항**: Google Test (logger 단위 테스트용)

## 시작하기

```bash
# 전체 프로젝트 클론 후
git clone <repository-url>
cd linux-c-lab

# 전체 빌드
make all

# 테스트 실행
make test

# 도움말 확인
make help
```

## 개발 환경

이 프로젝트는 다음 환경에서 개발되었습니다:
- macOS/Linux
- GCC/Clang 컴파일러
- Make 빌드 시스템
- IDE: CLion, VS Code 등
