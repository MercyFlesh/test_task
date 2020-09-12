#include "Server.hpp"

using namespace std;


/**
 * @brief creating Server object 
 * and processing received messages from client
 * 
 * @param exit_flag exit status flag from main thread
 */
void get_user_message(char& exit_flag)
{
    Server server;
    server.start();
    string message;
    
    while(exit_flag != 10)
    {
        message = server.get_top_recv_message();
        if (!message.empty())
        {
            if (message.size() > 2 && stoi(message) % 32 == 0)
            {
                cout << "\x1b[32m[+]\x1b[0m Received correct sum " << message << endl;
            }
            else
            {
                cout << "\x1b[31m[-]\x1b[0m Error: invalid sum " << message << endl;
            }
        }
    }
}


int main()
{
    char exit_flag;
    thread th_(get_user_message, ref(exit_flag));

    while (exit_flag != 10)
    {
        cin.get(exit_flag);
    }
    
    th_.join();
    return 0;
}