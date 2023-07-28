#include <stdio.h>
#include <vector>
#include <string>
#include<utility>
using namespace std;

class AbstractProcess{
public:
    virtual int getPriority() = 0;
    virtual vector< pair< string, string> > getTCB() = 0;
    virtual bool executeOneQuantum() = 0;
    virtual void killProcess() = 0;
    
}
