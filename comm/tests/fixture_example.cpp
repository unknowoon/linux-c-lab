#include <gtest/gtest.h>
#include <vector>

// 테스트에서 공통으로 사용할 데이터와 설정
class VectorTest : public ::testing::Test {
protected:
    // 각 테스트 전에 실행됨
    void SetUp() override {
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        std::cout << "SetUp: vector initialized\n";
    }
    
    // 각 테스트 후에 실행됨
    void TearDown() override {
        vec.clear();
        std::cout << "TearDown: vector cleaned\n";
    }
    
    // 테스트에서 공통으로 사용할 데이터
    std::vector<int> vec;
};

// 픽스처를 사용하는 테스트들
TEST_F(VectorTest, InitialSize) {
    EXPECT_EQ(vec.size(), 3);
}

TEST_F(VectorTest, FirstElement) {
    EXPECT_EQ(vec[0], 1);
}

TEST_F(VectorTest, AddElement) {
    vec.push_back(4);
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec[3], 4);
}