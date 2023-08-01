#ifndef MEMORYCOMPRESSIONPROCESS_H
#define MEMORYCOMPRESSIONPROCESS_H

#include <vector>
#include <string>

#include "../memory/MemoryHandler.h"
#include "AbstractProcess.h"

class MemoryCompressionProcess: public AbstractProcess{
public:
  MemoryCompressionProcess(int pid, MemoryHandler* memoryHandler);
  int getPID() override;
  std::vector< std::string > getTCB() override;
  std::vector< std::string > getStatus() override;
  std::string getName() override;
  StatusExecution executeOneQuantum() override;
  void killProcess() override;

private:
  int pid;
  MemoryHandler* memoryHandler;
};

#endif
