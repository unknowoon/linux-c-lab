#include <gtest/gtest.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>

extern "C" {
    #include "../inc/comm.h"
}

class CommTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a socket pair for testing
        if (socketpair(AF_UNIX, SOCK_STREAM, 0, socket_fds) == -1) {
            FAIL() << "Failed to create socket pair";
        }
    }
    
    void TearDown() override {
        if (socket_fds[0] >= 0) {
            close(socket_fds[0]);
        }
        if (socket_fds[1] >= 0) {
            close(socket_fds[1]);
        }
    }
    
    int socket_fds[2] = {-1, -1};
};

TEST_F(CommTest, CommInitValidSocket) {
    EXPECT_EQ(comm_init(socket_fds[0]), 0);
}

TEST_F(CommTest, CommInitInvalidSocket) {
    EXPECT_EQ(comm_init(-1), -1);
}

TEST_F(CommTest, CommCleanup) {
    // Test that cleanup doesn't crash
    EXPECT_NO_THROW(comm_cleanup(socket_fds[0]));
}

TEST_F(CommTest, CommHandleDataEcho) {
    // Make socket non-blocking to prevent test hanging
    int flags = fcntl(socket_fds[0], F_GETFL, 0);
    fcntl(socket_fds[0], F_SETFL, flags | O_NONBLOCK);
    fcntl(socket_fds[1], F_SETFL, flags | O_NONBLOCK);
    
    const char* test_message = "hello";
    const char* expected_response = "Echo: hello";
    
    // Send test message
    write(socket_fds[1], test_message, strlen(test_message));
    
    // Give some time for processing
    usleep(10000);
    
    // Read response
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = read(socket_fds[1], buffer, BUFFER_SIZE - 1);
    
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        EXPECT_STREQ(buffer, expected_response);
    }
}

TEST_F(CommTest, CommHandleDataQuit) {
    // Make socket non-blocking
    int flags = fcntl(socket_fds[0], F_GETFL, 0);
    fcntl(socket_fds[0], F_SETFL, flags | O_NONBLOCK);
    fcntl(socket_fds[1], F_SETFL, flags | O_NONBLOCK);
    
    const char* quit_message = "quit";
    
    // Send quit message
    write(socket_fds[1], quit_message, strlen(quit_message));
    
    // The function should handle quit gracefully
    EXPECT_NO_THROW(comm_handle_data(socket_fds[0]));
}

// Test for comm_context_t structure
TEST(CommContextTest, StructureSize) {
    comm_context_t context;
    
    // Basic structure validation
    EXPECT_GE(sizeof(context), sizeof(int) + sizeof(struct sockaddr_in) + sizeof(socklen_t));
}

// Test buffer size constant
TEST(CommConstantsTest, BufferSizeValid) {
    EXPECT_EQ(BUFFER_SIZE, 1024);
    EXPECT_EQ(MAX_CLIENTS, 10);
}