#include "RoundRobinDispatcher.h"
#include <algorithm>
#include <iostream>

RoundRobinDispatcher::RoundRobinDispatcher(int quantumsToExecute): quantumsToExecute(quantumsToExecute){
  currentProcess = nullptr;
  quantumsExecuted=0;
  return;
}

void RoundRobinDispatcher::executeOneQuantum() {
  if(currentProcess == nullptr)
    return;

  StatusExecution status = currentProcess->executeOneQuantum();
  switch(status){
    case Finished:
      currentProcess->killProcess();
      currentProcess = nullptr;
      quantumsExecuted=0;
      break;

    case Executing:
      quantumsExecuted++;
      if(quantumsExecuted==quantumsToExecute){
        quantumsExecuted = 0;
        q.push_back(currentProcess);
        currentProcess = nullptr;
      }
      break;

    case Blocked:
      q.push_back(currentProcess);
      currentProcess = nullptr;
      break;

    default:
      break;
  }
};

void RoundRobinDispatcher::add(AbstractProcess* process) {
  q.push_back(process);
};

AbstractProcess* RoundRobinDispatcher::getCurrentProcess() {
  if(currentProcess==nullptr && (!q.empty())){
    currentProcess = q.front();
    q.pop_front();
  }
    
  return currentProcess;
}

AbstractProcess* RoundRobinDispatcher::remove(int pid) {
  auto it = std::find_if(q.begin(), q.end(), [pid](AbstractProcess* process) {
    return process->getPID() == pid;
  });
  
  if (it != q.end()) {
    AbstractProcess* removedValue = *it;
    q.erase(it);
    return removedValue;
  }
  return NULL;
};

std::vector<std::string> RoundRobinDispatcher::showQueue(){
  std::vector<std::string> lines;
  for(AbstractProcess* process : q) {
    lines.push_back(process->getName());
  }
  return lines;
}