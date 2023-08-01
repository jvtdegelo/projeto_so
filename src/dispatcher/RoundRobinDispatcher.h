#ifndef ROUNDROBINDISPATCHER_H
#define ROUNDROBINDISPATCHER_H

#include "AbstractDispatcher.h"
#include "../process/AbstractProcess.h"
#include <deque>
#include <vector>
#include <string>

class RoundRobinDispatcher: public AbstractDispatcher{
public:
  RoundRobinDispatcher(int quantumToExecute);
  void executeOneQuantum() override;
  AbstractProcess* getCurrentProcess() override;
  void add(AbstractProcess* process) override;
  AbstractProcess* remove(int pid) override;
  std::vector<std::string> showQueue() override;

private:
  int quantumsToExecute;
  int quantumsExecuted;
  std::deque<AbstractProcess*> q;
  AbstractProcess* currentProcess;
};

#endif