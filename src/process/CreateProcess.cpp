#include "CreateProcess.h"
#include "InstructionProcess.h"

CreateProcess::CreateProcess(
  int pid, int newProcessMemory, MemoryHandler* memoryHandler, AbstractQueue* processQueue): 
  priority(1), pid(pid), newProcessMemory(newProcessMemory), memoryHandler(memoryHandler), processQueue(processQueue) {}

int CreateProcess::getPriority() {
  return priority;
}

int CreateProcess::getPID() {
  return pid;
}

std::vector< std::pair< std::string, std::string> > CreateProcess::getTCB() {
  std::vector< std::pair < std::string, std::string> > tcb;
  tcb.push_back(std::make_pair("PID", std::to_string(pid)));
  tcb.push_back(std::make_pair("Priority", std::to_string(priority))); 

  return tcb;
}

bool CreateProcess::executeOneQuantum() {
  int newPid = ++NEW_PROCESS_ID;
  int memoryPosition = memoryHandler->Allocate(newProcessMemory, newPid);
  if (memoryPosition == -1){
    priority++;
    return false;
  }
  AbstractProcess* p = new InstructionProcess(newPid, newProcessMemory, memoryPosition, memoryHandler);
  processQueue->add(p);
  return true;  
}

void CreateProcess::killProcess() {
  return;
}

int CreateProcess::NEW_PROCESS_ID = 0;