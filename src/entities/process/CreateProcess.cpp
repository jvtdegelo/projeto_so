#include <stdio.h>
#include <vector>
#include <string>
#include<utility>
using namespace std;

class CreateProcess: public AbstractProcess{
public:
  CreateProcess(
    int pid, int newProcessMemory, MemoryHandler& memoryHandler, AbstractQueue processQueue): 
    priority(1), pid(pid), newProcessMemory(newProcessMemory), memoryHandler(memoryHandler), processQueue(processQueue) {}

  int getPriority() override {
    return priority;
  }

  vector< pair< string, string> > getTCB() override {
    vector< pair < string, string> > tcb;
    tcb.push_back(make_pair("PID", to_string(pid)));
    tcb.push_back(make_pair("Priority", to_string(pid))); 

    return tcb;
  }

  bool executeOneQuantum() override {
    int newPid = ++NEW_PROCESS_ID;
    int memoryPosition = memoryHandler.Allocate(newProcessMemory, newPid);
    if (memoryPosition == -1){
      priority++;
      return
    }
    AbstractProcess = new InstructionProcess(pid, newProcessMemory, memoryPosition)
    processQueue.add(AbstractProcess);
    return true;  
  }
  
  void killProcess() override {
    return;
  }

private:
  int priority;
  int pid;
  int newProcessMemory;
  MemoryHandler memoryHandler;
  AbstractQueue processQueue;
  static int NEW_PROCESS_ID;
}