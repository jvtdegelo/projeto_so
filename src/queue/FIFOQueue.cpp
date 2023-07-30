#include "FIFOQueue.h"
#include <algorithm>
#include <iostream>
FIFOQueue::FIFOQueue(){
  return;
}

AbstractProcess* FIFOQueue::next() {
  AbstractProcess* next = q.front();
  q.pop_front();
  return next;
};

void FIFOQueue::add(AbstractProcess* process) {
  q.push_back(process);
};

AbstractProcess* FIFOQueue::remove(int pid) {
  auto it = std::find_if(q.begin(), q.end(), [pid](AbstractProcess* process) {
    std::cout<<"PID sendo analisado: "<<std::to_string(process->getPID())<<" com "<< std::to_string(pid)<<std::endl;
    return process->getPID() == pid;
  });
  
  if (it != q.end()) {
    AbstractProcess* removedValue = *it;
    q.erase(it);
    std::cout<<"Achou"<<std::endl;
    return removedValue;
  }
  std::cout<<"Nao achou"<<std::endl;
  return NULL;
};
bool FIFOQueue::isEmpty() {
  return q.empty();
}