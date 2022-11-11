#include <iostream>
using namespace std;

class Message
{

public:    
    virtual ~Message(){}
};

/*Forklaring på, hvor destructoren skal være virtual
https://stackoverflow.com/questions/461203/when-to-use-virtual-destructors*/

