#include "Client.hpp"
#include <thread>
#include <chrono>

using namespace std;


Client::Client() :
    ip("127.0.0.1"), port(5000), exit_flag(false)
{
}


Client::Client(const string& ip, const int& port) :
    ip(ip), port(port), exit_flag(false)
{
}


Client::~Client()
{
    stop();  
}


void Client::start()
{
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
        perror("failed to create socket");

    if (fcntl(client_socket, F_SETFL, O_NONBLOCK) == -1)
        perror("failed to set descriptor flag");
    
    sockAddress.sin_family = AF_INET;
    sockAddress.sin_port = htons(port);
    sockAddress.sin_addr.s_addr = inet_addr(ip.c_str());
    
    handler_thread_loop = thread([this]{ loop(); });
}


void Client::loop()
{
    while(!exit_flag)
    {
        int resault = connect(client_socket, (struct sockaddr*)&sockAddress, sizeof(sockAddress));
        if (resault == -1)
        {
            this_thread::sleep_for(chrono::seconds(1));
        }
        else
        {
            thread th_send([this]{ client_send(); });
            
            th_send.join();
        }
    }
}


void Client::push_message_to_send(const string& msg)
{
    pool_send_messages.push(msg);
}


void Client::client_send()
{
    while (!exit_flag)
    {
        mx_send.lock();
        if (!pool_send_messages.empty())
        {
            vector<char> message(pool_send_messages.front().begin(), pool_send_messages.front().end());

            int sendcount = send(client_socket, &message[0], message.size(), 0);
            if (sendcount == -1) 
            {
                this_thread::sleep_for(chrono::seconds(1));
            }
            else
            {
                pool_send_messages.pop();
            }
            mx_send.unlock();                
        }
        else
        {
            mx_send.unlock();
        }
    }  
}


void Client::stop()
{
    exit_flag = true;
    handler_thread_loop.join();
    close(client_socket);
}