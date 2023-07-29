#include <stdio.h>
#include <vector>
#include <string>
#include<utility>
using namespace std;

class InstructionProcess: public AbstractProcess{
public:
  InstructionProcess(int pid, int memorySize, int memoryPosition, MemoryHandler& memoryHandler): 
  priority(2), pid(pid), memorySize(memorySize), memoryPosition(memoryPosition), memoryHandler(memoryHandler) {
    code.push_back("MOV AX, #0");
    code.push_back("MOV BX, AX");
    code.push_back("JMP #0");
    code.push_back("HLT");
  }

  int getPriority() override {
    return priority;
  }

  vector< pair< string, string> > getTCB() override {
    vector< pair < string, string> > tcb;
    tcb.push_back(make_pair("PID", to_string(pid)));
    tcb.push_back(make_pair("Priority", to_string(priority))); 
    tcb.push_back(make_pair("Program Counter", to_string(programCounter)));
    if(checkPastCodeContains("AX"));
      tcb.push_back(make_pair("AX", "#VALOR"));
    if(checkPastCodeContains("BX"));
      tcb.push_back(make_pair("BX", "#VALOR"));
    return tcb;
  };

  bool executeOneQuantum() override {
    programCounter+=1;
    if(programCounter == code.size()){
      return true
    }
    return false;
  }
  
  void killProcess() override {
    memoryHandler.Deallocate(pid);
    return;
  }

private:
  int pid;
  int priority;
  int memorySize;
  int memoryPosition;
  int programCounter=0;
  MemoryHandler memoryHandler; 
  vector< string > code;
  bool checkPastCodeContains(string str){
    for(int i=0; i<programCounter; i++){
      string line = code[i];
      if(line.find(str) != string::npos){
        return true;
      }
    }
    return false;
  }
}