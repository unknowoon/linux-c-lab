#include <gtest/gtest.h>

// NOTE: 실행 방법
// g++ -std=c++17 basic_example.cpp -lgtest -lgtest_main -pthread -o basic_test

// 테스트할 간단한 함수들
int add(int a, int b) {
    return a + b;
}

bool is_even(int n) {
    return n % 2 == 0;
}

// 1. 가장 기본적인 테스트
TEST(BasicTest, AddFunction) {
    EXPECT_EQ(add(2, 3), 5);        // 2 + 3 = 5 인지 확인
    EXPECT_EQ(add(-1, 1), 0);       // -1 + 1 = 0 인지 확인
    EXPECT_EQ(add(0, 0), 0);        // 0 + 0 = 0 인지 확인
}

// 2. 불린 값 테스트
TEST(BasicTest, IsEvenFunction) {
    EXPECT_TRUE(is_even(4));        // 4는 짝수
    EXPECT_FALSE(is_even(3));       // 3은 홀수
    EXPECT_TRUE(is_even(0));        // 0은 짝수
}

// 3. 문자열 테스트
TEST(BasicTest, StringTest) {
    std::string result = "hello";
    EXPECT_STREQ(result.c_str(), "hello");  // 문자열 비교
    EXPECT_EQ(result.length(), 5);          // 길이 확인
}