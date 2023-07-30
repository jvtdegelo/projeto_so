#ifndef CREATEPROCESS_H
#define CREATEPROCESS_H

#include "../../memory/MemoryHandler.h"
#include "../queue/AbstractQueue.h"
#include "AbstractProcess.h"

#include <vector>
#include <string>
#include <utility>

class CreateProcess: public AbstractProcess{
public:
  CreateProcess(int pid, int newProcessMemory, MemoryHandler* memoryHandler, AbstractQueue* processQueue);
  int getPriority() override;
  int getPID() override;
  std::vector< std::pair< std::string, std::string> > getTCB() override;
  bool executeOneQuantum() override;
  void killProcess() override;

private:
  int priority;
  int pid;
  int newProcessMemory;
  MemoryHandler* memoryHandler;
  AbstractQueue* processQueue;
  static int NEW_PROCESS_ID;
};

#endif
