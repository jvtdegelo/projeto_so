#include "KillProcess.h"

KillProcess::KillProcess(
  int pid, int pidToKill, MemoryHandler* memoryHandler, AbstractDispatcher* dispatcher):
  pid(pid), pidToKill(pidToKill), memoryHandler(memoryHandler), dispatcher(dispatcher) {}

int KillProcess::getPID() {
  return pid;
}

std::vector< std::string > KillProcess::getTCB() {
  std::vector< std::string > tcb;
  tcb.push_back("PID: "+ std::to_string(pid));
  tcb.push_back("PID to kill: " + std::to_string(pidToKill));

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

StatusExecution KillProcess::executeOneQuantum() {
  AbstractProcess* process = dispatcher->remove(pidToKill);
  if(process!=NULL)
    process->killProcess();
  return StatusExecution::Finished;
}

void KillProcess::killProcess() {
  return;
}
