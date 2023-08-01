#include "InstructionProcess.h"
#include <random>

InstructionProcess::InstructionProcess(int pid, int memorySize, MemoryHandler* memoryHandler):
  pid(pid), memorySize(memorySize), memoryHandler(memoryHandler){ 
  createRandomProcess();
}

int InstructionProcess::getPID() {
  return pid;
}

std::vector<std::string > InstructionProcess::getTCB() {
  std::vector<std::string > tcb;
  tcb.push_back("PID: "+std::to_string(pid)); 
  tcb.push_back("PC: "+ std::to_string(programCounter));
  tcb.push_back("Memory Size: " + std::to_string(memorySize));
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

StatusExecution InstructionProcess::executeOneQuantum() {
  programCounter+=1;
  if(programCounter == code.size()){
    return StatusExecution::Finished;
  }
  return StatusExecution::Executing;
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

void InstructionProcess::createRandomProcess(){
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(0, 4);
  int num = dist(gen);
  if(num == 0){
    code.push_back("PUSH AX");
    code.push_back("PUSH BX");
    code.push_back("MOV AX, #0");
    code.push_back("MOV BX, AX");
    code.push_back("MOV AX, #1");
    code.push_back("MOV AX, BX");
    code.push_back("JMP #0");
    code.push_back("HLT");
  }
  else if(num==1){
    code.push_back("MOV AX, #0");
    code.push_back("JMP #0");
    code.push_back("HLT");
  }

  else if(num==2){
    code.push_back("MOV BX, #0");
    code.push_back("MOV AX, #0");
    code.push_back("POP AX");
    code.push_back("JMP #0");
    code.push_back("HLT");
  }
  
  else if(num==3){
    code.push_back("HLT");
  }

  else{
    code.push_back("MOV BX, #0");
    code.push_back("JMP #0");
    code.push_back("HLT");   
  }
}