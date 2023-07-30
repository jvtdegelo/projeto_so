#include "InstructionProcess.h"

InstructionProcess::InstructionProcess(int pid, int memorySize, int memoryPosition, MemoryHandler* memoryHandler):
  priority(2), pid(pid), memorySize(memorySize), memoryPosition(memoryPosition), memoryHandler(memoryHandler){ 
  code.push_back("MOV AX, #0");
  code.push_back("MOV BX, AX");
  code.push_back("JMP #0");
  code.push_back("HLT");
}

int InstructionProcess::getPriority() {
  return priority;
}

int InstructionProcess::getPID() {
  return pid;
}

std::vector< std::pair< std::string, std::string> > InstructionProcess::getTCB() {
  std::vector< std::pair < std::string, std::string> > tcb;
  tcb.push_back(std::make_pair("PID", std::to_string(pid)));
  tcb.push_back(std::make_pair("Priority", std::to_string(priority))); 
  tcb.push_back(std::make_pair("Program Counter", std::to_string(programCounter)));
  if(checkPastCodeContains("AX"));
    tcb.push_back(std::make_pair("AX", "#VALOR"));
  if(checkPastCodeContains("BX"));
    tcb.push_back(std::make_pair("BX", "#VALOR"));
  return tcb;
}

bool InstructionProcess::executeOneQuantum() {
  programCounter+=1;
  if(programCounter == code.size()){
    return true;
  }
  return false;
}
  
void InstructionProcess::killProcess() {
  memoryHandler->Deallocate(pid);
  return;
}

bool InstructionProcess::checkPastCodeContains(std::string str){
  for(int i=0; i<programCounter; i++){
    std::string line = code[i];
    if(line.find(str) != std::string::npos){
      return true;
    }
  }
  return false;
}