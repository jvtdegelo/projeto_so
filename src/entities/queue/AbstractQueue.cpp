#include <stdio.h>
using namespace std;

class AbstractQueue{
public:
    virtual AbstractProcess next() = 0;
    virtual void add(AbstractProcess) = 0;
    virtual AbstractProcess remove(int pid) = 0;
    virtual bool isEmpty() = 0;
}
