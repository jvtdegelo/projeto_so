#include <stdio.h>
#include <iostream>
#include <string>
#include "entities/process/AbstractProcess.h"
#include "entities/process/CreateProcess.h"
#include "entities/queue/AbstractQueue.h"
#include "entities/queue/FIFOQueue.h"
#include "memory/MemoryHandler.h"

int main(){
  MemoryHandler* memoryHandler = new MemoryHandler();
  AbstractQueue* queue = new FIFOQueue();
  CreateProcess cp1(11, 4, memoryHandler, queue);
  queue->add(&cp1);
  while(!queue->isEmpty()){
    AbstractProcess* p = queue->next();
    std::cout << "Prestes a executar processo: " + p->getPID();
    std::string line;
    getline(std::cin, line);
    bool finished = p->executeOneQuantum();
    if(!finished){
      queue->add(p);
      std::cout<< "added back"<< std::endl;
    }
    std::cout<< "Finished one quantum" << std::endl;
    std::cout<< std::endl;
  }
  return 0;
}