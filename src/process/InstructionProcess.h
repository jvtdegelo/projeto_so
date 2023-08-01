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
  InstructionProcess(int pid, int memorySize, MemoryHandler* memoryHandler);
  int getPID() override;
  std::vector< std::string > getTCB() override;
  std::vector< std::string > getStatus() override;
  std::string getName() override;
  StatusExecution executeOneQuantum() override;
  void killProcess() override;

private:
  int pid;
  int memorySize;
  int programCounter=0;
  MemoryHandler* memoryHandler; 
  std::vector< std::string > code;
  bool checkPastCodeContains(std::string str);
  void createRandomProcess();
};

#endif
