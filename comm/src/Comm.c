#include "../inc/comm.h"

int comm_init(int socket_fd) {
    if (socket_fd < 0) {
        log_error("Comm: Invalid socket file descriptor");
        return -1;
    }
    
    log_info("Comm: Initialized with socket fd %d (PID: %d)", socket_fd, getpid());
    return 0;
}

int comm_handle_data(void) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received, bytes_sent;
    
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        
        bytes_received = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
        
        if (bytes_received <= 0) {
            if (bytes_received == 0) {
                log_info("Comm: Client disconnected");
            } else {
                log_error("Comm: read failed: %s", strerror(errno));
            }
            break;
        }
        
        buffer[bytes_received] = '\0';
        log_debug("Comm: Received %ld bytes: %s", bytes_received, buffer);
        
        if (strncmp(buffer, "quit", 4) == 0) {
            log_info("Comm: Client requested to quit");
            break;
        }
        
        char response[BUFFER_SIZE];
        snprintf(response, BUFFER_SIZE, "Echo: %s", buffer);
        
        bytes_sent = write(STDOUT_FILENO, response, strlen(response));
        if (bytes_sent < 0) {
            log_error("Comm: write failed: %s", strerror(errno));
            break;
        }
        
        log_debug("Comm: Sent %ld bytes: %s", bytes_sent, response);
    }
    
    return 0;
}

void comm_cleanup(void) {
    log_info("Comm: Socket closed");
    // Note: stdin/stdout will be automatically closed when process exits
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
}

int main(void) {
    char log_filename[256];
    int socket_fd = STDIN_FILENO;
    
    snprintf(log_filename, sizeof(log_filename), "comm_%d.log", getpid());
    logger_init(log_filename, LOG_INFO);
    log_info("Comm: Starting child process %d", getpid());
    
    comm_init(socket_fd);
    
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    
    if (getpeername(STDIN_FILENO, (struct sockaddr *)&client_addr, &client_len) == 0) {
        log_info("Comm: Handling client %s:%d", 
               inet_ntoa(client_addr.sin_addr), 
               ntohs(client_addr.sin_port));
    } else {
        log_info("Comm: Handling client (address unknown)");
    }
    
    comm_handle_data();
    comm_cleanup();
    
    log_info("Comm: Process %d terminating", getpid());
    logger_close();
    return 0;
}