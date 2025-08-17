# 범용 연결 리스트 (Generic Linked List) 학습 가이드

## 🎯 학습 목표

이 과제를 통해 다음과 같은 핵심 개념들을 학습할 수 있습니다.

## 1. C 전처리기와 매크로 프로그래밍

### 타입 안전 매크로
```c
#define INSERT_INT(list, value) \
    linkedlist_insert_back(list, &(int){value}, TYPE_INT, sizeof(int))

#define GET_STRING(list, index) \
    ((char*)linkedlist_get(list, index))
```

**학습 포인트:**
- **함수형 매크로**: 복잡한 함수 호출을 단순화
- **복합 리터럴**: `&(int){value}`로 임시 객체 생성
- **do-while(0) 패턴**: 안전한 다중 문장 매크로
- **타입 캐스팅**: 안전한 void* 포인터 변환

### 범용 자료구조 설계
```c
typedef struct Node {
    void *data;          // 실제 데이터
    DataType type;       // 타입 정보
    size_t data_size;    // 크기 정보
    struct Node *next;   // 다음 노드
} Node;
```

**장점:**
- **범용성**: 하나의 리스트에 모든 타입 저장
- **타입 안전성**: 매크로를 통한 컴파일 타임 검사
- **메모리 효율**: 필요한 만큼만 동적 할당
- **확장성**: 새로운 타입 쉽게 추가 가능

## 2. 자료구조 기초

### 연결 리스트의 개념
- **동적 자료구조**: 런타임에 크기가 변할 수 있는 자료구조
- **노드 기반 구조**: 데이터와 포인터를 포함하는 노드들의 연결
- **메모리 효율성**: 필요한 만큼만 메모리를 할당

### 전통적 방법 vs 범용 연결 리스트 비교
| 특성 | 타입별 분리 | 범용 리스트 |
|------|------------|-------------|
| 사용성 | 타입별 별도 리스트 | 하나의 리스트에 모든 타입 |
| 메모리 사용 | 타입별 최적화 | 타입 정보 추가 저장 |
| 타입 안전성 | 컴파일 타임 보장 | 매크로로 런타임 검사 보완 |
| 코드 복잡도 | 타입별 중복 코드 | 단일 구현 |
| 실용성 | 동일 타입만 저장 | 혼합 타입 저장 가능 |

## 3. 매크로 설계 패턴

### 타입 안전 삽입 매크로
```c
#define INSERT_INT(list, value) \
    linkedlist_insert_back(list, &(int){value}, TYPE_INT, sizeof(int))

#define INSERT_STRING(list, value) \
    do { \
        char *str = malloc(strlen(value) + 1); \
        strcpy(str, value); \
        linkedlist_insert_back(list, str, TYPE_STRING, strlen(value) + 1); \
    } while(0)
```

### 타입 안전 접근 매크로
```c
#define GET_INT(list, index) \
    (*(int*)linkedlist_get(list, index))

#define GET_CUSTOM(list, index, type) \
    ((type*)linkedlist_get(list, index))
```

## 4. 고급 매크로 기법

### 토큰 결합과 문자열화
```c
#define STRINGIFY(x) #x           // 토큰을 문자열로 변환
#define CONCAT(a, b) a##b         // 토큰 결합
#define FUNC_NAME(type) linkedlist_##type##_create
```

### 가변 인수 매크로
```c
#define DEBUG_PRINT(fmt, ...) \
    printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)
```

### 매크로 안전성
```c
#define MAX(a, b) ((a) > (b) ? (a) : (b))  // 괄호로 감싸기
#define SAFE_FREE(ptr) do { \
    if (ptr) { \
        free(ptr); \
        ptr = NULL; \
    } \
} while(0)
```

## 5. 실무 적용과 주의사항

### 매크로 사용의 장점
- **코드 생성 자동화**: 반복적인 코드 작성 방지
- **타입 안전성**: 컴파일 타임 오류 검출
- **성능 최적화**: 런타임 오버헤드 제거
- **유지보수성**: 중앙화된 로직 관리

