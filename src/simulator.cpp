#include <stdio.h>
#include <iostream>
#include <string>
#include "process/AbstractProcess.h"
#include "process/CreateProcess.h"
#include "process/KillProcess.h"
#include "queue/AbstractQueue.h"
#include "queue/FIFOQueue.h"
#include "memory/MemoryHandler.h"

int main(){
  MemoryHandler* memoryHandler = new MemoryHandler();
  AbstractQueue* queue = new FIFOQueue();
  CreateProcess cp1(11, 4, memoryHandler, queue);
  CreateProcess cp2(12, 5, memoryHandler, queue);
  CreateProcess cp3(13, 5, memoryHandler, queue);
  KillProcess kp1(14, 12, memoryHandler, queue);
  queue->add(&cp1);
  queue->add(&kp1);
  queue->add(&cp2);
  queue->add(&cp3);
  while(!queue->isEmpty()){
    AbstractProcess* p = queue->next();
    std::cout << "Prestes a executar processo: " + std::to_string(p->getPID());
    std::string line;
    getline(std::cin, line);
    bool finished = p->executeOneQuantum();
    if(!finished){
      queue->add(p);
    }
    else{
      p->killProcess();
    }
    std::cout<< "Finished one quantum" << std::endl;
    std::cout<< std::endl;
  }
  return 0;
}