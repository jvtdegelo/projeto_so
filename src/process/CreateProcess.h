#ifndef CREATEPROCESS_H
#define CREATEPROCESS_H

#include <vector>
#include <string>
#include <utility>

#include "../memory/MemoryHandler.h"
#include "../dispatcher/AbstractDispatcher.h"
#include "../utils/GetterPID.h"
#include "AbstractProcess.h"

class CreateProcess: public AbstractProcess{
public:
  CreateProcess(int pid, int newProcessMemory, MemoryHandler* memoryHandler, AbstractDispatcher* dispatcher);
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
  int newProcessMemory;
  MemoryHandler* memoryHandler;
  AbstractDispatcher* dispatcher;
  GetterPID* getterPID;
};

#endif
