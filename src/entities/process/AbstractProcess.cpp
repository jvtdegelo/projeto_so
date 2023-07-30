#include <stdio.h>

class AbstractProcess{
public:
    virtual int getPriority() = 0;
    virtual int getPID() = 0;
    virtual std::vector< std::pair< std::string, std::string> > getTCB() = 0;
    virtual bool executeOneQuantum() = 0;
    virtual void killProcess() = 0;
    
    virtual ~MyAbstractClass() {}
}
