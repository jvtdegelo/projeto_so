#ifndef INSTRUCTIONPROCESS_H
#define INSTRUCTIONPROCESS_H

#include <stdio.h>
#include <vector>
#include <string>
#include <utility>

#include "../memory/MemoryHandler.h"
#include "AbstractProcess.h"

class InstructionProcess: public AbstractProcess{
public:
  InstructionProcess(int pid, int memorySize, int memoryPosition, MemoryHandler* memoryHandler);
  int getPriority() override;
  int getPID() override;
  std::vector< std::string > getTCB() override;
  std::vector< std::string > getStatus() override;
  std::string getName() override;
  bool executeOneQuantum() override;
  void killProcess() override;

private:
  int pid;
  int priority;
  int memorySize;
  int memoryPosition;
  int programCounter=0;
  MemoryHandler* memoryHandler; 
  std::vector< std::string > code;
  bool checkPastCodeContains(std::string str);
};

#endif
