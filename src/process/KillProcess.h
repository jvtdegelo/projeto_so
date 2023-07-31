#ifndef KILLPROCESS_H
#define KILLPROCESS_H

#include <stdio.h>
#include <vector>
#include <string>
#include <utility>

#include "../memory/MemoryHandler.h"
#include "../queue/AbstractQueue.h"
#include "AbstractProcess.h"

class KillProcess: public AbstractProcess{
public:
  KillProcess(int pid, int pidToKill, MemoryHandler* memoryHandler, AbstractQueue* processQueue);
  int getPriority() override;
  int getPID() override;
  std::vector< std::string > getTCB() override;
  std::vector< std::string > getStatus() override;
  std::string getName() override;
  bool executeOneQuantum() override;
  void killProcess() override;

private:
  int priority;
  int pid;
  int pidToKill;
  MemoryHandler* memoryHandler;
  AbstractQueue* processQueue;
};

#endif