#ifndef FIFOQUEUE_H
#define FIFOQUEUE_H

#include "AbstractQueue.h"
#include "../process/AbstractProcess.h"
#include <deque>
#include <vector>
#include <string>

class FIFOQueue: public AbstractQueue{
public:
  FIFOQueue();
  AbstractProcess* next() override;
  void add(AbstractProcess* process) override;
  AbstractProcess* remove(int pid) override;
  bool isEmpty() override;
  std::vector<std::string> show() override;

private:  
  std::deque<AbstractProcess*> q;
};

#endif