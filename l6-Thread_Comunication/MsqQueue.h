#include "Message.h"

class MsqQueue
{
public:
    MsqQueue(unsigned long maxSize);
    void send(unsigned long id, Message* msg = NULL);
    Message * receive(unsigned long& id);
    ~MsqQueue();

private:
    /* data */

};


