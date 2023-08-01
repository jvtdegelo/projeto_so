#include "MemoryCompressionProcess.h"

MemoryCompressionProcess::MemoryCompressionProcess(
  int pid, MemoryHandler* memoryHandler): 
  pid(pid), memoryHandler(memoryHandler) {}

int MemoryCompressionProcess::getPID() {
  return pid;
}

std::vector< std::string > MemoryCompressionProcess::getTCB() {
  std::vector< std::string > tcb;
  tcb.push_back("PID: " + std::to_string(pid));
  
  return tcb;
}

std::vector< std::string > MemoryCompressionProcess::getStatus() {
  std::vector< std::string > status;
  status.push_back("memory compression");
  return status;
}

std::string MemoryCompressionProcess::getName() {
  return "PID " + std::to_string(pid) + ": COMPRESSION"; 
}

StatusExecution MemoryCompressionProcess::executeOneQuantum() {
  memoryHandler->compress();
  return StatusExecution::Finished;  
}

void MemoryCompressionProcess::killProcess() {
  return;
}
