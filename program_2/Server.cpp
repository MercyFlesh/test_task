#include "Server.hpp"

using namespace std;


Server::Server() :
    ip("0.0.0.0"), port(5000), exit_flag(false)
{
}


Server::Server(const string& ip, const int& port) :
    ip(ip), port(port), exit_flag(false)
{
}


Server::~Server()
{
    stop();
}


void Server::start()
{
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        perror("failed to create socket");

    if (fcntl(server_socket, F_SETFL, O_NONBLOCK) == -1)
        perror("failed to set descriptor flag");
    
    sockAddress.sin_family = AF_INET;
    sockAddress.sin_port = htons(port);
    sockAddress.sin_addr.s_addr = inet_addr(ip.c_str());
        
    if (bind(server_socket, (struct sockaddr*)&sockAddress, sizeof(sockAddress)) == -1)
        perror("failed bind socket");
    
    int optval = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    
    if (listen(server_socket, SOMAXCONN) == -1)
        perror("failed to set socket to listen");
    

    handler_thread_loop = thread([this]{ loop(); });
}


void Server::loop()
{
    while(!exit_flag)
    {
        client_socket_acc = accept(server_socket, (struct sockaddr*)NULL, NULL);
        if (client_socket_acc == -1)
        {
            this_thread::sleep_for(chrono::seconds(1));
        }
        else
        {
            thread th_get([this]{ server_get(); });

            th_get.join();
        }
    }
}


void Server::server_get()
{
    while(!exit_flag)
    {
        const int RCV_SIZE = 4096;
        array<char, RCV_SIZE> message;
        int reccount = recv(client_socket_acc, &message[0], RCV_SIZE, 0);
        if (reccount == -1) 
        {
            this_thread::sleep_for(chrono::seconds(1));
        }
        else if (reccount == 0)
        {
            this_thread::sleep_for(chrono::seconds(1));
        }
        else
        {   
            mx_get.lock();
            pool_get_messages.push(message.data());
            mx_get.unlock();
        }
    }
}


string Server::get_top_recv_message()
{
    string top;

    mx_get.lock();
    if (!pool_get_messages.empty())
    {
        top = pool_get_messages.front();
        pool_get_messages.pop();
    }
    mx_get.unlock();

    top.shrink_to_fit();
    return top;
}


void Server::stop()
{
    exit_flag = true;
    handler_thread_loop.join();
    
    shutdown(client_socket_acc, SHUT_RDWR);
    close(client_socket_acc);
    close(server_socket);
}