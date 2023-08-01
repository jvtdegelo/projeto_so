#include "FIFODispatcher.h"
#include <algorithm>
#include <iostream>

FIFODispatcher::FIFODispatcher() {
  currentProcess = nullptr;
  return;
}

void FIFODispatcher::executeOneQuantum() {
  if(currentProcess == nullptr)
    return;

  StatusExecution status = currentProcess->executeOneQuantum();
  switch(status){
    case Finished:
      currentProcess->killProcess();
      currentProcess = nullptr;
      break;

    case Executing:
      break;

    case Blocked:
      q.push_back(currentProcess);
      currentProcess = nullptr;
      break;

    default:
      break;
  }
};

void FIFODispatcher::add(AbstractProcess* process) {
  q.push_back(process);
};

AbstractProcess* FIFODispatcher::getCurrentProcess() {
  if(currentProcess==nullptr && (!q.empty())){
    currentProcess = q.front();
    q.pop_front();
  }
    
  return currentProcess;
}

AbstractProcess* FIFODispatcher::remove(int pid) {
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

std::vector<std::string> FIFODispatcher::showQueue(){
  std::vector<std::string> lines;
  for(AbstractProcess* process : q) {
    lines.push_back(process->getName());
  }
  return lines;
}