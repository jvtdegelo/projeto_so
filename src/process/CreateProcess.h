#ifndef CREATEPROCESS_H
#define CREATEPROCESS_H

#include <vector>
#include <string>
#include <utility>

#include "../memory/MemoryHandler.h"
#include "../queue/AbstractQueue.h"
#include "../utils/GetterPID.h"
#include "AbstractProcess.h"

class CreateProcess: public AbstractProcess{
public:
  CreateProcess(int pid, int newProcessMemory, MemoryHandler* memoryHandler, AbstractQueue* processQueue);
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
  int newProcessMemory;
  MemoryHandler* memoryHandler;
  AbstractQueue* processQueue;
  GetterPID* getterPID;
};

#endif
