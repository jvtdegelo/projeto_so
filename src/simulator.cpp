#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "process/AbstractProcess.h"
#include "process/CreateProcess.h"
#include "process/KillProcess.h"
#include "queue/AbstractQueue.h"
#include "queue/FIFOQueue.h"
#include "memory/MemoryHandler.h"

std::string fill_end_line(std::string str, int maxSize){
  if(maxSize> str.size())
    str.insert(str.end(), maxSize-str.size(), ' ');
  return str;
}

void show_interface(AbstractProcess* process, AbstractQueue* queue, MemoryHandler* memory){
  std::vector<std::string> tcbProcess = process->getTCB();
  std::vector<std::string> statusProcess = process->getStatus();
  std::vector<std::string> showMemory = memory->show();
  std::vector<std::string> showQueue = queue->show();
  std::cout<<"+=======================++===============++==============++=====================+"<<std::endl;
  std::cout<<"|         Status        ||      TCB      || Mapa de bits ||   Fila de Prontos   |"<<std::endl;
  std::cout<<"+=======================++===============++==============++=====================+"<<std::endl;
  for(int i=0; i<8; i++){
    std::string statusLine = i<statusProcess.size()? statusProcess[i]: "";
    std::string tcbLine = i<tcbProcess.size()? tcbProcess[i]: "";
    std::string memoryLine = i<showMemory.size()? showMemory[i]: "";
    std::string queueLine = i<showQueue.size()? showQueue[i]: "";
    std::cout<<"| " << fill_end_line(statusLine, 21) << " || " << fill_end_line(tcbLine, 13) << " || " << fill_end_line(memoryLine, 12) << " || "<< fill_end_line(queueLine, 19)<< " |"<< std::endl;
  }
  std::cout<<"+-----------------------++---------------++--------------++---------------------+"<<std::endl;
  std::cout<< std::endl;
}

int main(){
  GetterPID* getterPID = new GetterPID();
  MemoryHandler* memoryHandler = new MemoryHandler();
  AbstractQueue* queue = new FIFOQueue();
  CreateProcess cp1(getterPID->get(), 11, memoryHandler, queue);
  CreateProcess cp2(getterPID->get(), 11, memoryHandler, queue);
  CreateProcess cp3(getterPID->get(), 11, memoryHandler, queue);
  KillProcess kp1(getterPID->get(), 1, memoryHandler, queue);
  queue->add(&cp1);
  queue->add(&kp1);
  queue->add(&cp2);
  queue->add(&cp3);
  while(!queue->isEmpty()){
    AbstractProcess* p = queue->next();
    show_interface(p, queue, memoryHandler);
    std::string line;
    getline(std::cin, line);
    bool finished = p->executeOneQuantum();
    if(!finished){
      queue->add(p);
    }
    else{
      p->killProcess();
    }
  }
  return 0;
}

