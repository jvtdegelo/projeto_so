#include <stdio.h>
#include <vector>
#include <string>
#include<utility>

class CreateProcess: public AbstractProcess{
public:
  CreateProcess(
    int pid, int newProcessMemory, MemoryHandler* memoryHandler, AbstractQueue* processQueue): 
    priority(1), pid(pid), newProcessMemory(newProcessMemory), memoryHandler(memoryHandler), processQueue(processQueue) {}

  int getPriority() override {
    return priority;
  }

  int getPID() override {
    return pid;
  }

  std::vector< std::pair< std::string, std::string> > getTCB() override {
    std::vector< std::pair < std::string, std::string> > tcb;
    tcb.push_back(std::make_pair("PID", to_string(pid)));
    tcb.push_back(std::make_pair("Priority", to_string(priority))); 

    return tcb;
  }

  bool executeOneQuantum() override {
    int newPid = ++NEW_PROCESS_ID;
    int memoryPosition = memoryHandler->Allocate(newProcessMemory, newPid);
    if (memoryPosition == -1){
      priority++;
      return
    }
    AbstractProcess p = new InstructionProcess(pid, newProcessMemory, memoryPosition)
    processQueue->add(p);
    return true;  
  }
  
  void killProcess() override {
    return;
  }

private:
  int priority;
  int pid;
  int newProcessMemory;
  MemoryHandler* memoryHandler;
  AbstractQueue* processQueue;
  static int NEW_PROCESS_ID;
}