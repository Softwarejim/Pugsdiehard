#include "Message.h"
#include <queue>
#include <pthread.h>
using namespace std;

class MsqQueue : public Message
{
public:
    MsqQueue(unsigned long maxSize);
    void send(unsigned long id, Message* msg = NULL);
    Message * receive(unsigned long& id);
    ~MsqQueue();
    bool isFull();
    bool isEmpty();

private:
    unsigned long maxsize_;
    struct Item
    {
        unsigned long id_;
        Message *msg_;
    };
    queue<Item> messageQueue_;
    pthread_mutex_t mutex;
    pthread_cond_t sig_senders;
    pthread_cond_t sig_receivers;
};


