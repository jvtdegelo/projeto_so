#ifndef KILLPROCESS_H
#define KILLPROCESS_H

#include <stdio.h>
#include <vector>
#include <string>
#include <utility>

#include "../memory/MemoryHandler.h"
#include "../dispatcher/AbstractDispatcher.h"
#include "AbstractProcess.h"

class KillProcess: public AbstractProcess{
public:
  KillProcess(int pid, int pidToKill, MemoryHandler* memoryHandler, AbstractDispatcher* dispatcher);
  int getPriority() override;
  int getPID() override;
  std::vector< std::string > getTCB() override;
  std::vector< std::string > getStatus() override;
  std::string getName() override;
  StatusExecution executeOneQuantum() override;
  void killProcess() override;

private:
  int priority;
  int pid;
  int pidToKill;
  MemoryHandler* memoryHandler;
  AbstractDispatcher* dispatcher;
};

#endif