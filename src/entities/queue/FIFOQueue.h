#ifndef FIFOQUEUE_H
#define FIFOQUEUE_H

#include "AbstractQueue.h"
#include <deque>

class FIFOQueue: public AbstractQueue{
public:
  AbstractProcess* next() override;
  void add(AbstractProcess* process) override;
  AbstractProcess* remove(int pid) override;
  bool isEmpty() override;

private:  
  std::deque<AbstractProcess*> q;
};

#endif