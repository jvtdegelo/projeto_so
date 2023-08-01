#include "CreateProcess.h"
#include "InstructionProcess.h"

CreateProcess::CreateProcess(
  int pid, int newProcessMemory, MemoryHandler* memoryHandler, AbstractDispatcher* dispatcher): 
  priority(1), pid(pid), newProcessMemory(newProcessMemory), memoryHandler(memoryHandler), dispatcher(dispatcher) {
    getterPID = new GetterPID();
  }

int CreateProcess::getPriority() {
  return priority;
}

int CreateProcess::getPID() {
  return pid;
}

std::vector< std::string > CreateProcess::getTCB() {
  std::vector< std::string > tcb;
  tcb.push_back("PID: "+std::to_string(pid));
  tcb.push_back("Priority: "+std::to_string(priority)); 

  return tcb;
}

std::vector< std::string > CreateProcess::getStatus() {
  std::vector< std::string > status;
  status.push_back("create "+ std::to_string(newProcessMemory));
  return status;
}

std::string CreateProcess::getName() {
  return "PID " + std::to_string(pid) + ": CREATE " + std::to_string(newProcessMemory); 
}

StatusExecution CreateProcess::executeOneQuantum() {
  int newPid = getterPID->get();
  int memoryPosition = memoryHandler->allocate(newProcessMemory, newPid);
  if (memoryPosition == -1){
    priority++;
    return StatusExecution::Blocked;
  }
  AbstractProcess* p = new InstructionProcess(newPid, newProcessMemory, memoryPosition, memoryHandler);
  dispatcher->add(p);
  return StatusExecution::Finished;  
}

void CreateProcess::killProcess() {
  return;
}
