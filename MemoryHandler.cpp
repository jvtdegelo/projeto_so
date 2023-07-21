#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include<utility>
using namespace std;

int MEMORY_SIZE = 20;

class MemoryHandler {
    private:
        bool bitmap[MEMORY_SIZE];
        map< int, pair < int, int > > pidmap; 

    public:
        MemoryHandler(){
            ifstream inputFile("memory_map.txt"); 
            if (inputFile.is_open()) {
                string line;
                getline(inputFile, line);
                int memoryIndex = 0;
                for (int i=0; i<line.length; i++){
                    if(line[i] != "1" && line[i] != "0")
                        continue;
                    
                    bool currentPositionOccupied = line[i] == "1";
                    bitmap[memoryIndex] = currentPositionOccupied;
                    memoryIndex++;
                }

                inputFile.close();
            } else {
                cout << "Unable to open the file." << endl;
            }
        }

        int Allocate(int size, int pid){
            for (int i=0; i<MEMORY_SIZE-size+1; i++){
                bool hasSpace = true;
                for (int j=i; j<i+size; j++){
                    if (!bitmap[j]){
                        hasSpace = false;
                        break;
                    }
                }
                if (hasSpace){
                    for (int j=i; j<i+size; j++){
                        bitmap[j] = true;
                    }
                    pidmap[pid] = make_pair(i, size);
                    return i;
                }
            }

            cout<< "Não há espaço disponível na memória" << endl;
            return -1;

        }

        void Deallocate(int pid){
            if(pidmap.count(pid)){
                pair< int, int> pidpair = pidmap[pid];
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
}