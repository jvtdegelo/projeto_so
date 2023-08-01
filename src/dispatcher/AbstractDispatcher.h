#ifndef ABSTRACTDISPATCHER_H
#define ABSTRACTDISPATCHER_H

#include <string>
#include <vector>
#include "../process/AbstractProcess.h"

class AbstractDispatcher{
public:
  virtual void executeOneQuantum()=0;
  virtual AbstractProcess* getCurrentProcess()=0;
  virtual void add(AbstractProcess* process)=0;
  virtual AbstractProcess* remove(int pid)=0;
  virtual std::vector<std::string> showQueue()=0;
};

#endif