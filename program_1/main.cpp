#include <iostream>
#include <thread>

#include "ProducerConsumer.hpp"

using namespace std;


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ConcurrentQueue<string> buf;
    ProducerConsumer producer_consumer(buf);
    
    thread th_produce(&ProducerConsumer::produce, ref(producer_consumer));
    thread th_consume(&ProducerConsumer::consume, ref(producer_consumer));

    th_produce.join();
    th_consume.join();

    return 0;
}