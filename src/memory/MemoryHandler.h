#ifndef MEMORYHANDLER_H
#define MEMORYHANDLER_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include<utility>

#define MEMORY_SIZE 20

class MemoryHandler {
private:
  bool bitmap[MEMORY_SIZE];
  std::map< int, std::pair < int, int > > pidmap; 

public:
  MemoryHandler();
  int Allocate(int size, int pid);
  void Deallocate(int pid);
};

#endif