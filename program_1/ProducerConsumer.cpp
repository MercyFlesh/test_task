#include "ProducerConsumer.hpp"

using namespace std;


ProducerConsumer::ProducerConsumer(ConcurrentQueue<string>& shm_buf) :
    shm_buf(shm_buf)
{
    client.start();
}


void ProducerConsumer::produce()
{
    string user_str;
    while (true)
    {
        getline(cin, user_str);
        if (user_str.empty())
        {
            shm_buf.push("");
            break;
        }

        if (user_str.size() <= 64 &&
            all_of(user_str.begin(), user_str.end(),
                [](const char& ch) {
                    return isdigit(ch);
                })
        )
        {
            sort(user_str.begin(), user_str.end(),
                [](const char& ch_1, const char& ch_2) {
                    return ch_1 > ch_2;
                });

            string new_string;
            new_string.reserve(user_str.size() * 2);

            for (const char& ch : move(user_str))
            {
                if (static_cast<int>(ch) % 2 == 0)
                {
                    new_string.append("KB");
                }
                else
                {
                    new_string.push_back(ch);
                }
            }
            
            shm_buf.push(new_string);
        }    
    }
}


void ProducerConsumer::consume()
{
    while (true)
    {
        string str = shm_buf.pop();
        if (!str.empty())
        {
            cout << "\x1b[32m[+]\x1b[0m Received data: " << str << endl;

            int sum = 0;
            for (char& ch : str)
                if (isdigit(ch))
                    sum += ch - '0';

            client.push_message_to_send(to_string(sum));
        }
        else
            break;
    }
}