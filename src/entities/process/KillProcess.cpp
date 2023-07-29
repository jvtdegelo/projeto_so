#include <stdio.h>
#include <vector>
#include <string>
#include<utility>
using namespace std;

class killProcess: public AbstractProcess{
public:
  KillProcess(int pid, int pidToKill, MemoryHandler& memoryHandler, AbstractQueue& processQueue): 
  priority(1), pid(pid), pidToKill(pidToKill), memoryHandler(memoryHandler), processQueue(processQueue) {}

  int getPriority() override {
    return priority;
  }

  vector< pair< string, string> > getTCB() override {
    vector< pair < string, string> > tcb;
    tcb.push_back(make_pair("PID", to_string(pid)));
    tcb.push_back(make_pair("Priority", to_string(priority))); 

    return tcb;
  }

  bool executeOneQuantum() override {
    process = processQueue.remove(pidToKill);
    process.killProcess();
    return true;
  }
  
  void killProcess() override {
    return;
  }

private:
  int priority;
  int pid;
  int pidToKill;
  MemoryHandler memoryHandler;
  AbstractQueue processQueue;
}