#include "linked_list.h"

typedef struct {
    char name[20];
    int age;
    double score;
} Student;

int main() {
    printf("=== 범용 연결 리스트 예제 (하나의 리스트에 다양한 타입) ===\n\n");
    
    LinkedList *mixed_list = linkedlist_create();
    
    printf("1. 매크로를 사용한 타입 안전 삽입:\n");
    
    INSERT_INT(mixed_list, 42);
    printf("정수 42 추가 후: ");
    linkedlist_print(mixed_list);
    
    INSERT_DOUBLE(mixed_list, 3.14);
    printf("실수 3.14 추가 후: ");
    linkedlist_print(mixed_list);
    
    INSERT_STRING(mixed_list, "Hello World");
    printf("문자열 추가 후: ");
    linkedlist_print(mixed_list);
    
    INSERT_CHAR(mixed_list, 'A');
    printf("문자 'A' 추가 후: ");
    linkedlist_print(mixed_list);
    
    printf("\n2. 구조체 타입 삽입:\n");
    Student student = {"김철수", 20, 85.5};
    INSERT_CUSTOM(mixed_list, &student, sizeof(Student));
    printf("학생 구조체 추가 후: ");
    linkedlist_print(mixed_list);
    
    printf("\n3. 매크로를 사용한 타입 안전 접근:\n");
    printf("인덱스 0 (정수): %d\n", GET_INT(mixed_list, 0));
    printf("인덱스 1 (실수): %.2f\n", GET_DOUBLE(mixed_list, 1));
    printf("인덱스 2 (문자열): %s\n", GET_STRING(mixed_list, 2));
    printf("인덱스 3 (문자): %c\n", GET_CHAR(mixed_list, 3));
    
    Student *s = GET_CUSTOM(mixed_list, 4, Student);
    if (s) {
        printf("인덱스 4 (구조체): %s, %d세, %.1f점\n", s->name, s->age, s->score);
    }
    
    printf("\n4. 타입 정보 확인:\n");
    const char* type_names[] = {"INT", "DOUBLE", "STRING", "CHAR", "CUSTOM"};
    for (size_t i = 0; i < linkedlist_size(mixed_list); i++) {
        DataType type = linkedlist_get_type(mixed_list, i);
        printf("인덱스 %zu: %s 타입\n", i, type_names[type]);
    }
    
    printf("\n5. 리스트 정보:\n");
    printf("총 크기: %zu\n", linkedlist_size(mixed_list));
    printf("비어있음: %s\n", linkedlist_is_empty(mixed_list) ? "예" : "아니오");
    
    printf("\n6. 삭제 연산:\n");
    linkedlist_delete_at(mixed_list, 2);
    printf("인덱스 2 삭제 후: ");
    linkedlist_print(mixed_list);
    
    printf("\n=== 전처리 매크로의 장점 ===\n");
    printf("1. 타입 안전성: INSERT_INT()는 정수만, GET_STRING()는 문자열만 처리\n");
    printf("2. 사용 편의성: 복잡한 함수 호출을 간단한 매크로로 단순화\n");
    printf("3. 코드 가독성: 타입별 명확한 의도 표현\n");
    printf("4. 컴파일 타임 최적화: 매크로 확장으로 런타임 오버헤드 최소화\n");
    printf("5. 범용성: 하나의 리스트에 모든 타입 저장 가능\n");
    
    linkedlist_destroy(mixed_list);
    
    return 0;
}