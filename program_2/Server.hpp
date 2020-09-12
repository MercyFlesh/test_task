#pragma once

#include <iostream>
#include <string>
#include <queue>
#include <array>
#include <thread>
#include <mutex>
#include <cerrno>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/utsname.h>
#include <arpa/inet.h>


/**
 * @brief class implements server socket
 * 
 */
class Server
{   
    const std::string ip;
    const int port;
    bool exit_flag;

public:
    Server();
    Server(const std::string& ip, const int& port);
    ~Server();
    
/**
 * @brief bind and listen socket 
 * and starts loop() in handler_thread_loop
 */
    void start();

/**
 * @brief Get the top receved message from pool_get_messages queue
 * 
 * @return string top message
 */
    std::string get_top_recv_message();

private:
/**
 * @brief starts a loop for accept connecting on the socket 
 * and starting in thread method server_get();
 * terminates when calling destructor, when exit_flag set in true in stop().
 */
    void loop();

/**
 * @brief called in the destructor;
 * close socket and wait handler_thread_loop
 */
    void stop();

/**
 * @brief read data from socket 
 * and push received data to pool_get_messages
 */
    void server_get();
    
    std::queue<std::string> pool_get_messages;
    std::thread handler_thread_loop;
    std::mutex mx_get;

    int server_socket;
    int client_socket_acc;
    struct sockaddr_in sockAddress;
};