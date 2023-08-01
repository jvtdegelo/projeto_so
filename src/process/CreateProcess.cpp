#include "CreateProcess.h"
#include "InstructionProcess.h"
#include "MemoryCompressionProcess.h"

CreateProcess::CreateProcess(
  int pid, int memorySize, MemoryHandler* memoryHandler, AbstractDispatcher* dispatcher): 
  pid(pid), memorySize(memorySize), memoryHandler(memoryHandler), dispatcher(dispatcher) {
    getterPID = new GetterPID();
  }

int CreateProcess::getPID() {
  return pid;
}

std::vector< std::string > CreateProcess::getTCB() {
  std::vector< std::string > tcb;
  tcb.push_back("PID: " + std::to_string(pid));
  tcb.push_back("New memory size: "+std::to_string(memorySize));

  return tcb;
}

std::vector< std::string > CreateProcess::getStatus() {
  std::vector< std::string > status;
  status.push_back("create "+ std::to_string(memorySize));
  return status;
}

std::string CreateProcess::getName() {
  return "PID " + std::to_string(pid) + ": CREATE " + std::to_string(memorySize); 
}

StatusExecution CreateProcess::executeOneQuantum() {
  int newPid = getterPID->get();
  StatusMemory status = memoryHandler->allocate(memorySize, newPid);
  if (status==StatusMemory::Fragmented){
    AbstractProcess* p = new MemoryCompressionProcess(newPid, memoryHandler);
    dispatcher->add(p);
    return StatusExecution::Blocked;
  }
  else if(status==StatusMemory::NoSpace){
    return StatusExecution::Blocked;
  }
  else{
    AbstractProcess* p = new InstructionProcess(newPid, memorySize, memoryHandler);
    dispatcher->add(p);
    return StatusExecution::Finished;  
  }
}

void CreateProcess::killProcess() {
  return;
}
