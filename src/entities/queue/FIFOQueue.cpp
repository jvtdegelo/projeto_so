#include <stdio.h>
#include <iostream>
#include <deque>

class FIFOQueue: public AbstractQueue{
public:
  AbstractProcess* next(){
    AbstractProcess* next = q.front();
    q.pop_front();
    return next;
  };

  void add(AbstractProcess* process){
    q.push_back(process);
  };

  AbstractProcess* remove(int pid){
    auto it = find_if(q.begin(), q.end(), [pid](const AbstractProcess* process) {
      return process->getPID() == pid;
    });
    
    if (it != q.end()) {
      AbstractProcess* removedValue = *it;
      q.erase(it);
      return removedValue;
    }
    return NULL;
  };
  bool isEmpty(){
    return q.empty();
  }
private:  
  std::deque<AbstractProcess*> q;
}