#include <gtest/gtest.h>
extern "C" {
#include "../inc/logger.h"
}
#include <fstream>
#include <string>
#include <thread>
#include <vector>
#include <chrono>

class LoggerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 테스트 시작 전에 로그 파일 정리
        std::remove("test_unit.log");
    }

    void TearDown() override {
        logger_close();
        std::remove("test_unit.log");
    }

    std::string readLogFile(const std::string& filename) {
        std::ifstream file(filename);
        std::string content((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
        return content;
    }
};

// 기본 초기화 테스트
TEST_F(LoggerTest, InitializationTest) {
    logger_init("test_unit.log", LOG_DEBUG);
    
    // 로그 파일이 생성되었는지 확인
    std::ifstream file("test_unit.log");
    EXPECT_TRUE(file.good());
}

// 로그 레벨 테스트
TEST_F(LoggerTest, LogLevelTest) {
    logger_init("test_unit.log", LOG_WARNING);
    
    log_debug("Debug message");
    log_info("Info message");
    log_warning("Warning message");
    log_error("Error message");
    
    std::string content = readLogFile("test_unit.log");
    
    // DEBUG, INFO는 출력되지 않아야 함
    EXPECT_EQ(content.find("Debug message"), std::string::npos);
    EXPECT_EQ(content.find("Info message"), std::string::npos);
    
    // WARNING, ERROR는 출력되어야 함
    EXPECT_NE(content.find("Warning message"), std::string::npos);
    EXPECT_NE(content.find("Error message"), std::string::npos);
}

// 로그 레벨 변경 테스트
TEST_F(LoggerTest, SetLogLevelTest) {
    logger_init("test_unit.log", LOG_DEBUG);
    
    log_debug("First debug message");
    logger_set_level(LOG_ERROR);
    log_debug("Second debug message");
    log_error("Error message");
    
    std::string content = readLogFile("test_unit.log");
    
    EXPECT_NE(content.find("First debug message"), std::string::npos);
    EXPECT_EQ(content.find("Second debug message"), std::string::npos);
    EXPECT_NE(content.find("Error message"), std::string::npos);
}

// 파일 출력 제어 테스트
TEST_F(LoggerTest, FileOutputControlTest) {
    logger_init("test_unit.log", LOG_DEBUG);
    
    log_info("Message before disable");
    logger_enable_file(0);
    log_info("Message after disable");
    logger_enable_file(1);
    log_info("Message after enable");
    
    std::string content = readLogFile("test_unit.log");
    
    EXPECT_NE(content.find("Message before disable"), std::string::npos);
    EXPECT_EQ(content.find("Message after disable"), std::string::npos);
    EXPECT_NE(content.find("Message after enable"), std::string::npos);
}

// 포맷 문자열 테스트
TEST_F(LoggerTest, FormattedOutputTest) {
    logger_init("test_unit.log", LOG_DEBUG);
    
    int value = 42;
    float pi = 3.14f;
    const char* str = "test";
    
    log_info("Integer: %d, Float: %.2f, String: %s", value, pi, str);
    
    std::string content = readLogFile("test_unit.log");
    
    EXPECT_NE(content.find("Integer: 42"), std::string::npos);
    EXPECT_NE(content.find("Float: 3.14"), std::string::npos);
    EXPECT_NE(content.find("String: test"), std::string::npos);
}

// 멀티스레드 안전성 테스트
TEST_F(LoggerTest, ThreadSafetyTest) {
    logger_init("test_unit.log", LOG_DEBUG);
    
    const int num_threads = 4;
    const int messages_per_thread = 10;
    std::vector<std::thread> threads;
    
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([i, messages_per_thread]() {
            for (int j = 0; j < messages_per_thread; ++j) {
                log_info("Thread %d Message %d", i, j);
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        });
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    std::string content = readLogFile("test_unit.log");
    
    // 모든 메시지가 기록되었는지 확인
    int message_count = 0;
    size_t pos = 0;
    while ((pos = content.find("Thread", pos)) != std::string::npos) {
        message_count++;
        pos++;
    }
    
    EXPECT_EQ(message_count, num_threads * messages_per_thread);
}

// 로그 파일 닫기 테스트
TEST_F(LoggerTest, CloseTest) {
    logger_init("test_unit.log", LOG_DEBUG);
    log_info("Before close");
    logger_close();
    
    // 닫은 후에는 파일에 쓰기가 되지 않아야 함
    log_info("After close");
    
    std::string content = readLogFile("test_unit.log");
    
    EXPECT_NE(content.find("Before close"), std::string::npos);
    EXPECT_EQ(content.find("After close"), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}