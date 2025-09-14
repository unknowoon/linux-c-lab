#include <gtest/gtest.h>

// C 함수를 C++에서 사용
extern "C" {
    #include <string.h>
    
    // 테스트할 C 함수들 (예시)
    int c_add(int a, int b) {
        return a + b;
    }
    
    int c_string_length(const char* str) {
        if (str == NULL) return -1;
        return strlen(str);
    }
    
    char* c_copy_string(const char* src) {
        if (src == NULL) return NULL;
        char* dest = (char*)malloc(strlen(src) + 1);
        strcpy(dest, src);
        return dest;
    }
}

// C 함수 테스트
TEST(CFunctionTest, AddTest) {
    EXPECT_EQ(c_add(5, 3), 8);
    EXPECT_EQ(c_add(-2, 7), 5);
}

TEST(CFunctionTest, StringLengthTest) {
    EXPECT_EQ(c_string_length("hello"), 5);
    EXPECT_EQ(c_string_length(""), 0);
    EXPECT_EQ(c_string_length(NULL), -1);  // NULL 처리
}

TEST(CFunctionTest, CopyStringTest) {
    char* result = c_copy_string("test");
    
    ASSERT_NE(result, nullptr);           // NULL이 아닌지 먼저 확인
    EXPECT_STREQ(result, "test");         // 내용 확인
    
    free(result);  // 메모리 해제 중요!
    
    // NULL 입력 테스트
    EXPECT_EQ(c_copy_string(NULL), nullptr);
}