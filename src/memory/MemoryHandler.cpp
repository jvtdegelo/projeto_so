#include "MemoryHandler.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility>


MemoryHandler::MemoryHandler(){
  std::ifstream inputFile("./memory_map.txt"); 
  if (inputFile.is_open()) {
    std::string line;
    std::getline(inputFile, line);
    int memoryIndex = 0;
    for (int i=0; i<line.size(); i++){
      if(line[i] != '1' && line[i] != '0')
        continue;
      
      bool currentPositionOccupied = line[i] == '1';
      bitmap[memoryIndex] = currentPositionOccupied;
      memoryIndex++;
    }

    inputFile.close();
  } else {
    std::cout << "Unable to open the memory file." << std::endl;
  }
}

int MemoryHandler::allocate(int size, int pid){
  for (int i=0; i<MEMORY_SIZE-size+1; i++){
    bool hasSpace = true;
    for (int j=i; j<i+size; j++){
      if (bitmap[j]){
        hasSpace = false;
        break;
      }
    }
    if (hasSpace){
      for (int j=i; j<i+size; j++){
        bitmap[j] = true;
      }
      pidmap[pid] = std::make_pair(i, size);
      return i;
    }
  }

  std::cout<< "Não há espaço disponível na memória" << std::endl;
  return -1;

}

void MemoryHandler::deallocate(int pid){
  if(pidmap.count(pid)){
    std::pair< int, int> pidpair = pidmap[pid];
    int position = pidpair.first;
    int size = pidpair.second;
    for(int i=position; i<position+size; i++){
      bitmap[i] = false;
    }
    pidmap.erase(pid);
    return;
  }
  return;
}

char bool2str(bool position){
  return position? '1': '0';
}

std::vector< std::string> MemoryHandler::show(){
  std::vector< std::string> lines;
  for (int i=0; i<5; i++){
    std::string line;
    line+="  ";
    line+=bool2str(bitmap[4*i]);
    line+=" ";
    line+=bool2str(bitmap[4*i+1]);
    line+=" ";
    line+=bool2str(bitmap[4*i+2]);
    line+=" ";
    line+=bool2str(bitmap[4*i+3]);
    lines.push_back(line);
  }
  return lines;
}