### 매크로 사용의 단점과 주의사항
- **디버깅 어려움**: 매크로 확장으로 인한 복잡성
- **컴파일 시간 증가**: 많은 코드 생성
- **코드 크기 증가**: 각 타입별로 별도 코드 생성
- **가독성 저하**: 복잡한 매크로 문법

### Best Practices
```c
// 1. 매크로명은 대문자 사용
#define DECLARE_LIST(TYPE)

// 2. 복잡한 매크로는 do-while(0) 패턴 사용
#define SAFE_DELETE(list, index) do { \
    if (list && index < list->size) { \
        linkedlist_delete_at(list, index); \
    } \
} while(0)

// 3. 매크로 인수에 괄호 사용
#define SQUARE(x) ((x) * (x))

// 4. 헤더 가드 사용
#ifndef LINKED_LIST_H
#define LINKED_LIST_H
```

## 6. 알고리즘 구현

### 기본 연산들
- **삽입**: 앞쪽, 뒤쪽, 특정 위치
- **삭제**: 앞쪽, 뒤쪽, 특정 위치
- **검색**: 인덱스 기반 접근
- **순회**: 전체 리스트 탐색

### 시간 복잡도 이해
- 삽입/삭제: O(1) ~ O(n)
- 검색: O(n)
- 공간 복잡도: O(n)

## 7. 실습을 통한 학습

### 단계별 접근
1. **기본 구조** 이해: void* 기반 노드와 타입 정보 관리
2. **매크로 설계**: 타입별 안전한 삽입/접근 함수
3. **메모리 관리**: 동적 할당과 타입별 해제 처리
4. **혼합 데이터**: 하나의 리스트에 다양한 타입 저장
5. **실제 사용**: 구조체, 문자열 등 복합 타입 처리

### 확장 과제
- **타입 체크**: 런타임 타입 검증 매크로 추가
- **직렬화**: 리스트 데이터를 파일로 저장/로드
- **정렬 기능**: 타입별 정렬 함수 구현
- **반복자**: 타입 안전한 순회 매크로 개발

## 8. 고급 주제

### 메타프로그래밍
```c
// X-Macro 패턴
#define LIST_TYPES \
    X(int) \
    X(double) \
    X(char)

#define X(type) DECLARE_LIST(type);
LIST_TYPES
#undef X
```

### 조건부 기능
```c
#ifdef DEBUG_MODE
#define DBG_PRINT(msg) printf("DEBUG: %s\n", msg)
#else
#define DBG_PRINT(msg)
#endif
```

## 🔍 핵심 학습 포인트

1. **void 포인터 활용**: 타입 독립적 데이터 저장과 관리
2. **매크로 프로그래밍**: 타입 안전성과 사용 편의성 제공
3. **메모리 관리**: 동적 할당과 타입별 적절한 해제
4. **데이터 타입 추상화**: enum을 통한 타입 정보 관리
5. **API 설계**: 직관적이고 안전한 인터페이스 제공

## 🚀 실무 연관성

이 과제는 다음과 같은 실무 기술과 직결됩니다:

- **데이터베이스 시스템**: 다양한 타입의 레코드 저장
- **네트워크 프로그래밍**: 혼합 타입 메시지 처리
- **컴파일러 개발**: AST 노드의 다양한 타입 관리
- **게임 엔진**: 다양한 게임 객체 컨테이너
- **파일 시스템**: 다양한 메타데이터 저장

## 💡 실제 사용 예시

```c
LinkedList *config_list = linkedlist_create();

// 설정 파일 데이터 저장
INSERT_STRING(config_list, "server_host");
INSERT_INT(config_list, 8080);
INSERT_DOUBLE(config_list, 3.14159);
INSERT_CUSTOM(config_list, &user_config, sizeof(UserConfig));

// 타입 안전한 접근
char *host = GET_STRING(config_list, 0);
int port = GET_INT(config_list, 1);
```

이 과제는 단순한 자료구조 구현을 넘어서, **실무에서 자주 마주치는 혼합 타입 데이터 처리 문제**를 해결하는 실용적인 기법을 학습할 수 있는 훌륭한 기회입니다.