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
    return process->getPID() == pid;
  });
  
  if (it != q.end()) {
    AbstractProcess* removedValue = *it;
    q.erase(it);
    return removedValue;
  }
  return NULL;
};
bool FIFOQueue::isEmpty() {
  return q.empty();
}

std::vector<std::string> FIFOQueue::show(){
  std::vector<std::string> lines;
  for(AbstractProcess* process : q) {
    lines.push_back(process->getName());
  }
  return lines;
}