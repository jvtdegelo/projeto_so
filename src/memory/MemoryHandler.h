#ifndef MEMORYHANDLER_H
#define MEMORYHANDLER_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility>
#include <vector>

#define MEMORY_SIZE 20

enum StatusMemory{
  Allocated,
  NoSpace,
  Fragmented
};

class MemoryHandler {
private:
  bool bitmap[MEMORY_SIZE];
  std::map< int, std::pair < int, int > > pidmap; 
  int freeSpace();
public:
  MemoryHandler();
  StatusMemory allocate(int size, int pid);
  void deallocate(int pid);
  void compress();
  std::vector< std::string> show();
};

#endif