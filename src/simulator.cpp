#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include "process/AbstractProcess.h"
#include "process/CreateProcess.h"
#include "process/KillProcess.h"
#include "queue/AbstractQueue.h"
#include "queue/FIFOQueue.h"
#include "memory/MemoryHandler.h"
#include "configuration/DispatcherConfiguration.h"

DispatcherConfiguration* config;
GetterPID* getterPID;
MemoryHandler* memoryHandler;
AbstractQueue* queue;
pthread_mutex_t mutex;
int lastCounter = 0;

void* listener(void* arg) {
  while (true) {
    std::ifstream inputFile("./memory_map.txt"); 
    if (inputFile.is_open()) {
      std::string line;
      std::getline(inputFile, line);
      int newCounter = std::stoi(line);
      if (newCounter!=lastCounter){
        std::getline(inputFile, line);
        char operation = line[0];
        int parameter = std::stoi(line.substr(2, line.size()-1));
        AbstractProcess* newProcess;
        if (operation == 'C')
          newProcess = new CreateProcess(getterPID->get(), parameter, memoryHandler, queue);
        else if (operation == 'K')
          newProcess = new KillProcess(getterPID->get(), parameter, memoryHandler, queue);
        pthread_mutex_lock(&mutex);
        queue->add(newProcess);
        pthread_mutex_unlock(&mutex);    
      }
      inputFile.close();
    } else {
      std::cout << "Unable to open the communication file" << std::endl;
    }
        
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return nullptr;
}

std::string fill_end_line(std::string str, int maxSize){
  if(maxSize> str.size())
    str.insert(str.end(), maxSize-str.size(), ' ');
  return str;
}

void show_interface(AbstractProcess* process, AbstractQueue* queue, MemoryHandler* memory){
  std::vector<std::string> emptyVector;
  std::vector<std::string> tcbProcess = process == NULL? emptyVector: process->getTCB();
  std::vector<std::string> statusProcess = process == NULL? emptyVector: process->getStatus();
  std::vector<std::string> showMemory = memory->show();
  pthread_mutex_lock(&mutex);
  std::vector<std::string> showQueue = queue->show();
  pthread_mutex_unlock(&mutex);    
  
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
  pthread_t thread;
	pthread_mutex_init(&mutex, NULL);

  config = new DispatcherConfiguration();
  getterPID = new GetterPID();
  memoryHandler = new MemoryHandler();
  queue = new FIFOQueue();
  int thread_num = 1;
  int result = pthread_create(&thread, nullptr, listener, nullptr);
  if (result != 0) {
    std::cout << "Error: Unable to create the new thread." << std::endl;
    return 1;
  }
  while(true){
		pthread_mutex_lock(&mutex);
    AbstractProcess* p = queue->isEmpty()? NULL: queue->next();
    pthread_mutex_unlock(&mutex);
    int timeToExecute = config->timeToExecute;
    bool finished = false;
    while(!finished && timeToExecute>0){
      show_interface(p, queue, memoryHandler);
      std::string line;
      getline(std::cin, line);
      if (p!=NULL)
        finished = p->executeOneQuantum();
      timeToExecute--;
    }
    if(!finished && p!=NULL){
      pthread_mutex_lock(&mutex);
      queue->add(p);
      pthread_mutex_unlock(&mutex);
    }
    else if(p!=NULL){
      p->killProcess();
    }
  }
  pthread_join(thread, nullptr);
  return 0;
}

