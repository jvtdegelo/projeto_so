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

std::vector<std::string > InstructionProcess::getTCB() {
  std::vector<std::string > tcb;
  tcb.push_back("PID: "+std::to_string(pid));
  tcb.push_back("Priority: "+std::to_string(priority)); 
  tcb.push_back("PC: "+ std::to_string(programCounter));
  if(checkPastCodeContains("AX"))
    tcb.push_back("AX: #VALOR");
  if(checkPastCodeContains("BX"))
    tcb.push_back("BX: #VALOR");
  return tcb;
}

std::vector< std::string > InstructionProcess::getStatus() {
  std::vector< std::string > status;
  for (int i=0; i< code.size(); i++){
    std::string line = programCounter == i? code[i] + " <-": code[i];
    status.push_back(line);
  }
  return status;
}

std::string InstructionProcess::getName() {
  return "PID " + std::to_string(pid) + ": INSTRUCTIONS"; 
}

bool InstructionProcess::executeOneQuantum() {
  programCounter+=1;
  if(programCounter == code.size()){
    return true;
  }
  return false;
}
  
void InstructionProcess::killProcess() {
  memoryHandler->deallocate(pid);
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