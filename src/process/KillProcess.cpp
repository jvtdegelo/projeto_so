#include "KillProcess.h"

KillProcess::KillProcess(
  int pid, int pidToKill, MemoryHandler* memoryHandler, AbstractQueue* processQueue):
  priority(1), pid(pid), pidToKill(pidToKill), memoryHandler(memoryHandler), processQueue(processQueue) {}

int KillProcess::getPriority() {
  return priority;
}

int KillProcess::getPID() {
  return pid;
}

std::vector< std::string > KillProcess::getTCB() {
  std::vector< std::string > tcb;
  tcb.push_back("PID: "+ std::to_string(pid));
  tcb.push_back("Priority: "+std::to_string(priority)); 

  return tcb;
}

std::vector< std::string > KillProcess::getStatus() {
  std::vector< std::string > status;
  status.push_back("kill "+ std::to_string(pidToKill));
  return status;
}

std::string KillProcess::getName() {
  return "PID " + std::to_string(pid) + ": KILL " + std::to_string(pidToKill); 
}

bool KillProcess::executeOneQuantum() {
  AbstractProcess* process = processQueue->remove(pidToKill);
  if(process!=NULL)
    process->killProcess();
  return true;
}

void KillProcess::killProcess() {
  return;
}
