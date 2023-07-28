#include <stdio.h>
#include <iostream>
#include <deque>
using namespace std;

class FIFOQueue: public AbstractQueue{
public:
  AbstractProcess next(){
    AbstractProcess next = q.front();
    q.pop_front();
    return next;
  };

  void add(AbstractProcess process){
    q.push_back(process);
  };

  AbstractProcess remove(int pid){
    auto it = find_if(q.begin(), q.end(), [pid](const AbstractProcess& process) {
      return process.pid == pid;
    });
    
    if (it != q.end()) {
      AbstractProcess removedValue = *it;
      q.erase(it);
      return removedValue;
    }
    return NULL;
  };
  bool isEmpty(){
    return q.empty();
  }
private:  
  deque<AbstractProcess> q;
}