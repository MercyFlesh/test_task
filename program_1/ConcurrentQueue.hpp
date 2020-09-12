#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>


/**
 * @brief class for creating synchronization of 
 * add data to shared buffer and receiving
 * 
 * @tparam T the type of data to placed queue
 */
template<typename T>
class ConcurrentQueue
{
public:
    ConcurrentQueue() = default;
    ~ConcurrentQueue() = default;

    void push(const T& message);
    T pop();

private:
    std::queue<T> messages;
    std::mutex mx;
    std::condition_variable cv;
};


template<typename T>
void ConcurrentQueue<T>::push(const T& message)
{
    messages.push(message);
    cv.notify_one();
}


template<typename T>
T ConcurrentQueue<T>::pop()
{  
    std::unique_lock<std::mutex> mx_lock(mx);
    cv.wait(mx_lock);

    T message = messages.front();
    messages.pop();
    
    return message;
}