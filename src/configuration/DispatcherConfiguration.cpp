#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "DispatcherConfiguration.h"

DispatcherConfiguration::DispatcherConfiguration(){
  std::ifstream inputFile("./config_dispatcher.txt"); 
  if (inputFile.is_open()) {
    std::string line;
    std::getline(inputFile, line);
    size_t spacePos = line.find(' ');
    if (spacePos == std::string::npos) {
      timeToExecute=1;
      schedulingAlgorithm=0;
      std::cout<<"Nao foi possivel pegar config"<<std::endl;
      return;
    }
    std::string numberStr = line.substr(0, spacePos);
    std::string charStr = line.substr(spacePos + 1);

    try {
      timeToExecute = std::stoi(numberStr);
    } catch (const std::invalid_argument&) {
      timeToExecute=1;
      schedulingAlgorithm=0;
      std::cout<<"Nao foi possivel pegar config"<<std::endl;
      return;    
    } catch (const std::out_of_range&) {
      timeToExecute=1;
      schedulingAlgorithm=0;
      std::cout<<"Nao foi possivel pegar config"<<std::endl;
      return;
    }

    if (charStr.size() != 1) {
      timeToExecute=1;
      schedulingAlgorithm=0;
      std::cout<<"Nao foi possivel pegar config"<<std::endl;
      return;
    }
    schedulingAlgorithm = charStr[0] == 'R'? 1: 0;
  }
}