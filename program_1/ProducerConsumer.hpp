#pragma once

#include <iostream>
#include <sstream>
#include <algorithm>
#include <utility>

#include "ConcurrentQueue.hpp"
#include "Client.hpp"

/**
 * @brief class for multithreading processing 
 * user input
 */
class ProducerConsumer
{
public:
/**
 * @brief Construct a new ProducerConsumer object
 * 
 * @param shm_buf is used to create a message 
 * queue as a shared buffer
 */
    ProducerConsumer(ConcurrentQueue<std::string>& shm_buf);
    
/**
 * @brief function to validate user input 
 * and write to the queue
 */
    void produce();

/**
 * @brief the function reads data from the shared buffer, 
 * performs calculations and sends data to the socket
 */
    void consume();

private:
    ConcurrentQueue<std::string>&  shm_buf;
    Client client;
};