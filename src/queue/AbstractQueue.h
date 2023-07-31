#ifndef ABSTRACTQUEUE_H
#define ABSTRACTQUEUE_H

#include <string>
#include <vector>
#include "../process/AbstractProcess.h"

class AbstractQueue{
public:
  virtual AbstractProcess* next()=0;
  virtual void add(AbstractProcess* process)=0;
  virtual AbstractProcess* remove(int pid)=0;
  virtual bool isEmpty()=0;
  virtual std::vector<std::string> show()=0;
};

#endif