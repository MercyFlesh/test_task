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
#include <sys/utsname.h>
#include <arpa/inet.h>

/**
 * @brief class implements client socket
 * 
 */
class Client
{
    const std::string ip;
    const int port;
    bool exit_flag;

public:
    Client();
    Client(const std::string& ip, const int& port);
    ~Client(); 

/**
 * @brief build socket and starts loop() in handler_thread_loop
 * 
 */
    void start();

/**
 * @brief adds msg to the queue pool_send_messages for sending 
 * 
 * @param msg 
 */
    void push_message_to_send(const std::string& msg);

/**
 * @brief get the front received message of pool_get_messages
 * 
 * @return string 
 */
    std::string get_top_recv_message();
    
private:
/**
 * @detailed starts a loop for connecting to the server 
 * and starting in thread method client_send();
 * terminates when calling destructor, when exit_flag set in true in stop().
 */
    void loop();

/**
 * @brief called in the destructor;
 * close socket and wait handler_thread_loop
 */
    void stop();

/**
 * @brief sends data on socket from the queue pool_send_messages
 * 
 */
    void client_send();

    std::queue<std::string> pool_send_messages;
    std::thread handler_thread_loop;
    std::mutex mx_send;
    
    int client_socket;
    struct sockaddr_in sockAddress;
};