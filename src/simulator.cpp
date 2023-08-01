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
#include "dispatcher/AbstractDispatcher.h"
#include "dispatcher/FIFODispatcher.h"
#include "dispatcher/RoundRobinDispatcher.h"
#include "memory/MemoryHandler.h"
#include "configuration/DispatcherConfiguration.h"

DispatcherConfiguration* config;
GetterPID* getterPID;
MemoryHandler* memoryHandler;
AbstractDispatcher* dispatcher;
pthread_mutex_t mutex;

void* listener(void* arg) {
  while (true) {
    std::ifstream communicationFileRead("./communication.txt"); 
    if (communicationFileRead.is_open()) {
      std::string line;
      std::getline(communicationFileRead, line);
      while(!communicationFileRead.eof()){
        char operation = line[0];
        int parameter = std::stoi(line.substr(2, line.size()-1));
        AbstractProcess* newProcess;
        pthread_mutex_lock(&mutex);
        if (operation == 'c'){
          newProcess = new CreateProcess(getterPID->get(), parameter, memoryHandler, dispatcher);
        }
        else if (operation == 'k'){
          newProcess = new KillProcess(getterPID->get(), parameter, memoryHandler, dispatcher);
        }
        dispatcher->add(newProcess);
        pthread_mutex_unlock(&mutex);
        std::getline(communicationFileRead, line);
      }
      communicationFileRead.close();

      std::ofstream communicationFileWrite("./communication.txt");
      if (!communicationFileWrite) {
        std::cerr << "Error opening the communication file for writing." << std::endl;
      }
      communicationFileWrite.close();

    } else {
      std::cout << "Unable to open the communication file" << std::endl;
    }
        
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }

  return nullptr;
}

std::string fill_end_line(std::string str, int maxSize){
  if(maxSize> str.size())
    str.insert(str.end(), maxSize-str.size(), ' ');
  return str;

}

void show_interface(AbstractProcess* process, AbstractDispatcher* dispatcher, MemoryHandler* memory){
  std::vector<std::string> emptyVector;
  std::vector<std::string> tcbProcess = process == nullptr? emptyVector: process->getTCB();
  std::vector<std::string> statusProcess = process == nullptr? emptyVector: process->getStatus();
  std::vector<std::string> showMemory = memory->show();
  pthread_mutex_lock(&mutex);
  std::vector<std::string> showQueue = dispatcher->showQueue();
  pthread_mutex_unlock(&mutex);
  std::cout<<"+=======================++===============++==============++=======================+"<<std::endl;
  std::cout<<"|         Status        ||      TCB      || Mapa de bits ||    Fila de Prontos    |"<<std::endl;
  std::cout<<"+=======================++===============++==============++=======================+"<<std::endl;
  for(int i=0; i<8; i++){
    std::string statusLine = i<statusProcess.size()? statusProcess[i]: "";
    std::string tcbLine = i<tcbProcess.size()? tcbProcess[i]: "";
    std::string memoryLine = i<showMemory.size()? showMemory[i]: "";
    std::string queueLine = i<showQueue.size()? showQueue[i]: "";
    std::cout<<"| " << fill_end_line(statusLine, 21) << " || " << fill_end_line(tcbLine, 13) << " || " << fill_end_line(memoryLine, 12) << " || "<< fill_end_line(queueLine, 21)<< " |"<< std::endl;
  }
  std::cout<<"+-----------------------++---------------++--------------++-----------------------+"<<std::endl;
  std::cout<< std::endl;
}

AbstractDispatcher* get_dispatcher(DispatcherConfiguration* config){
  if (config->schedulingAlgorithm == 0)
    return new FIFODispatcher();

  else
    return new RoundRobinDispatcher(config->timeToExecute);
}

int main(){
  pthread_t thread;
	pthread_mutex_init(&mutex, NULL);

  config = new DispatcherConfiguration();
  getterPID = new GetterPID();
  memoryHandler = new MemoryHandler();
  dispatcher = get_dispatcher(config);
  int thread_num = 1;
  int result = pthread_create(&thread, nullptr, listener, nullptr);
  if (result != 0) {
    std::cout << "Error: Unable to create the new thread." << std::endl;
    return 1;
  }
  while(true){
		pthread_mutex_lock(&mutex);
    AbstractProcess* p = dispatcher->getCurrentProcess();
    pthread_mutex_unlock(&mutex);
    show_interface(p, dispatcher, memoryHandler);
    std::string line;
    getline(std::cin, line);
    pthread_mutex_lock(&mutex);
    dispatcher->executeOneQuantum();
    pthread_mutex_unlock(&mutex);
  }
  pthread_join(thread, nullptr);
  return 0;
}

