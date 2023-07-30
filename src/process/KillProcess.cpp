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

std::vector< std::pair< std::string, std::string> > KillProcess::getTCB() {
  std::vector< std::pair < std::string, std::string> > tcb;
  tcb.push_back(std::make_pair("PID", std::to_string(pid)));
  tcb.push_back(std::make_pair("Priority", std::to_string(priority))); 

  return tcb;
}

bool KillProcess::executeOneQuantum() {
  std::cout<<"Executando kill: "<<std::to_string(pidToKill)<< std::endl;
  AbstractProcess* process = processQueue->remove(pidToKill);
  if(process!=NULL)
    process->killProcess();
  return true;
}

void KillProcess::killProcess() {
  return;
}
