#ifndef FIFODISPATCHER_H
#define FIFODISPATCHER_H

#include "AbstractDispatcher.h"
#include "../process/AbstractProcess.h"
#include <deque>
#include <vector>
#include <string>

class FIFODispatcher: public AbstractDispatcher{
public:
  FIFODispatcher();
  void executeOneQuantum() override;
  AbstractProcess* getCurrentProcess() override;
  void add(AbstractProcess* process) override;
  AbstractProcess* remove(int pid) override;
  std::vector<std::string> showQueue() override;

private:  
  std::deque<AbstractProcess*> q;
  AbstractProcess* currentProcess;
};

#endif